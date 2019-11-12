/* includes */
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
//#include <self-monitor.h>

/* namespaces */
using namespace std;

double last_power_read = 0;

double getCPU(int pid)
{
    string dat = "top -p ";
    string spid=to_string(pid);
    string query=dat+spid+" -b -d 1 -n 1 > temp.txt";
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
    fclose(fp);
    return atof(res);
}

double getMem(int pid)
{
    string dat = "top -p ";
    string spid=to_string(pid);
    string query=dat+spid+" -b -d 1 -n 1 > temp.txt";
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
        if (cont == 9)
        {
            res = ptr;
            break;
        }
        ptr = strtok(NULL, " ");
        cont++;
    }
    fclose(fp);
    return atof(res);
}

void writeResult(double data,char* output)
{
    FILE *fp;
    fp = fopen(output, "a");
    fprintf(fp, "%f\n", data);
    fclose(fp);
}

double getPIDPower(int pid)
{
    //Info based on Raspberry pi 2 board
    float voltaje = 5;
    float max_current = 1.8;
    /*float min_current = 0.0017;
    float min_freq = 600;
    float max_freq = 900;
    float min_cm = 0;
    float max_cm = 100;*/

    //read freq
    system("cat /sys/devices/system/cpu/cpufreq/policy0/scaling_cur_freq > current_Freq.txt");
    FILE *fp;
    char str[100];
    const char *filename = "current_Freq.txt";
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return 1;
    }
    while (fgets(str, 100, fp) != NULL)
        ;
    char *ptr = strtok(str, " ");
    int current_freq = 0;
    sscanf(ptr,"%i",&current_freq);
    system("rm -r current_Freq.txt");
    fclose(fp);

    //read cache misses
    double power_porcent = 0;
    try{
    string verif_dat = "/proc/";
    string verif_spid=to_string(pid);
    string verif_query=verif_dat+verif_spid+"/io";
    FILE *fp_verif;
    fp_verif = fopen(verif_query.c_str(), "r");
    if (fp_verif == NULL)
    {
        return 0;
    }

    string dat = "cat /proc/";
    string spid=to_string(pid);
    string query=dat+spid+"/io > current_cm.txt";
    const char * cQuery = query.c_str();
    system(cQuery);
    fclose(fp_verif);
    FILE *fp2;
    char str2[100];
    const char *filename2 = "current_cm.txt";
    fp2 = fopen(filename2, "r");
    if (fp2 == NULL)
    {
        printf("Could not open file %s", filename2);
        return 1;
    }
    int rchar = 0;
    int read_bytes = 0;
    fgets(str2, 100, fp2);
    sscanf(str2,"rchar: %i",&rchar);
    for (size_t i = 0; i < 4; i++)
    {
       fgets(str2, 100, fp2);
    }
    sscanf(str2,"read_bytes: %i",&read_bytes);
    system("rm -r current_cm.txt");
    fclose(fp2);

    //by lineal regretion formula
    /**
     * p1 = (min_current*voltaje,0) = (1.75,0) ; se establece 0 como la nueva referencia para el valor menor
     * p2 = (max_current*voltaje,9) = (90000,9)
     * m = y2-y1/x2-x1 = 0.008056
     * y = mx + b ; b se elimina segun el nuevo marco de referencia, si no se cambia la referencia entonces b = 0.0017 
     **/
    current_freq = (current_freq / 1000);
    double cache_miss = (100*abs(read_bytes-rchar)/(rchar+read_bytes)); // REVISAR
    if(cache_miss == 0)
        cache_miss = 1;
    if(cache_miss > 0)
        cache_miss = 100;
    double power = (0.00008056 * (current_freq * cache_miss));
    power_porcent = 100*power / (max_current*voltaje);
    }catch(exception e){
        power_porcent = 0;
    }
    return power_porcent;
}

/**
 * returns lineal regretion ecuation constant in order to determine PID powers
 * */
double getPower()    
{
    string dat = "top";
    string query=dat+" -b -d 1 -n 1 > temp.txt";
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
    for (size_t i = 0; i < 7; i++)
    {
        fgets(str, 1000, fp);
    }
    int cont = 0;
    double temp_power = 0;
    for (size_t i = 0; i < 10; i++)
    {
        fgets(str, 1000, fp);
        char *ptr = strtok(str, " ");
        cont = 0;
        while (ptr != NULL)
        {
            if (cont == 0)
            {
                try{
                temp_power += getPIDPower(atoi(ptr));
                }
                catch(exception e){
                    temp_power += 0;
                }
                break; 
            }
            ptr = strtok(NULL, " ");
            cont++;
        }
    }
    system("rm -r temp.txt");

    temp_power = temp_power/10;

    temp_power = (temp_power+last_power_read)/2;

    last_power_read = temp_power;

    fclose(fp);
    
    return (temp_power);

}