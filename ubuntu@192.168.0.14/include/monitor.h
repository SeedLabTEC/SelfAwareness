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

struct generalUse {
  int pid;
  double memPercen;
  double memBytes;
  double usePower;
  double cpuPercen;
  string date;
  bool error;
};

bool checkRunning(int pid);
void getUsageNow(int pid,struct generalUse *use);
bool recordProcess(int pid,struct generalUse *use);
void monitorProcess(int pid);
void printed();
bool saveRecord(struct generalUser *use);
