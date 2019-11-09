#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string JSON_PATH =  "/usr/SAM/Model/";


int pid;
double upperPower;
double lowerPower;
int upperFreq;
int lowerFreq;
int upperCores;
int lowerCores;
double upperCPU;
double lowerCPU;
double upperMem;
double lowerMem;

void readJson(int ppid){
    FILE *fp;
    char str[1000];
    string filename = JSON_PATH + to_string(ppid) +".txt";
    fp = fopen(filename.c_str(), "r");
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


double getPowerUpperLimit(){
    return upperPower;
}

double getPowerLowerLimit(){
    return lowerPower;
}

double getFreqUpperLimit(){
    return upperFreq;
}

double getFreqLowerLimit(){
    return lowerFreq;
}

double getCoresUpperLimit(){
    return upperCores;
}

double getCoresLowerLimit(){
    return lowerCores;
}

double getCPUUpperLimit(){
    return upperCPU;
}

double getCPULowerLimit(){
    return lowerCPU;
}

double getMemUpperLimit(){
    return upperMem;
}

double getMemLowerLimit(){
    return lowerMem;
}
