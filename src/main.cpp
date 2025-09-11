#include "../include/ArmToHack.h"
#include <iostream>

using namespace std;

int main (int argc, char* argv[])
{
    if (argc != 3)
    {
        cout << "Invalid input! The program takes two arguments such as <input_file_name> <output_file_name>" << endl;
        return -1;
    }

    ArmToHack translator;

    translator.translate(argv[1], argv[2]);

    return 0;
}