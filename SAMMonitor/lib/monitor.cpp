#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <syslog.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <signal.h>
//#include <monitor.h>
#include "memoryMonitor.cpp"
#include "self-monitor.cpp"
#include "self-monitorCPU.cpp"
#include <time.h>
#include <unistd.h>

using namespace std;

struct generalUse {
  int pid;
  double memPercen;
  double memBytes;
  double usePower;
  double cpuPercen;
  string date;
  bool error;
  int processor;
};


const unsigned int microseconds = 500000;
// bool checkRunning(int pid){
//     string spid = to_string(pid);
//     char command[]= "ps -p ";
//     strcat(command, spid.c_str());
//     int status = system(command);
//     if(status==0){
//         return true;
//     }
//     return false;
// }

bool checkRunning(int pid){
    if (0 == kill(pid, 0))
    {
        return true;
    }
    return false;
}

int getProcessor(int pid){

}

double cpuForPc(double cpu){
    int temRange = (int)(cpu/100);
    temRange++;
    double resCpu = cpu/temRange;
    return resCpu;
}

void getUsageNow(int pid,struct generalUse *use){
    memoryUse *memUse = new memoryUse();
    getProcessInfo(memUse,pid);
    double cpuUsage = getCpuUsage(pid);
    cpuUsage = cpuForPc(cpuUsage);
    double powerUse = getPIDPower(pid);
    use->memPercen = memUse->usePercen;
    use->memBytes = memUse->useBytes;
    use->pid=pid;
    use->date = to_string(time(0)%60);
    use->cpuPercen = cpuUsage;
    use->usePower = powerUse;
    use->processor = memUse->processor;
}




bool saveRecord(struct generalUse *use){
    // open a file in write mode.
   ofstream outfile;
   ofstream history;
   string path = "/var/log/SAM/results/";
   string name = path+ to_string(use->pid)+".txt";
   string nameHisotry = path+ to_string(use->pid)+"all.txt";
   outfile.open(name);
   history.open(nameHisotry,std::ofstream::out | std::ofstream::app);
   // write inputted data into the file.
   string data = to_string(use->pid)+":"+to_string(use->memBytes)+":"+to_string(use->memPercen)+":"+to_string(use->cpuPercen)+":"+to_string(use->processor)+":"+to_string(use->usePower)+":"+use->date+":"+to_string(1);
   outfile << data << endl;
   history << data << endl;
   outfile.close();
   history.close();
   return true;
}
bool saveEnd(struct generalUse *use){
    // open a file in write mode.
   ofstream outfile;
   ofstream history;
   string path = "/var/log/SAM/results/";
   string name = path+ to_string(use->pid)+".txt";
   string nameHisotry = path+ to_string(use->pid)+"all.txt";
   outfile.open(name);
   history.open(nameHisotry,std::ofstream::out | std::ofstream::app);
   // write inputted data into the file.
   string data = to_string(use->pid)+":"+to_string(use->memBytes)+":"+to_string(use->memPercen)+":"+to_string(use->cpuPercen)+":"+to_string(use->processor)+":"+to_string(use->usePower)+":"+use->date+":"+to_string(0);
   outfile << data << endl;
   history << data << endl;
   outfile.close();
   history.close();
   return true;
}

bool recordProcess(int pid,struct generalUse *use){
    if(checkRunning(pid)){
        getUsageNow(pid,use);
        saveRecord(use);
        printf("monitoring\n");
        return true;
    }
    use->cpuPercen=0;
    use->memBytes=0;
    use->memPercen=0;
    use->pid=pid;
    use->usePower=0;
    use->date= to_string(time(0)%60);
    saveEnd(use);
    printf("Process not running\n");
    return false;
}

void monitorProcess(int pid){
    generalUse *use = new generalUse;
    bool status = recordProcess(pid,use);
    while(status){
        status = recordProcess(pid,use);
        usleep(microseconds);
    }
    printf("process end\n");
    return;
}

void printed(){
    printf("test");
}