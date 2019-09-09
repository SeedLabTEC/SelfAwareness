/* includes */
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

#include "../include/self-monitor.h"
#include "../include/env-monitor.h"   

/* namespaces */
using namespace std;

/*global vars*/
unsigned int microseconds = 1000000;

double env_power(){
    double temp = getSystemPower();
    return temp;
}

double self_power(){
    double temp = getPIDPower(123);
    return temp;
}

int main()
{
    while(1){
        double envpower = env_power();
        cout << "env-power: " << envpower << endl;

        double selfpower = self_power();
        cout << "self-power: " << selfpower << endl;
        
        usleep(microseconds);
    }
    return 0;
}