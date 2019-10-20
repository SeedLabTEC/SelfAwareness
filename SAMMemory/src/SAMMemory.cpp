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
#include <memoryMonitor.h>

using namespace std;
int main()
{
    memoryUse *memUse = new memoryUse();
    getProcessInfo(memUse,1913);
    cout << memUse->pid << " =pid\n";
    cout << memUse->useBytes << " =bytes\n";
    cout << memUse->usePercen << " =percentage\n";  
}