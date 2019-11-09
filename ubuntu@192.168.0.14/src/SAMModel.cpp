#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string JSON_PATH =  "/usr/SAM/Model/";


int model_pid;
float model_upperPower;
float model_lowerPower;
int model_upperFreq;
int model_lowerFreq;
int model_upperCores;
int model_lowerCores;
float model_upperCPU;
float model_lowerCPU;
float model_upperMem;
float model_lowerMem;

void readJson(int ppid){
    FILE *fp;
    char str[1000];
    string filename = JSON_PATH + to_string(ppid) +".txt";
    fp = fopen(filename.c_str(), "r");
    if (fp == NULL)
    {
        printf("Could not open file %s\n", filename.c_str());
    }
    else{
        while (fgets(str, 1000, fp) != NULL)
            ;
        sscanf(str, "%i:%f:%f:%i:%i:%i:%i:%f:%f:%f:%f", &model_pid,&model_upperPower,&model_lowerPower,&model_upperFreq,&model_lowerFreq,&model_upperCores,&model_lowerCores,&model_upperCPU,&model_lowerCPU,&model_upperMem,&model_lowerMem); 
        /*cout << str << endl;
        cout << model_pid << endl;
        cout << model_upperPower << endl;
        cout << model_lowerPower << endl;
        cout << model_upperFreq << endl;
        cout << model_lowerFreq << endl;
        cout << model_upperCores << endl;
        cout << model_lowerCores << endl;
        cout << model_upperCPU << endl;
        cout << model_lowerCPU << endl;
        cout << model_upperMem << endl;
        cout << model_lowerMem << endl;
        cout << "end" <<endl;*/
    }
}


float getPowerUpperLimit(){
    return model_upperPower;
}

float getPowerLowerLimit(){
    return model_lowerPower;
}

float getFreqUpperLimit(){
    return model_upperFreq;
}

float getFreqLowerLimit(){
    return model_lowerFreq;
}

float getCoresUpperLimit(){
    return model_upperCores;
}

float getCoresLowerLimit(){
    return model_lowerCores;
}

float getCPUUpperLimit(){
    return model_upperCPU;
}

float getCPULowerLimit(){
    return model_lowerCPU;
}

float getMemUpperLimit(){
    return model_upperMem;
}

float getMemLowerLimit(){
    return model_lowerMem;
}
