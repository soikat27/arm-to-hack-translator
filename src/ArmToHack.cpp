#include "../include/ArmToHack.h"
#include "../include/token_io.h"

#include <string>
#include <iostream>
#include <cstdio> // for file deletion
using namespace std;

// constructor
ArmToHack::ArmToHack()
{
}

// methods

void ArmToHack::reset()
{
    lineNum = 0;

    labelMap.clear();
    labelFixupMap.clear();
    arrayBaseMap.clear();
}

void ArmToHack::write_line(const string &line)
{
    outputFile << line << endl;

    lineNum++;
}

void ArmToHack::translate(const string &inFileName, const string &outFileName)
{
    string tempFileName = inFileName + ".tmp";

    translateFirstPass(inFileName, tempFileName);
    lineNum = 0;
    translateSecondPass(tempFileName, outFileName);

    reset();

    // delete the tempFile from disc
    remove (tempFileName.c_str());
}

void ArmToHack::translateFirstPass(const string &inFileName, const string &outFileName)
{
    inputFile.open(inFileName);
    outputFile.open(outFileName);

    // initialize the stack
    translateSTACK(DEFAULT_STACK_ADDRESS);

    while (inputFile)
    {
        string curLine = read_line(inputFile);

        if (!curLine.empty() && curLine[0] != ';')
        {
            if (peek_first(curLine) != "END" && peek_second(curLine).empty())
            {
                string key = peek_first(curLine);
                string value = to_string(lineNum);

                labelMap[key] = value;
            }

            else
            {
                translate(curLine);
            }
        }
    }

    inputFile.close();
    outputFile.close();
}

void ArmToHack::translate(string &line)
{
    string token = peek_first(line);
    string dcdToken = peek_second(line);

    if (token == "MOV")
    {
        translateMOV(line);
    }

    else if (token == "ADD")
    {
        translateADD(line);
    }

    else if (token == "SUB")
    {
        translateSUB(line);
    }

    else if (token == "RSB")
    {
        translateRSB(line);
    }

    else if (token == "CMP")
    {
        translateCMP(line);
    }

    else if (token == "END")
    {
        translateEND(line);
    }

    else if (token[0] == 'B')
    {
        translateJumps(line);
    }

    else if (token == "STMDA")
    {
        translateSTMDA(line);
    }

    else if (token == "LDMIB")
    {
        translateLDMIB(line);
    }

    else if (token == "LDR")
    {
        translateLDR(line);
    }

    else if (token == "STR")
    {
        translateSTR(line);
    }

    else if (dcdToken == "DCD")
    {
        translateDCD(line);
    }

    else if (token == "ASR")
    {
        translateASR(line);
    }
}

void ArmToHack::translateMOV(string &line)
{
    extract_token(line);

    string dest = peek_first(line);
    string src = peek_second(line);

    // write_opr2
    write_oper2(src);

    // write_opr1 and do operation
    write_line("@" + regMap[dest]);
    write_line("M=D");

    // if dest is pc-equiv
    write_pcjump(dest);
}

void ArmToHack::translateADD(string &line)
{
    extract_token(line);

    string dest = extract_token(line);
    string opr1 = peek_first(line);
    string opr2 = peek_second(line);

    // write_opr2
    write_oper2(opr2);

    // write_oper1 and do the operation
    write_line("@" + regMap[opr1]);
    write_line("D=M+D");

    // store the sum(D) in dest
    write_line("@" + regMap[dest]);
    write_line("M=D");

    // if dest is pc-equiv
    write_pcjump(dest);
}

void ArmToHack::translateSUB(string &line)
{
    extract_token(line);

    string dest = extract_token(line);
    string opr1 = peek_first(line);
    string opr2 = peek_second(line);

    // write_opr2
    write_oper2(opr2);

    // write_oper1 and do the operation
    write_line("@" + regMap[opr1]);
    write_line("D=M-D");

    // store result(D) in dest
    write_line("@" + regMap[dest]);
    write_line("M=D");

    // if dest is pc-equiv
    write_pcjump(dest);
}

