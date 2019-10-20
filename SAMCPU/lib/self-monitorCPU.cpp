/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sstream>
#include "../include/self-monitorCPU.h"

/* namespaces */
using namespace std;

/* functions */
double getCpuUsage(int pid)
{
    string dat = "top -p ";
    string spid=to_string(pid);
    string query=dat+spid+" -b -d 1 -n 1 > temp.txt";
    double x=0; 
    const char * cQuery = query.c_str();
    system(cQuery);
    FILE *fp;
    char str[1000];
    const char *filename = "temp.txt";
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 1;
    }
    while (fgets(str, 1000, fp) != NULL)
        ;
    char *ptr = strtok(str, " ");
    int cont = 0;
    char *res;
    system("rm -r temp.txt");
    while (ptr != NULL)
    {
        if (cont == 8)
        {
            res = ptr;
            break;
        }
        ptr = strtok(NULL, " ");
        cont++;
    }
  //  printf("Command used: %s\n", cQuery);
    printf("self-cpu: %s\n", res);
    writeResult(res);
    fclose(fp);
    x=atof(res);
    return x;
}

void writeResult(char *data)
{
    FILE *fp;
    fp = fopen("cpuOut.txt", "a");
    fprintf(fp, "%s\n", data);
    fclose(fp);
}