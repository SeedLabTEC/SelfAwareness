// Execution Queue data model

enum Origin{
    POW = 0,
    CPU = 1,
    MEM = 2,
};

enum Functions{
    slowFreq  = 0,
    increaseFreq = 1,
    movePID = 2,
    stopProcessor = 3,
    initProcessor = 4,
    stopPID = 5,
    initPID = 6

};

struct eqmodel
{
    int origin; // origin ? power = 0, cpu = 1, mem = 2
    int priority; //define the priority of execution in queue
    int function; // define function to execute

    eqmodel(int porigin,int ppriority,int pfunction): origin(porigin), priority(ppriority), function(pfunction){}

    bool operator <(const eqmodel & model) const
	{
		return priority < model.priority;
	}
};