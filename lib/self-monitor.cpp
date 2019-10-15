/* includes */
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <self-monitor.h>

/* namespaces */
using namespace std;

double getCPU(int pid)
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
    //system("rm -r temp.txt");
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
    writeResult(res,"powerCpu.txt");
    fclose(fp);
    x=atof(res);
    return x;
}

double getMem(int pid)
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
    //system("rm -r temp.txt");
    while (ptr != NULL)
    {
        if (cont == 9)
        {
            res = ptr;
            break;
        }
        ptr = strtok(NULL, " ");
        cont++;
    }
    writeResult(res,"powerMem.txt");
    fclose(fp);
    x=atof(res);
    return x;
}

void writeResult(char *data,char* output)
{
    FILE *fp;
    fp = fopen(output, "a");
    fprintf(fp, "%s\n", data);
    fclose(fp);
}

double getPower()    
{
    int x;
    int current = 0;
    int voltage = 0;
    ifstream inFile;
    
    inFile.open("/sys/class/power_supply/BAT1/current_now");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    inFile >> current;
    inFile.close();

    inFile.open("/sys/class/power_supply/BAT1/voltage_now");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    inFile >> voltage;
    inFile.close();

    double newCurrent = (double)current/(double)1000000;
    double newVoltage = (double)voltage/(double)1000000;

    return newCurrent * newVoltage;
}

double getPIDPower(int pid)
{
    double cpu = getMem(pid);
    double mem = getMem(pid);
    double power = getPower();
    double temp_porc = cpu * mem;
    double pidPower = (temp_porc * power) / 100;
    return pidPower;
}