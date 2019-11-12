/* includes */
#include <iostream>
#include <fstream>
#include <logger.h>

#define LOG_PATH "/var/log/SAM/results/"

/* namespaces */
using namespace std;

int PID_log = 0;

void setPID(int pid){
  PID_log = pid;
}

bool writelog(string data){
  ofstream file;
  file.open (LOG_PATH + to_string(PID_log) + ".logger", std::ofstream::out | ofstream::app);
  file << data << endl;
  file.close();
  return 0;
}

bool writelogResults(string data){
  ofstream file;
  file.open (LOG_PATH + to_string(PID_log) + ".results", std::ofstream::out | ofstream::app);
  file << data << endl;
  file.close();
  return 0;
}