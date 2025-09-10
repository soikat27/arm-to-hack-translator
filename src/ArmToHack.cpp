#include "ArmToHack.h"

#include <string>
#include <iostream>
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

}

void ArmToHack::translateSecondPass(const string &inFileName, const string &outFileName)
{

}

void ArmToHack::write_pcjump(const string &regRd)
{

}

void ArmToHack::translateSTACK(const string &address)
{

}

void ArmToHack::translateSTMDA(string &line)
{
  
}

void ArmToHack::translateLDMIB(string &line)
{

}

void ArmToHack::translateLDR(string &line)
{

}

void ArmToHack::translateSTR(string &line)
{

}

void ArmToHack::translateDCD(string &line)
{

}

void ArmToHack::translateASR(string &line)
{

}