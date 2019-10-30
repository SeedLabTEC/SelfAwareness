/* includes */
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <SAMModel.h>

/* namespaces */
using namespace std;

double getPower()    
{
    //Info based on Raspberry pi 2 board
    float voltaje = 5;
    float min_current = 0.0017;
    float max_current = 1.8;
    float min_freq = 600;
    float max_freq = 900;
    float min_cm = 0;
    float max_cm = 100;
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
    
    //by lineal regretion formula
    /**
     * p1 = (min_current*voltaje,0) = (1.75,0) ; se establece 0 como la nueva referencia para el valor menor
     * p2 = (max_current*voltaje,9) = (90000,9)
     * m = y2-y1/x2-x1 = 0.0008056
     * y = mx + b ; b se elimina segun el nuevo marco de referencia, si no se cambia la referencia entonces b = 0.0017 
     * */
    double power = 0.00008056 * ((current_freq/1000)); //no se visualiza cache misses ya que no monitoreamos ningun proceso, solo el procesador.
    double power_porcent = 100*power / (max_current*voltaje);

    return power_porcent;

}

double getPIDPower(int pid)
{
    //Info based on Raspberry pi 2 board
    float voltaje = 5;
    float min_current = 0.0017;
    float max_current = 1.8;
    float min_freq = 600;
    float max_freq = 900;
    float min_cm = 0;
    float max_cm = 100;

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

    //read cache misses
    string dat = "sudo cat /proc/";
    string spid=to_string(pid);
    string query=dat+spid+"/io > current_cm.txt";
    const char * cQuery = query.c_str();
    system(cQuery);
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


    //by lineal regretion formula
    /**
     * p1 = (min_current*voltaje,0) = (1.75,0) ; se establece 0 como la nueva referencia para el valor menor
     * p2 = (max_current*voltaje,9) = (90000,9)
     * m = y2-y1/x2-x1 = 0.008056
     * y = mx + b ; b se elimina segun el nuevo marco de referencia, si no se cambia la referencia entonces b = 0.0017 
     **/
    current_freq = (current_freq / 1000);
    double cache_miss = (100*(read_bytes)/(rchar)); // REVISAR
    if(cache_miss == 0)
        cache_miss = 1;
    if(cache_miss > 0)
        cache_miss = 100;
    double power = (0.00008056 * (current_freq * cache_miss));
    double power_porcent = 100*power / (max_current*voltaje);
    return power_porcent;
}

int main(){
<<<<<<< HEAD
    //cout << getPower() << endl;
    //cout << getPIDPower(8051) << endl;
    cout << getCPULowerLimit() << endl;
=======
    cout << getPower() << endl;
    cout << getPIDPower(23996) << endl;
>>>>>>> 0e2afa6f575025dd9d16c9dead151c1dfeb95a6b
    return 0;
}