#include <iostream>
#include <iomanip>
#include <pthread.h>
#include <fstream>
#include <string>
#include <vector>
#include "matOperations.h"
#include "multiThread.h"
#include "math.h"

#define BUFFERSIZE 50
#define HEAPSIZE 100
using namespace std;

mat& matOperations::mul(mat& A, mat& B, bool multiThread) {
    if (A.n_cols != B.n_rows) {
        cout << "Out of range!" << endl;
        exit;
    }

    mat * p = new mat(A.n_rows, B.n_cols);
    int size = BUFFERSIZE / B.n_cols * B.n_cols;
    int rows = BUFFERSIZE / B.n_cols;

    int writeBuffer [B.n_cols];
    int leftBuffer [A.n_cols];
    int rightBuffer [size];

    ifstream finl(A.filename, ios::binary);
    ifstream finr(B.filename, ios::binary);
    ofstream fout(p->filename, ios::binary);

    bool leftIsFile = ((A.n_rows * A.n_cols >= HEAPSIZE) ? true : false);
    bool rightIsFile = ((B.n_rows * B.n_cols >= HEAPSIZE) ? true : false);
    bool toFile = ((A.n_rows * B.n_cols >= HEAPSIZE) ? true : false);

    for (int j = 0; j < A.n_rows; j++) {
        generate(&writeBuffer[0], &writeBuffer[0] + B.n_cols, [](){return 0;});

        if (leftIsFile) finl.read((char *)&leftBuffer[0], sizeof(int) * A.n_cols);

        int *left = (leftIsFile)? leftBuffer : &A.data[j * A.n_cols];
        int *output = (toFile)? writeBuffer : &p->data[j * B.n_cols];

        for (int i = 0; i < B.n_rows / rows; i++) {
            if (rightIsFile) finr.read((char *)&rightBuffer[0], sizeof(int) * size);
            int *right = (rightIsFile)? rightBuffer : &B.data[i * B.n_cols];

            bufferMultiply(left, right, output, rows, B.n_cols, multiThread);
        }

        if (A.n_cols % rows != 0) {
            if (rightIsFile) finr.read((char *)&rightBuffer[0], sizeof(int) * (A.n_cols % rows) * B.n_cols);
            int *right = (rightIsFile)? rightBuffer : &B.data[B.n_rows / rows * B.n_cols];

            bufferMultiply(left, right, output, A.n_cols % rows, B.n_cols, multiThread);
        }

        if (toFile) fout.write((char *)&writeBuffer[0], sizeof(int) * B.n_cols);

        finr.clear();
        finr.seekg(0, ios::beg);
    }
    return *p;
}

void matOperations::bufferMultiply(int * left, int * right, int * output,
    int n_rows, int n_cols, bool multiThread) {

    if (!multiThread) {
        for (int i = 0; i < n_rows; i++) {
            for (int j = 0; j < n_cols; j++) {
                output[j] += left[i] * right[n_cols * i + j];
            }
        }
    }
    else {
        pthread_t threads[num_thread];
        arg_struct Arg;
        Arg.left = left;
        Arg.right = right;
        Arg.output = output;
        Arg.n_rows = n_rows;
        Arg.n_cols = n_cols;
        for (int i = 0; i < num_thread; i++) {
            pthread_create(&threads[i], NULL, multiThread::multiply, (void *)&Arg);
        }
        for (int i = 0; i < num_thread; i++) {
            pthread_join(threads[i], NULL);
        }
        multiThread::core_multiply = 0;
    }
}
