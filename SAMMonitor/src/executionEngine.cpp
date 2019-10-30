/* includes */
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <executionManager.h>
#include <monitorParse.h>
#include <decisionMaking.h>

using namespace std;

void *startMonitorParse(void *pid){
    cout << "init monitor parse" << endl;
    int* current_pid = (int *) pid;
    cout << "pid: " << *current_pid << endl;
    runMonitorQueue(*current_pid);
}

void *startexecutionManager(void *threadid){
    cout << "init execution manager" << endl;
    runQueue();
}

void *startDecisionMaking(void *threadid){
    cout << "init decision making" << endl;
    runDecisionMaking();
}

void runThreads(int pid){
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    int t1_rc;
    int t2_rc;
    int t3_rc;
    t1_rc = pthread_create(&t1, NULL, startexecutionManager, (void *)1);
      
    if (t1_rc) {
        cout << "Error:unable to create thread," << t1_rc << endl;
        exit(-1);
    }

    t2_rc = pthread_create(&t2, NULL, startDecisionMaking, (void *)2);
      
    if (t2_rc) {
        cout << "Error:unable to create thread," << t2_rc << endl;
        exit(-1);
    }

    t3_rc = pthread_create(&t3, NULL, startMonitorParse, (void *) &pid);

    if (t3_rc) {
        cout << "Error:unable to create thread," << t3_rc << endl;
        exit(-1);
    }
}