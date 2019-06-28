#ifndef   MULTITHREAD_H
#define	  MULTITHREAD_H

using namespace std;
extern int num_thread;

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
