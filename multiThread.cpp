#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "multiThread.h"

using namespace std;

int num_thread = 4;

void * multiThread::transpose(void * arguments) {
    struct arg_struct *args = (struct arg_struct *)arguments;
    int r = args->A->n_rows;
    int c = args->A->n_cols;
    int step = core_transpose++;

    for (int i = step * r / num_thread; i < (step + 1) * r / num_thread; i++) {
        for (int j = 0; j < c; j++) {
            args->tmp[j * r + i] = args->A->getElement(i, j);
        }
    }
}

int multiThread::core_transpose = 0;


void* multiThread::multiply(void * arguments) {
      struct arg_struct *args = (struct arg_struct *)arguments;
      mat * A = args->A;
      mat * B = args->B;
      mat * OUT = args->OUT;
      int r = A->n_rows;
      int c = B->n_cols;
      int s = A->n_cols;
      int step = core_multiply++;

        for (int i = step * r / num_thread; i < (step + 1) * r / num_thread; i++) {
            for (int j = 0; j < c; j++) {
                int sum = 0;
                for (int k = 0; k < s; k++) {
                    sum += A->getElement(i, k) * B->getElement(k, j);
                }
              //  OUT->getElement(i, j) = sum;
            }
        }
}

int multiThread::core_multiply = 0;
