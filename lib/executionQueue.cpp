/* includes */
#include <iostream>
#include <list> 
#include <EQModel.h>

/* namespaces */
using namespace std;

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
