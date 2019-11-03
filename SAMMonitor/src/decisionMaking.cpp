/* includes */
#include <iostream>
#include <monitorParse.h>
#include <executionQueue.h>
#include <SAMModel.h>
#include <unistd.h>

using namespace std;

void writeQueue(int origin,int priority,int function,int pid,int processor){
    eqmodel temp1 =  eqmodel(origin,priority,function,pid,processor);
    push(temp1);
}

void powerDecision(float readPower){
    float upper = getPowerUpperLimit();
    float lower = getPowerLowerLimit();
    cout << "power: " << lower << endl;
    if(readPower > upper){
        cout << "upper power reached" << endl;
    }
    else if (readPower < lower){
        cout << "lower power reached" << endl;
    }
}

void takeDecision(){
    monitorData data = getreadData();
    cout << "readData: " << *data.power_porcent << endl;
    powerDecision(*data.power_porcent);
}

void runDecisionMaking(){
    startJson();
    while(1){
        takeDecision();
        usleep(1000000);
    }
}