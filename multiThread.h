#ifndef   MULTITHREAD_H
#define	  MULTITHREAD_H

#include "mat.h"

using namespace std;
extern int num_thread;

struct arg_struct {
    int * tmp;
    mat * A;
    mat * B;
    mat * OUT;
};

class multiThread {
public:
    static void * transpose(void * arguments);
    static void * multiply(void * arguments);
    static int core_transpose;
    static int core_multiply;
};

#endif
