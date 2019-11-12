/* includes */
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <executionManager.h>
#include <executionQueue.h>
#include <logger.h>

int EXEC_STATUS = 1;

/* namespaces */
using namespace std;

void sleepProcessor(int num)
{
    cout << "durmiendo el procesador: " << num << endl;
    writelog("durmiendo el procesador number: " + to_string(num));
    string dat = "echo 0 | tee /sys/devices/system/cpu/cpu";
    string spid = to_string(num);
    string query = dat + spid + "/online";
    const char *cQuery = query.c_str();
    system(cQuery);
}

void startProcessor(int num)
{
    cout << "iniciando el procesador: " << num << endl;
    writelog("iniciando el procesador number: " + to_string(num));
    string dat = "echo 1 | tee /sys/devices/system/cpu/cpu";
    string spid = to_string(num);
    string query = dat + spid + "/online";
    const char *cQuery = query.c_str();
    system(cQuery);
}

void sleepProcess(int num)
{
    cout << "Durmiendo proceso: " << num << endl;
    writelog("Durmiendo proceso numero: " + to_string(num));
    string dat = "kill -STOP ";
    string spid = to_string(num);
    string query = dat + spid;
    const char *cQuery = query.c_str();
    system(cQuery);
}

void moveProcess(int proc, int pid)
{
    cout << "moviendo proceso: " << pid << endl;
    writelog("moviendo proceso numero: " + to_string(pid));
    string dat = "taskset -cp ";
    string spid = to_string(pid);
    string sproc = to_string(proc);
    string query = dat + sproc + " " + spid;
    const char *cQuery = query.c_str();
    system(cQuery);
}

void setMinFreq(int num, int freq)
{
    cout << "Seteando frecuencia minima: " << freq << endl;
    writelog("Seteando frecuencia "+ to_string(freq)+" minima number: " + to_string(num));
    string dat = "echo "+to_string(freq)+" | tee /sys/devices/system/cpu/cpu";
    string spid = to_string(num);
    string query = dat + spid + "/cpufreq/scaling_min_freq";
    const char *cQuery = query.c_str(); 
    system(cQuery);
}

void setMaxFreq(int num, int freq)
{
    cout << "Seteando frecuencia minima: " << freq << endl;
    writelog("Seteando frecuencia "+ to_string(freq)+" minima number: " + to_string(num));
    string dat = "echo "+to_string(freq)+" | tee /sys/devices/system/cpu/cpu";
    string spid = to_string(num);
    string query = dat + spid + "/cpufreq/scaling_max_freq";
    const char *cQuery = query.c_str(); 
    system(cQuery);
}

void setCPUFreqStandards(){
    startProcessor(0);
    startProcessor(1);
    startProcessor(2);
    startProcessor(3);
    setMinFreq(1,700);
    setMaxFreq(1,800);
    setMinFreq(2,800);
    setMaxFreq(2,900);
    setMinFreq(3,600);
    setMaxFreq(3,700);
    setMinFreq(0,600);
    setMaxFreq(0,900);
}

void runQueue()
{
    setCPUFreqStandards();
    while (EXEC_STATUS)
    {
        if (size() > 0)
        {
            eqmodel temp = pop();
            switch (temp.function)
            {
            case stopProcessor:
                sleepProcessor(temp.processor);
                break;
            case initProcessor:
                startProcessor(temp.processor);
                break;
            case movePID:
                moveProcess(temp.pid, temp.processor);
                break;
            case stopPID:
                sleepProcess(temp.pid);
                break;
            case minFreq:
                setMinFreq(temp.pid,temp.freq);
                break;
            case maxFreq:
                setMaxFreq(temp.pid,temp.freq);
                break;
            }
            usleep(1000);
        }
    }
}