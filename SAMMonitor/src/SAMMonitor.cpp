
#include <stdlib.h>
#include <monitor.h>
#include <executionEngine.h>
#include <logger.h>
#include <executionQueue.h>

using namespace std;  

bool main_flag = 1;

void setMainFlag(int state){
    main_flag = state;
}

void setNormalState(int i){
     eqmodel temp = eqmodel(CPU,1,initProcessor,0,i,0);
     push(temp);
}

int main(int argc, char **argv){
    generalUse *use = new generalUse();
    int pid = atoi(argv[1]);
    setPID(pid);
    writelog("Process start with PID:" + to_string(pid));
    runThreads(pid);
    while(main_flag);
    
    for (size_t i = 0; i < 4; i++)
    {
        setNormalState(i);
    }
    
}