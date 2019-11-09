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

using namespace std;

struct memoryUse {
  int pid;
  double usePercen;
  double useBytes;
  bool error;
};

bool findSelfMem(int pid);
string fileReader();
bool deletefile();
vector<string> handleData(string rawInfo, char delimeter);
void getStructuredInfo(struct memoryUse *data,vector<string> processInfo);
void getProcessInfo(struct memoryUse *data, int pid);