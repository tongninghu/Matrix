#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "multiThread.h"

using namespace std;

int num_thread = 4;

void * multiThread::multiTranspose(void * arguments) {
    struct arg_struct *args = (struct arg_struct *)arguments;
    int n_rows = args->r;
    int n_cols = args->c;
    int step = core++;

    for (int i = step * n_rows / num_thread; i < (step + 1) * n_rows / num_thread; i++) {
        for (int j = 0; j < n_cols; j++) {
            args->tmp[j * n_rows + i] = args->data[i * n_cols + j];
        }
    }
}

int multiThread::core = 0;