void ArmToHack::translateRSB(string &line)
{
    extract_token(line);

    string dest = extract_token(line);
    string opr1 = peek_first(line);
    string opr2 = peek_second(line);

    // write_opr2
    write_oper2(opr2);

    // write_oper1 and do the operation
    write_line("@" + regMap[opr1]);
    write_line("D=D-M");

    // store result(D) in dest
    write_line("@" + regMap[dest]);
    write_line("M=D");

    // if dest is pc-equiv
    write_pcjump(dest);
}

void ArmToHack::translateCMP(string &line)
{
    extract_token(line);

    string opr1 = peek_first(line);
    string opr2 = peek_second(line);

    // write_opr2
    write_oper2(opr2);

    // write_oper1 and do the operation
    write_line("@" + regMap[opr1]);
    write_line("D=M-D");
}

void ArmToHack::translateEND(string &line)
{
    int jumpLine = lineNum + 1;
    string address = to_string(jumpLine);

    // jump onto jump_line address cell unconditionally
    write_line("@" + address);
    write_line("0;JMP");
}

void ArmToHack::write_oper2(string &token)
{
    if (token[0] == 'R' || token == "FP" || token == "SP" || token == "LR" || token == "PC")
    {
        write_line("@" + regMap[token]);
        write_line("D=M");
    }

    else if (token[0] == '#')
    {
        strip(token, "#+");

        if (token[0] == '-')
        {
            strip(token, "-");

            write_line("@" + token);
            write_line("D=-A");
        }

        else
        {
            write_line("@" + token);
            write_line("D=A");
        }
    }
}

void ArmToHack::translateJumps(string &line)
{
    string jumpType = peek_first(line);
    string label = peek_second(line);
    string labelAddress = labelMap[label];

    if (jumpType == "BL")
    {
        // Save return address in LR (R14)
        
        write_line("@" + to_string(lineNum + 6)); // it takes 6 more lines to write equivalence of "BL" arm command!
        write_line("D=A");
        write_line("@14");
        write_line("M=D");
    }

    if (labelAddress.empty())
    {
        labelFixupMap[to_string(lineNum)] = label;
        write_line("@-1");
    }

    else
    {
        write_line("@" + labelAddress);
    }

    if (jumpType == "BL" || jumpType == "BAL")
    {
        write_line("0;JMP");
    }

    else
    {
        write_line("D;" + jumpMap[jumpType]);
    }
}

void ArmToHack::translateSecondPass(const string &inFileName, const string &outFileName)
{
    inputFile.open(inFileName);
    outputFile.open(outFileName);

    while (inputFile)
    {
        string curLine = read_line(inputFile);

        if (peek_first(curLine) == "@-1")
        {
            string label = labelFixupMap[to_string(lineNum)];
            write_line("@" + labelMap[label]);
        }

        else
        {
            write_line(curLine);
        }
    }

    inputFile.close();
    outputFile.close();
}

void ArmToHack::write_pcjump(const string &regRd)
{
    if (regMap[regRd] == regMap["PC"])
    {
        write_line("@15");
        write_line("A=M");
        write_line("0;JMP");
    }
}

void ArmToHack::translateSTACK(const string &address)
{
    write_line("@" + address);
    write_line("D=A");
    write_line("@" + regMap["SP"]);
    write_line("M=D");
}

void ArmToHack::translateSTMDA(string &line)
{
    extract_token(line);

    string base = extract_token(line);
    strip(base, "!");

    string regList = line;
    strip(regList, "{}");

    while (!regList.empty())
    {
        string curReg = extract_token(regList);

        // store curReg in D
        write_line("@" + regMap[curReg]);
        write_line("D=M");

        // store D in baseReg
        write_line("@" + regMap[base]);
        write_line("A=M");
        write_line("M=D");

        // decrease base(move up)
        write_line("@" + regMap[base]);
        write_line("M=M-1");
    }
}

