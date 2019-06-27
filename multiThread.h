#ifndef   MULTITHREAD_H
#define	  MULTITHREAD_H

using namespace std;


struct arg_struct {
    int * data;
    int * tmp;
    int r;
    int c;
};

class multiThread {
public:
    static void * multiTranspose(void * arguments);
    static int core;
};

#endif
