/* includes */
#include <iostream>
#include <fstream>
#include <logger.h>

#define LOG_PATH "/var/log/SAM/results/executionEngine.txt"

/* namespaces */
using namespace std;

bool writelog(string data){
  ofstream file;
  file.open (LOG_PATH, std::ofstream::out | ofstream::app);
  file << data << endl;
  file.close();
  return 0;
}