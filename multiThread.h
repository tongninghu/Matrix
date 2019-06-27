#ifndef   MULTITHREAD_H
#define	  MULTITHREAD_H

#include <vector>
#include <fstream>
#include <iostream>


using namespace std;

struct arg_struct {
    int core;
    int * data;
    int * tmp;
    int r;
    int c;
};

class multiThread {
public:
    static void * multiTranspose(void * arguments);
};

#endif
