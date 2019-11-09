//#include<memoryMonitor.h>
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
  int processor;
  int totalProcessors;
  bool error;
};

bool findSelfMem(int pid)
{
  char arr_pid [10];
  sprintf(arr_pid, "%d", pid);
  char name[] = "temMemory"; 
  char command[100]="bash bash/getMemory.sh ";
  strcat(command, arr_pid);
  strcat(command, " ");
  strcat(command,name);
  int status = system(command);
  if(status==0){
      return true;
  }
  return false;
}

string fileReader(){
  string line;
  ifstream myfile ("results/temMemory.txt");
  if (myfile.is_open())
  {
    getline (myfile,line);
    myfile.close();
    return line;
  }
  printf("Unable to open file");
  return line;
}

bool deletefile(){
    if( remove( "results/temMemory.txt" ) != 0 )
    {
        perror( "Error deleting file" );
        return false;
    }
    return true;
}

vector<string> handleData(string rawInfo, char delimeter){
    stringstream ss(rawInfo);
    string item;
    vector<string> splittedStrings;
    while (getline(ss, item, delimeter))
    {
       splittedStrings.push_back(item);
    }
    return splittedStrings;
}

void getStructuredInfo(struct memoryUse *data,vector<string> processInfo){
    int pid = atoi(processInfo.at(0).c_str());
    double useBytes = atof(processInfo.at(1).c_str());
    double usePercen = atof(processInfo.at(2).c_str()); 
    int processor = atoi(processInfo.at(3).c_str());
    int total = atoi(processInfo.at(4).c_str());
    data->pid = pid;
    data->useBytes = useBytes;
    data->usePercen = usePercen;
    data->error = false;
    data->processor = processor;
    data->totalProcessors = total;
}

void getProcessInfo(struct memoryUse *data, int pid){
    bool response = findSelfMem(pid);
    if(response){
        string rawInfo = fileReader();
        if(rawInfo.empty()){
            printf("File data not found");
            return ;
        }
        vector<string> processedInfo = handleData(rawInfo,':');
        getStructuredInfo(data,processedInfo);  
        deletefile(); 
    }
    else
    {
        data->error=true;
        printf("An error occur");
    }
}


