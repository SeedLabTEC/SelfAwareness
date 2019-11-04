// Execution Queue data model

enum Origin{
    POW = 0,
    CPU = 1,
    MEM = 2,
};

enum Functions{
    movePID = 0,
    stopProcessor = 1,
    initProcessor = 2,
    stopPID = 3,
    minFreq = 4,
    maxFreq = 5

};

struct eqmodel
{
    int origin; // origin ? power = 0, cpu = 1, mem = 2
    int priority; //define the priority of execution in queue
    int function; // define function to execute
    int pid;
    int processor;
    int freq;

    eqmodel(int porigin,int ppriority,int pfunction,int ppid,int proc, int pfreq): origin(porigin), priority(ppriority), function(pfunction), pid(ppid),processor(proc), freq(pfreq){}

    bool operator <(const eqmodel & model) const
	{
		return priority < model.priority;
	}
};