#include <iostream>
#include "admissionSys.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        cerr << "[ERROR] Wrong input format!" << endl;
        return 0;
    }

    admissionSys adm;

    adm.readFile(argv[1], argv[2]);
    adm.admit();
    adm.writeOutput(argv[3]);

    return 0;
}