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

}

void ArmToHack::translateFirstPass(const string &inFileName, const string &outFileName)
{

}

void ArmToHack::translate(string &line)
{

}

void ArmToHack::translateMOV(string &line)
{

}

void ArmToHack::translateADD(string &line)
{

}

void ArmToHack::translateSUB(string &line)
{

}

void ArmToHack::translateRSB(string &line)
{

}

void ArmToHack::translateCMP(string &line)
{

}

void ArmToHack::translateEND(string &line)
{

}

void ArmToHack::write_oper2(string &token)
{

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