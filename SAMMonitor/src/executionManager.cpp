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
    cout << "durmiendo el procesador" << endl;
    writelog("durmiendo el procesador number: " + to_string(num));
    string dat = "echo 0 | sudo tee /sys/devices/system/cpu/cpu";
    string spid = to_string(num);
    string query = dat + spid + "/online";
    const char *cQuery = query.c_str();
    system(cQuery);
}

void startProcessor(int num)
{
    cout << "iniciando el procesador" << endl;
    writelog("iniciando el procesador number: " + to_string(num));
    string dat = "echo 1 | sudo tee /sys/devices/system/cpu/cpu";
    string spid = to_string(num);
    string query = dat + spid + "/online";
    const char *cQuery = query.c_str();
    system(cQuery);
}

void sleepProcess(int num)
{
    cout << "Durmiendo proceso" << endl;
    writelog("Durmiendo proceso numero: " + to_string(num));
    string dat = "kill -STOP ";
    string spid = to_string(num);
    string query = dat + spid;
    const char *cQuery = query.c_str();
    system(cQuery);
}

void moveProcess(int proc, int pid)
{
    cout << "moviendo proceso" << endl;
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
    cout << "Seteando frecuencia minima" << endl;
    writelog("Seteando frecuencia "+ to_string(freq)+" minima number: " + to_string(num));
    string dat = "echo "+to_string(freq)+" | sudo tee /sys/devices/system/cpu/cpu";
    string spid = to_string(num);
    string query = dat + spid + "/cpufreq/scaling_min_freq";
    const char *cQuery = query.c_str(); 
    system(cQuery);
}

void setMaxFreq(int num, int freq)
{
    cout << "Seteando frecuencia minima" << endl;
    writelog("Seteando frecuencia "+ to_string(freq)+" minima number: " + to_string(num));
    string dat = "echo "+to_string(freq)+" | sudo tee /sys/devices/system/cpu/cpu";
    string spid = to_string(num);
    string query = dat + spid + "/cpufreq/scaling_max_freq";
    const char *cQuery = query.c_str(); 
    system(cQuery);
}

void runQueue()
{
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