void ArmToHack::translateLDMIB(string &line)
{
    extract_token(line);

    string base = extract_token(line);
    strip(base, "!");

    string regList = line;
    strip(regList, "{}");

    while (!regList.empty())
    {
        string curReg = extract_token_reverse(regList); // because curReg points to the last listed reg

        // increase base(move down)
        write_line("@" + regMap[base]);
        write_line("M=M+1");

        // load value from [base] into D
        write_line("@" + regMap[base]);
        write_line("A=M");
        write_line("D=M");

        // store D in curReg
        write_line("@" + regMap[curReg]);
        write_line("M=D");
    }
}

void ArmToHack::translateLDR(string &line)
{
    extract_token(line);

    string dest = extract_token(line);

    string src = line;

    if (src[0] == '=')
    {
        strip(src, "=");

        write_line("@" + arrayBaseMap[src]);
        write_line("D=A");
        write_line("@" + regMap[dest]);
        write_line("M=D");
    }

    else
    {
        strip(src, "[]");

        string base = extract_token(src);
        string index = extract_token(src);

        // computer final index & store src in D
        write_oper2(index);
        write_line("@" + regMap[base]);
        write_line("A=M+D");

        write_line("D=M");

        // store in dest
        write_line("@" + regMap[dest]);
        write_line("M=D");
    }

    // if dest is pc-equiv
    write_pcjump(dest);
}

void ArmToHack::translateSTR(string &line)
{
    extract_token(line);

    string src = extract_token(line);

    string dest = line;
    strip(dest, "[]");

    string base = extract_token(dest);
    string index = extract_token(dest);

    // compute final index
    write_oper2(index);
    write_line("@" + regMap[base]);
    write_line("D=M+D");

    // store index in temp/M[SP] cell
    write_line("@" + regMap["SP"]);
    write_line("A=M");
    write_line("M=D");

    // load src in D
    write_line("@" + regMap[src]);
    write_line("D=M");

    // store src/D in M[final address]
    write_line("@13");
    write_line("A=M");
    write_line("A=M");
    write_line("M=D");
}

void ArmToHack::translateDCD(string &line)
{
    string arrayName = extract_token(line);
    extract_token(line);
    arrayBaseMap[arrayName] = to_string(nextDCDAddress);

    string array = line;

    while (!array.empty())
    {
        string curValue = extract_token(array);
        strip(curValue, "+");

        if (curValue[0] == '-')
        {
            strip(curValue, "-");

            write_line("@" + curValue);
            write_line("D=-A");
        }

        else
        {
            write_line("@" + curValue);
            write_line("D=A");
        }

        write_line("@" + to_string(nextDCDAddress));
        write_line("M=D");

        nextDCDAddress++;
    }
}

void ArmToHack::translateASR(string &line)
{
    extract_token(line);

    string dest = extract_token(line);
    string shiftReg = extract_token(line);

    // set SP=[shiftReg] & result/SP-1 = 0
    write_line("@" + regMap[shiftReg]);
    write_line("D=M");
    write_line("@" + regMap["SP"]);
    write_line("A=M");
    write_line("M=D");

    write_line("A=A-1");
    write_line("M=0");

    // check condition/loop starts
    write_line("@" + regMap["SP"]);
    write_line("A=M");
    write_line("D=M");
    write_line("@2");
    write_line("D=D-A");
    write_line("@" + to_string(lineNum + 11));
    write_line("D;JLT");

    // inside loop
    write_line("@2");
    write_line("D=A");
    write_line("@" + regMap["SP"]);
    write_line("A=M");
    write_line("M=M-D");

    write_line("A=A-1");
    write_line("M=M+1");

    // jumpBack to loop
    write_line("@" + to_string(lineNum - 14));
    write_line("0;JMP");

    // END/put back from temp working cells to desired cells
    write_line("@" + regMap["SP"]);
    write_line("A=M-1");
    write_line("D=M");
    write_line("@" + regMap[dest]);
    write_line("M=D");

    // if dest is pc-equiv
    write_pcjump(dest);
}