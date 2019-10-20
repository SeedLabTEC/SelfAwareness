/* includes */
#include <iostream>
#include <env-monitor.h> 
#include <self-monitor.h> 
#include <powerModel.h> 

/* namespaces */
using namespace std;

int main(){
    cout << "environment power: " <<  getSystemPower() << endl;
    cout << "pid power: " <<  getPIDPower(5515) << endl;
    return 0;
}