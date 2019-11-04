/* includes */
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <executionManager.h>
#include <monitorParse.h>
#include <decisionMaking.h>
#include <logger.h>
#include <mutex> 

using namespace std;

mutex mtx;

void *startMonitorParse(void *pid){
    int* current_pid = (int *) pid;
    mtx.lock();
    writelog("init monitor parse for pid: " + to_string(*current_pid));
    mtx.unlock();
    runMonitorQueue(*current_pid);
}

void *startexecutionManager(void *pid){
    int* current_pid = (int *) pid;
    mtx.lock();
    writelog("init execution manager for pid: " + to_string(*current_pid));
    mtx.unlock();
    runQueue();
}

void *startDecisionMaking(void *pid){
    int* current_pid = (int *) pid;
    mtx.lock();
    writelog("init decision making for pid: " + to_string(*current_pid));
    mtx.unlock();
    runDecisionMaking(*current_pid);
}

void runThreads(int pid){
    pthread_t t1;
    pthread_t t2;
    pthread_t t3;
    int t1_rc;
    int t2_rc;
    int t3_rc;
    t1_rc = pthread_create(&t1, NULL, startexecutionManager, (void *) &pid);
      
    if (t1_rc) {
        cout << "Error:unable to create thread of execution manager" << t1_rc << endl;
        writelog("Error:unable to create thread of execution manager");
        exit(-1);
    }

    t2_rc = pthread_create(&t2, NULL, startDecisionMaking, (void *) &pid);
      
    if (t2_rc) {
        cout << "Error:unable to create thread of DecitionMaking" << t2_rc << endl;
        writelog("Error:unable to create thread of DecitionMaking");
        exit(-1);
    }

    t3_rc = pthread_create(&t3, NULL, startMonitorParse, (void *) &pid);

    if (t3_rc) {
        cout << "Error:unable to create thread of monitor Parse" << t3_rc << endl;
        writelog("Error:unable to create thread of monitor Parse");
        exit(-1);
    }
}