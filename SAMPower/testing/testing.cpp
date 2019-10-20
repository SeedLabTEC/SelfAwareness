/* includes */
#include <iostream>
#include <executionManager.h>
#include <executionQueue.h>

/* namespaces */
using namespace std;

int main(){
    eqmodel temp1 =  eqmodel(POW,1,stopProcessor,0,2);
    eqmodel temp2 =  eqmodel(POW,2,initProcessor,0,2);
    push(temp1);
    push(temp2);
    runQueue();
    return 0;
}