#include "self-monitor.cpp"
#include <fstream>
#include <iostream>
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
#include <signal.h>
using namespace std;
int main(int argc, char **argv){
    double power = getPIDPower(atoi(argv[1]));
    printf("power %f",power);   
}