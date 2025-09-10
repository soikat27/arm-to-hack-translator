#ifndef ARM_TO_HACK_H
#define ARM_TO_HACK_H

#include <string>
#include <map>
#include <fstream>
#include "token_io.h"

class ArmToHack {

    private:
        ifstream inputFile;
        ofstream outputFile;

        int lineNum = 0;
        int nextDCDAddress = 16;

        map<string, string> regMap = { {"R0", "0"}, {"R1", "1"}, {"R2", "2"}, {"R3", "3"}, {"R4", "4"},
                                    {"R5", "5"}, {"R6", "6"}, {"R7", "7"}, {"R8", "8"}, {"R9", "9"},
                                    {"R10", "10"}, {"R11", "11"}, {"R12", "12"}, {"R13", "13"}, {"R14", "14"},
                                    {"R15", "15"}, {"FP", "12"}, {"SP", "13"}, {"LR", "14"}, {"PC", "15"}
                                };
        
        map<string, string> jumpMap = { {"BGT", "JGT"}, {"BEQ", "JEQ"}, {"BGE", "JGE"}, 
                                        {"BLT", "JLT"}, {"BNE", "JNE"}, {"BLE", "JLE"}, {"BAL", "JMP"},
                                };

        map<string, string> labelMap = {}; // back jump
        map<string, string> labelFixupMap = {}; // forward jump

        map<string, string> arrayBaseMap = {};

        const string DEFAULT_STACK_ADDRESS = "16380";

    public:
        //constructor
        ArmToHack ();
        
        //methods
        void reset();

        void write_line(const string& line);

        void translate(const string& inFileName, const string& outFileName);

        void translateFirstPass(const string& inFileName, const string& outFileName);
        
        void translate(string& line);
        
        void translateMOV(string& line);

        void translateADD(string& line);

        void translateSUB(string& line);

        void translateRSB(string& line);

        void translateCMP(string& line);

        void translateEND(string& line);

        // adding support for numeric constant

        void write_oper2(string& token);

        // add supports for backJump

        void translateJumps(string& line);

        void translateSecondPass(const string& inFileName, const string& outFileName);

        void write_pcjump(const string& regRd);

        void translateSTACK(const string &address);

        void translateSTMDA(string& line);

        void translateLDMIB(string& line);

        void translateLDR(string& line);

        void translateSTR(string& line);

        void translateDCD(string& line);

        void translateASR(string& line);
};

#endif