/* includes */
#include <iostream>
#include <fstream>

/* namespaces */
using namespace std;

int getSystemPower()    
{
    int x;
    int current = 0;
    int voltage = 0;
    ifstream inFile;
    
    inFile.open("/sys/class/power_supply/BAT1/current_now");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    inFile >> current;
    inFile.close();

    inFile.open("/sys/class/power_supply/BAT1/voltage_now");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    inFile >> voltage;
    inFile.close();

    return current * voltage;
}