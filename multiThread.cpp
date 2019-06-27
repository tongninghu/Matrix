#include <vector>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "multiThread.h"

using namespace std;

void * multiThread::multiTranspose(void * arguments) {
    struct arg_struct *args = (struct arg_struct *)arguments;
    int n_rows = args->r;
    int n_cols = args->c;
    for (int i = args->core * n_rows / 4; i < (args->core + 1) * n_rows / 4; i++) {
        for (int j = 0; j < n_cols; j++) {
            args->tmp[j * n_rows + i] = args->data[i * n_cols + j];
        }
    }
}
