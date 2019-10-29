struct monitorData{
    int* pid;
    float* mem_bytes;
    float* mem_porcent;
    float* cpu_porcent;
    float* power_porcent;
    int* date;
    monitorData(int* ppid, float* pmem_bytes, float* pmem_porcent,float* pcpu_porcent, float* ppower_porcent, int* pdate):
    pid(ppid),mem_bytes(pmem_bytes),mem_porcent(pmem_porcent),cpu_porcent(pcpu_porcent),power_porcent(ppower_porcent),date(pdate){};
};

void openFile();

void closeFile();

void readLine();

void runMonitorQueue();

monitorData getreadData();