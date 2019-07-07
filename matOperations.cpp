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

mat& matOperations::mul(mat& A, mat& B) {
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
        else copy(&A.data[j * A.n_cols], &A.data[j * A.n_cols] + A.n_cols, &leftBuffer[0]);

        for (int i = 0; i < B.n_rows / rows; i++) {
            if (rightIsFile) finr.read((char *)&rightBuffer[0], sizeof(int) * size);
            else copy(&B.data[i * B.n_cols], &B.data[i * B.n_cols] + size, &rightBuffer[0]);

            bufferMultiply(leftBuffer, rightBuffer, writeBuffer, rows, B.n_cols);
        }

        if (A.n_cols % rows != 0) {
            if (rightIsFile) finr.read((char *)&rightBuffer[0], sizeof(int) * (A.n_cols % rows) * B.n_cols);
            else copy(&B.data[B.n_rows / rows * B.n_cols],
                &B.data[B.n_rows / rows * B.n_cols] + (A.n_cols % rows) * B.n_cols, &rightBuffer[0]);

            bufferMultiply(leftBuffer, rightBuffer, writeBuffer, A.n_cols % rows, B.n_cols);
        }

        if (toFile) {
            fout.write((char *)&writeBuffer[0], sizeof(int) * B.n_cols);
        }
        else {
            copy(&writeBuffer[0], &writeBuffer[0] + B.n_cols, &p->data[j * B.n_cols]);
        }

        finr.clear();
        finr.seekg(0, ios::beg);
    }
    return *p;
}

void matOperations::bufferMultiply(int * leftBuffer, int * rightBuffer,
      int * writeBuffer, int rows, int cols) {
      for (int i = 0; i < rows; i++) {
          for (int j = 0; j < cols; j++) {
              writeBuffer[j] += leftBuffer[i] * rightBuffer[cols * i + j];
          }
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
