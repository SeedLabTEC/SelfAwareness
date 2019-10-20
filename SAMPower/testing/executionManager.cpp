/* includes */
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <executionManager.h>
#include <executionQueue.h>

int EXEC_STATUS = 1;

/* namespaces */
using namespace std;

void sleepProcessor(int num){
    cout << "durmiendo el procesador" << endl;
    string dat = "echo 0 | sudo tee /sys/devices/system/cpu/cpu";
    string spid=to_string(num);
    string query=dat+spid+"/online";
    const char * cQuery = query.c_str();
    system(cQuery);
}

void startProcessor(int num){
    string dat = "echo 1 | sudo tee /sys/devices/system/cpu/cpu";
    string spid=to_string(num);
    string query=dat+spid+"/online";
    const char * cQuery = query.c_str();
    system(cQuery);
}

void sleepProcess(int num){
    string dat = "kill -STOP ";
    string spid=to_string(num);
    string query=dat+spid;
    const char * cQuery = query.c_str();
    system(cQuery);
}

void moveProcess(int proc, int pid){
    string dat = "taskset -cp ";
    string spid=to_string(pid);
    string sproc=to_string(proc);
    string query=dat+sproc+ " "+spid;
    const char * cQuery = query.c_str();
    system(cQuery);
}

void runQueue(){
    while(EXEC_STATUS){
        eqmodel temp = pop();
        switch (temp.function){
            case stopProcessor:
                sleepProcessor(temp.processor);
                break;
            case initProcessor:
                startProcessor(temp.processor);
                break;
            case movePID:
                moveProcess(temp.pid,temp.processor);
                break;
            case stopPID:
                sleepProcess(temp.pid);
                break;
        }
        usleep(1000);
    }
}