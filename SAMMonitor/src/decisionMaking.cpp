/* includes */
#include <iostream>
#include <monitorParse.h>
#include <executionQueue.h>
#include <SAMModel.h>
#include <unistd.h>
#include <logger.h>
#include <controlVariables.h>

using namespace std;

int currentFlow = 0; // 0 = initital flow for active / 1 = initial flow for sleep

void writeQueue(int origin, int priority, int function, int pid, int processor, int freq)
{
    eqmodel temp1 = eqmodel(origin, priority, function, pid, processor, freq);
    push(temp1);
}

enum dicitionTypes
{
    sleepProc = 0,
    upperMovePid = 1,
    startProc = 2,
    lowerMovePid = 3
};

enum UserPriority
{
    priority_cpu = 0,
    priority_mem = 1,
    priority_power = 2,
};

int decitionHelper(bool isUpper)
{

    int sizeActive = getActiveSize();
    int sizeSleep = getSleepSize();

    if (isUpper)
    { //come from reach upper
        if (sizeActive > 0)
        {
            if (getCurrentProc() == 1)
            {
                return sleepProc; //sleep proc
            }
            else
            {
                return upperMovePid; //movepid
            }
        }
    }
    else
    {
        if (sizeSleep > 0)
        {
            if (getCurrentProc() == 3)
            {
                return startProc; //start proc
            }
            else
            {
                return lowerMovePid; //movepid
            }
        }
    }
}

void powerDecision(float readPower, int pid)
{
    float upper = getPowerUpperLimit();
    float lower = getPowerLowerLimit();
    int priority = getPriority1();
    if (priority == priority_power)
    {
        if (readPower > upper)
        {
            //eqmodel temp = eqmodel(POW,1,stopProcessor,pid,1,0); // eqmodel(int porigin,int ppriority,int pfunction,int ppid,int proc,int pfreq)
            //push(temp);
            cout << "upper power reached" << endl;
            writelog("upper power reached for pid: " + to_string(pid));
        }
        else if (readPower < lower)
        {
            //eqmodel temp = eqmodel(POW,1,initProcessor,pid,1,0); // eqmodel(int porigin,int ppriority,int pfunction,int ppid,int proc,int pfreq)
            //push(temp);
            cout << "lower power reached" << endl;
            writelog("lower power reached for pid: " + to_string(pid));
        }
    }
}

void memDecision(float readMem, int pid)
{
    float upper = getMemUpperLimit();
    float lower = getMemLowerLimit();
    int priority = getPriority1();
    if (priority == priority_mem)
    {
        if (readMem > upper)
        {
            //eqmodel temp = eqmodel(MEM,1,stopProcessor,pid,1,0); // eqmodel(int porigin,int ppriority,int pfunction,int ppid,int proc,int pfreq)
            //push(temp);
            cout << "upper mem reached" << endl;
            writelog("upper mem reached for pid: " + to_string(pid));
        }
        else if (readMem < lower)
        {
            //eqmodel temp = eqmodel(MEM,1,initProcessor,pid,1,0); // eqmodel(int porigin,int ppriority,int pfunction,int ppid,int proc,int pfreq)
            //push(temp);
            cout << "lower mem reached" << endl;
            writelog("lower mem reached for pid: " + to_string(pid));
        }
    }
}

void cpuDecision(float readCpu, int pid)
{
    float upper = getCPUUpperLimit();
    float lower = getCPULowerLimit();
    int priority = getPriority1();
    if (priority == priority_cpu)
    {
        if (readCpu > upper)
        {
            int flow = decitionHelper(true);
            cout << "upper cpu reached" << endl;
            writelog("upper cpu reached for pid: " + to_string(pid));
            if (flow == sleepProc)
            {
                int cpu = getActiveCPU();
                eqmodel temp = eqmodel(CPU, 1, stopProcessor, pid, cpu, 0); // eqmodel(int porigin,int ppriority,int pfunction,int ppid,int proc,int pfreq)
                addSleep(cpu);
                push(temp);
            }
            else if (flow == upperMovePid)
            {
                eqmodel temp = eqmodel(CPU, 1, movePID, pid, 1, 0);
                setCurrentProc(1);
                push(temp);
            }
            else
            {
                cout << "no more actions could be bound for pid: " << pid << endl;
                writelog("no more actions could be bound for pid: " + to_string(pid));
            }
        }
        else if (readCpu < lower)
        {
            cout << "lower cpu reached" << endl;
            writelog("lower cpu reached for pid: " + to_string(pid));
            int flow = decitionHelper(false);
            if (flow == startProc)
            {
                int cpu = getsleepCPU();
                eqmodel temp = eqmodel(CPU, 1, initProcessor, pid, cpu, 0); // eqmodel(int porigin,int ppriority,int pfunction,int ppid,int proc,int pfreq)
                addActive(cpu);
                push(temp);
            }
            else if (flow == lowerMovePid)
            {
                eqmodel temp = eqmodel(CPU, 1, movePID, pid, 3, 0);
                setCurrentProc(3);
                push(temp);
            }
            else
            {
                cout << "no more actions could be bound for pid: " << pid << endl;
                writelog("no more actions could be bound for pid: " + to_string(pid));
            }
        }
    }
}

void takeDecision()
{
    monitorData data = getreadData();
    powerDecision(*data.power_porcent, *data.pid);
    memDecision(*data.power_porcent, *data.pid);
    cpuDecision(*data.power_porcent, *data.pid);
}

void runDecisionMaking(int pid)
{
    readJson(pid);
    initControlVariables();
    eqmodel temp = eqmodel(GENERAL, 100, movePID, pid, 0, 0); // eqmodel(int porigin,int ppriority,int pfunction,int ppid,int proc,int pfreq)
    push(temp);
    while (1)
    {
        takeDecision();
        usleep(1000000);
    }
}