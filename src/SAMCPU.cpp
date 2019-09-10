/* includes */
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

#include "../include/self-monitorCPU.h"
//#include "../include/env-monitorCPU.h"   

/* namespaces */
using namespace std;

/*global vars*/
#define microseconds 1000000

double env_cpu(){
    return 0;
}

double self_cpu(){
    double temp = getCpuUsage(4407);
    return temp;
}

int main()
{
    cout.precision(3);
    while(1){
        double envcpu = env_cpu();
        cout << "env-cpu: " << envcpu << endl;
        double selfcpu = self_cpu();
        usleep(microseconds);
    }
    return 0;
}