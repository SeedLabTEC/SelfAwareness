/* includes */
#include <iostream>
#include <monitorParse.h>
#include <executionQueue.h>
#include <SAMModel.h>
#include <unistd.h>
#include <logger.h>
#include <controlVariables.h>

using namespace std;

void writeQueue(int origin,int priority,int function,int pid,int processor){
    eqmodel temp1 =  eqmodel(origin,priority,function,pid,processor,0);
    push(temp1);
}

void powerDecision(float readPower, int pid){
    float upper = getPowerUpperLimit();
    float lower = getPowerLowerLimit();
    if(readPower > upper){
        //eqmodel temp = eqmodel(POW,1,stopProcessor,pid,1,0); // eqmodel(int porigin,int ppriority,int pfunction,int ppid,int proc,int pfreq)
        //push(temp);
        cout << "upper power reached" << endl;
        writelog("upper power reached for pid: " + to_string(pid));
    }
    else if (readPower < lower){
        //eqmodel temp = eqmodel(POW,1,initProcessor,pid,1,0); // eqmodel(int porigin,int ppriority,int pfunction,int ppid,int proc,int pfreq)
        //push(temp);
        cout << "lower power reached" << endl;
        writelog("lower power reached for pid: " + to_string(pid));
    }
}

void memDecision(float readMem, int pid){
    float upper = getMemUpperLimit();
    float lower = getMemLowerLimit();
    if(readMem > upper){
        //eqmodel temp = eqmodel(MEM,1,stopProcessor,pid,1,0); // eqmodel(int porigin,int ppriority,int pfunction,int ppid,int proc,int pfreq)
        //push(temp);
        cout << "upper mem reached" << endl;
        writelog("upper mem reached for pid: " + to_string(pid));
    }
    else if (readMem < lower){
        //eqmodel temp = eqmodel(MEM,1,initProcessor,pid,1,0); // eqmodel(int porigin,int ppriority,int pfunction,int ppid,int proc,int pfreq)
        //push(temp);
        cout << "lower mem reached" << endl;
        writelog("lower mem reached for pid: " + to_string(pid));
    }
}

void cpuDecision(float readCpu, int pid){
    float upper = getCPUUpperLimit();
    float lower = getCPULowerLimit();
    if(readCpu > upper){
        cout << "upper cpu reached" << endl;
        int cpu = getActiveCPU();
        eqmodel temp = eqmodel(CPU,1,stopProcessor,pid,cpu,0); // eqmodel(int porigin,int ppriority,int pfunction,int ppid,int proc,int pfreq)
        addSleep(cpu);
        push(temp);
        writelog("upper cpu reached for pid: " + to_string(pid));
    }
    else if (readCpu < lower){
        cout << "lower cpu reached" << endl;
        int cpu = getsleepCPU();
        eqmodel temp = eqmodel(CPU,1,initProcessor,pid,cpu,0); // eqmodel(int porigin,int ppriority,int pfunction,int ppid,int proc,int pfreq)
        addActive(cpu);
        push(temp);
        writelog("lower cpu reached for pid: " + to_string(pid));
    }
}

void takeDecision(){
    monitorData data = getreadData();
    powerDecision(*data.power_porcent,*data.pid);
    memDecision(*data.power_porcent,*data.pid);
    cpuDecision(*data.power_porcent,*data.pid);
}

void runDecisionMaking(int pid){
    readJson(pid);
    initControlVariables();
    while(1){
        takeDecision();
        usleep(1000000);
    }
}