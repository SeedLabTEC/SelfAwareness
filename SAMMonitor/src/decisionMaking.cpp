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

void powerDecision(float readPower, int pid, int proccesorcount)
{
    float upper = getPowerUpperLimit();
    float lower = getPowerLowerLimit();
    int priority = getPriority1();
    if (priority == priority_power)
    {
        if (readPower > upper)
        {
            cout << "max cpu reached" << endl;
            if (getCurrentFreq() != 600)
            {
                for (size_t i = 0; i < proccesorcount; i++)
                {
                    eqmodel temp = eqmodel(CPU, 1, maxFreq, pid, i, 600);
                    eqmodel temp1 = eqmodel(CPU, 1, minFreq, pid, i, 600);
                    push(temp);
                    push(temp1);
                }
                setCurrentFreq(600);
            }
            else
            {
                cout << "not more actions could be make" << endl;
            }
        }
        else if (readPower < lower)
        {
            cout << "min cpu reached" << endl;
        }
    }
}

void memDecision(float readMem, int pid, int proccesorcount)
{
    float upper = getMemUpperLimit();
    float lower = getMemLowerLimit();
    int priority = getPriority1();
    if (priority == priority_mem)
    {
        if (readMem > upper)
        {
            cout << "max cpu reached" << endl;
        }
        else if (readMem < lower)
        {
            cout << "min cpu reached" << endl;
            if (getCurrentFreq() != 900)
            {
                for (size_t i = 0; i < proccesorcount; i++)
                {
                    eqmodel temp = eqmodel(CPU, 1, maxFreq, pid, i, 900);
                    eqmodel temp1 = eqmodel(CPU, 1, minFreq, pid, i, 900);
                    push(temp);
                    push(temp1);
                }
                setCurrentFreq(900);
            }
            else
            {
                cout << "not more actions could be make" << endl;
            }
        }
    }
}

void cpuDecision(float readCpu, int pid, int proccesorcount)
{
    float upper = getCPUUpperLimit();
    float lower = getCPULowerLimit();
    int priority = getPriority1();
    if (priority == priority_cpu)
    {
        if (readCpu > upper)
        {
            cout << "max cpu reached" << endl;
            if (getCurrentFreq() != 600)
            {
                for (size_t i = 0; i < proccesorcount; i++)
                {
                    eqmodel temp = eqmodel(CPU, 1, maxFreq, pid, i, 600);
                    eqmodel temp1 = eqmodel(CPU, 1, minFreq, pid, i, 600);
                    push(temp);
                    push(temp1);
                }
                setCurrentFreq(600);
            }
            else
            {
                cout << "not more actions could be make" << endl;
            }
        }
        else if (readCpu < lower)
        {
            cout << "min cpu reached" << endl;
            if (getCurrentFreq() != 900)
            {
                for (size_t i = 0; i < proccesorcount; i++)
                {
                    eqmodel temp = eqmodel(CPU, 1, maxFreq, pid, i, 900);
                    eqmodel temp1 = eqmodel(CPU, 1, minFreq, pid, i, 900);
                    push(temp);
                    push(temp1);
                }
                setCurrentFreq(900);
            }
            else
            {
                cout << "not more actions could be make" << endl;
            }
        }
    }
}

void takeDecision()
{
    monitorData data = getreadData();
    powerDecision(*data.power_porcent, *data.pid, *data.processorcount);
    memDecision(*data.power_porcent, *data.pid, *data.processorcount);
    cpuDecision(*data.power_porcent, *data.pid, *data.processorcount);
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
        usleep(2000000);
    }
}