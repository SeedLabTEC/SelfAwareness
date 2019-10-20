/* includes */
#include <iostream>
#include <executionQueue.h>

/* namespaces */
using namespace std;

/*global var*/
list<eqmodel> gq;

void print_gq(){
    while(gq.size()>0)
    {
        cout << "{\norigin: " << gq.back().origin << "\npriority: " << gq.back().priority << "\nfunction: " << gq.back().function << "\n}" << endl;
        gq.pop_back();
    }
    
}

eqmodel get_next(){
    eqmodel temp = gq.back();
    gq.pop_back();
    return temp;
}

void push(eqmodel item){
    gq.push_back(item);
    gq.sort();
}

eqmodel pop(){
    eqmodel temp = gq.back();
    gq.pop_back();
    return temp;
}

int size(){
    return gq.size();
}