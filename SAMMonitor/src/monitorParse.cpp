#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

using namespace std;

#define FILE_PATH "/home/rodolfo/self-awareness/SelfAwareness/SAMMonitor/bin/results/1511.1" 

ifstream file;
int fd;

//variables of readed file
int pid;
float mem_bytes;
float mem_porcent;
float cpu_porcent;
float power_porcent;
int date;
int last_read_date = 0;


void openFile(){
    file.open(FILE_PATH);
    if (!file.is_open())
        cout <<  "File could not be openned" << endl;    
}

void closeFile(){
    if (file.is_open())
        file.close();
}

void readLine(){
    openFile();
    std::string str; 
    int iterator = 1;
    while (std::getline(file, str) && iterator > 0) {
        sscanf(str.c_str(), "%i:%f:%f:%f:%f:%i", &pid,&mem_bytes,&mem_porcent,&cpu_porcent,&power_porcent,&date);
        if(date > last_read_date){
            last_read_date = date;
            cout << pid <<endl;
            iterator --;
        }
    }
    closeFile();
}

int mapRead()
{   
    fd = open(FILE_PATH, O_RDONLY, (mode_t)0600);
    
    if (fd == -1)
    {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }  

    struct stat fileInfo = {32};
    
    if (fstat(fd, &fileInfo) == -1)
    {
        perror("Error getting the file size");
        exit(EXIT_FAILURE);
    }
    
    if (fileInfo.st_size == 0)
    {
        fprintf(stderr, "Error: File is empty, nothing to do\n");
        exit(EXIT_FAILURE);
    }
    
    char *map = (char*) mmap(0, fileInfo.st_size, PROT_READ, MAP_SHARED, fd, 0);
    
    if (map == MAP_FAILED)
    {
        close(fd);
        perror("Error mmapping the file");
        exit(EXIT_FAILURE);
    }
    
    for (off_t i = 0; i < fileInfo.st_size/57; i++)
    {
        //sscanf(map, "%i:%f:%f:%f:%f:%i", &pid,&mem_bytes,&mem_porcent,&cpu_porcent,&power_porcent,&last_read_date);
        printf("Found character %c at %ji\n", map[i], (intmax_t)i);
        cout << pid <<endl;
    }
    
    // Don't forget to free the mmapped memory
    if (munmap(map, fileInfo.st_size) == -1)
    {
        close(fd);
        perror("Error un-mmapping the file");
        exit(EXIT_FAILURE);
    }

    // Un-mmaping doesn't close the file, so we still need to do that.
    close(fd);
    
    return 0;
}

int main(){
    while(1)
        readLine();

    return 0;
}
 