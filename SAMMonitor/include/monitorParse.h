struct monitorData{
    int* pid;
    float* mem_bytes;
    float* mem_porcent;
    float* cpu_porcent;
    float* power_porcent;
    int* date;
    int* processor;
    int* processorcount;
    monitorData(int* ppid, float* pmem_bytes, float* pmem_porcent,float* pcpu_porcent, float* ppower_porcent, int* pdate, int* pprocessor, int* pprocessorcount):
    pid(ppid),mem_bytes(pmem_bytes),mem_porcent(pmem_porcent),cpu_porcent(pcpu_porcent),power_porcent(ppower_porcent),date(pdate), processor(pprocessor), processorcount(pprocessorcount){};
};

void openFile();

void closeFile();

void readLine();

void runMonitorQueue(int pid);

monitorData getreadData();