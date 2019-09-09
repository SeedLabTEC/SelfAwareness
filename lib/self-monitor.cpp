/* includes */
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* namespaces */
using namespace std;

double getCPU(int pid)
{
    double data = system("top -p 21590 -b -d 1 -n 1 > test.txt");
    FILE *fp;
    char str[1000];
    char *filename = "test.txt";
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 1;
    }
    while (fgets(str, 1000, fp) != NULL){
    }
  char *ptr = strtok(str, " ");
    int cont=0;
    char *res;
  while(ptr != NULL)
  {
        if(cont==8)
            res=ptr;
    ptr = strtok(NULL, " ");
        cont++;
  }
    printf("CPU usage: %s\n", res);
    fclose(fp);
    return 0;
}

double getPIDPower(int pid)
{
    double cpu = getCPU(pid);
    return cpu;
}