/* includes */
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string>


/* namespaces */
using namespace std;

int pid;
float upperPower;
float lowerPower;
int upperFreq;
int lowerFreq;
int upperCores;
int lowerCores;
float upperCPU;
float lowerCPU;
float upperMem;
float lowerMem;

void readConf(){
    FILE *fp;
    char str[1000];
    const char *filename = "SAMModel.txt";
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
    }
    else{
        while (fgets(str, 1000, fp) != NULL)
            ;
        sscanf(str, "%i:%f:%f:%i:%i:%i:%i:%f:%f:%f:%f", &pid,&upperPower,&lowerPower,&upperFreq,&lowerFreq,&upperCores,&lowerCores,&upperCPU,&lowerCPU,&upperMem,&lowerMem); 
        cout << "line: " << str << endl;
        cout << "pid: " << pid << endl;
        cout << "upper power: " << upperPower << endl;
        cout << "lower power: " << lowerPower << endl;
    }
    
}

int main(){
    //cout << getPower() << endl;
    //cout << getPIDPower(8051) << endl;
    //cout << getCPULowerLimit() << endl;
    readConf();
    return 0;
}