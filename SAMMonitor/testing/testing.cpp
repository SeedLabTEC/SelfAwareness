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

double getPIDPower(int pid)
{
    //Info based on Raspberry pi 2 board
    float voltaje = 5;
    float max_current = 1.8;

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
    cout << "current freq: " << current_freq << endl;
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
    cout << "cache miss: " << cache_miss << endl;
    if(cache_miss == 0)
        cache_miss = 1;
    if(cache_miss > 0)
        cache_miss = 100;
    double power = (0.00008056 * (current_freq * cache_miss));
    power_porcent = 100*power / (max_current*voltaje);
    }catch(exception e){
        power_porcent = 0;
    }

    return abs(power_porcent);
}

int main(int argc, char **argv){
    int power = getPIDPower(atoi(argv[1]));
    cout << power << endl;
}