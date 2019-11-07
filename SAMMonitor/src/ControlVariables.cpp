#include <iostream> 
#include <list> 
#include <iterator> 

using namespace std; 

list<int> activeCPUs;
list<int> sleepCPUs;
int currentFreq;


int getActiveCPU(){
    if(sleepCPUs.size() > 0){
        int temp = activeCPUs.back();
        activeCPUs.pop_back();
        return temp;
    }
    else{
        return 0;
    }
}

int getsleepCPU(){
    if(sleepCPUs.size() > 0){
        int temp = sleepCPUs.back();
        sleepCPUs.pop_back();
        return temp;
    }
    else{
        return 0;
    }   
}

void addActive(int data){
    activeCPUs.push_front(data);
}

void addSleep(int data){
    sleepCPUs.push_front(data);
}

void initControlVariables(){
    addActive(1);
    addActive(2);
    addActive(3);
    currentFreq = 600;
}