/* includes */
#include <iostream>
#include <fstream>
#include <env-monitor.h>

/* namespaces */
using namespace std;

double getSystemPower()    
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

    double newCurrent = (double)current/(double)1000000;
    double newVoltage = (double)voltage/(double)1000000;

    return newCurrent * newVoltage;
}