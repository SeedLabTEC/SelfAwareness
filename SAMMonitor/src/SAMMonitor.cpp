
#include <stdlib.h>
#include <monitor.h>
#include <executionEngine.h>
#include <logger.h>

using namespace std;  

bool main_flag = 1;

void setMainFlag(int state){
    main_flag = state;
}

int main(int argc, char **argv){
    generalUse *use = new generalUse();
    int pid = atoi(argv[1]);
    writelog("Process start with PID:" + to_string(pid));
    runThreads(pid);
    while(main_flag);
}