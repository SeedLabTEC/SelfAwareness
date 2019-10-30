
#include <stdlib.h>
#include <monitor.h>
#include <executionEngine.h>

using namespace std;

int main(int argc, char **argv){
    generalUse *use = new generalUse();
    int pid = atoi(argv[1]);
    runThreads(pid);
    while(1);
}