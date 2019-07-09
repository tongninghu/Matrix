#ifndef   MULTITHREAD_H
#define	  MULTITHREAD_H

#include "mat.h"

using namespace std;
extern int num_thread;

struct arg_struct {
    int * left;
    int * right;
    int * output;
    int n_rows;
    int n_cols;
};

class multiThread {
public:
    static void * multiply(void * arguments);
    static int core_multiply;
};

#endif
