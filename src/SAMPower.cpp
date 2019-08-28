/* includes */
#include <iostream>
#include "../include/self-monitor.h"   

/* namespaces */
using namespace std;

int main()
{
    int temp = getSystemPower();
    cout << temp << endl;
    return 0;
}