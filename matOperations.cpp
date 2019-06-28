#include <iostream>
#include <iomanip>
#include <pthread.h>
#include "matOperations.h"
#include "multiThread.h"
#include "math.h"

using namespace std;

mat& matOperations::mul(mat& A, mat& B) {
    if (A.n_cols != B.n_rows) {
        cout << "Out of range!" << endl;
    }
    else {
        mat * p = new mat(A.n_rows, B.n_cols);
        int r = A.n_rows;
        int c = B.n_cols;
        int s = A.n_cols;

        for (int i = 0; i < r; i++) {
            for (int j = 0; j < c; j++) {
                int sum = 0;
                for (int k = 0; k < s; k++) {
                    sum += A.getElement(i, k) * B.getElement(k, j);
                }
                p->getElement(i, j) = sum;
            }
        }
        p->n_rows = r;
        p->n_cols = c;
        return *p;
    }
}

mat& matOperations::mul_m(mat& A, mat& B) {
    if (A.n_cols != B.n_rows) {
        cout << "Out of range!" << endl;
    }
    else {
        mat *p = new mat(A.n_rows, B.n_cols);
        pthread_t threads[num_thread];

        arg_struct Arg;
        Arg.A = &A;
        Arg.B = &B;
        Arg.OUT = p;
        for (int i = 0; i < num_thread; i++) {
            pthread_create(&threads[i], NULL, multiThread::multiply, (void *)&Arg);
        }
        for (int i = 0; i < num_thread; i++) {
            pthread_join(threads[i], NULL);
        }
        multiThread::core_multiply = 0;
        return *p;
    }
}
