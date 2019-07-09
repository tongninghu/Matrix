#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "multiThread.h"

using namespace std;

int num_thread = 4;

void* multiThread::multiply(void * arguments) {
      struct arg_struct *args = (struct arg_struct *)arguments;
      int *left = args->left;
      int *right = args->right;
      int *output = args->output;
      int n_rows = args->n_rows;
      int n_cols = args->n_cols;
      int step = core_multiply++;

      for (int i = 0; i < n_rows; i++) {
          for (int j = step * n_cols / num_thread; j < (step + 1) * n_cols / num_thread; j++) {
              output[j] += left[i] * right[n_cols * i + j];
          }
      }
}

int multiThread::core_multiply = 0;
