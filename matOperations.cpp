#include <iostream>
#include <iomanip>
#include <pthread.h>
#include <fstream>
#include <string>
#include <vector>
#include "matOperations.h"
#include "multiThread.h"
#include "math.h"

#define BUFFERSIZE 15
#define HEAPSIZE 100
using namespace std;

mat& matOperations::mul(mat& A, mat& B) {
    if (A.n_cols != B.n_rows) {
        cout << "Out of range!" << endl;
        exit;
    }

    mat * p = new mat(A.n_rows, B.n_cols);
    int ar = A.n_rows;
    int bc = B.n_cols;
    int ac = A.n_cols;

    if (ar * ac <= HEAPSIZE && ac * bc <= HEAPSIZE){
        for (int i = 0; i < ar; i++) {
            for (int j = 0; j < bc; j++) {
                int sum = 0;
                for (int k = 0; k < ac; k++) {
                    sum += A.getElement(i, k) * B.getElement(k, j);
                }
                p->data[i * bc + j] = sum;
            }
        }
    }
    else if (ar * ac > HEAPSIZE && ac * bc > HEAPSIZE) {
        int size = BUFFERSIZE / B.n_cols * B.n_cols;
        int rows = BUFFERSIZE / B.n_cols;
        vector<int> writeBuffer (B.n_cols, 0);
        vector<int> leftBuffer(A.n_cols, 0);
        vector<int> rightBuffer(size, 0);
        ifstream finl(A.filename, ios::binary);
        ifstream finr(B.filename, ios::binary);
        bool toFile = ((ar * ac > HEAPSIZE) ? true : false);
        ofstream fout(p->filename, ios::binary);

        for (int j = 0; j < A.n_rows; j++) {
            finl.read((char *)&leftBuffer[0], sizeof(int) * A.n_cols);

            for (int i = 0; i < B.n_rows / rows; i++) {
                finr.read((char *)&rightBuffer[0], sizeof(int) * size);
                bufferMultiply(leftBuffer, rightBuffer, writeBuffer, rows);
            }

            if (ac % rows != 0) {
                finr.read((char *)&rightBuffer[0], sizeof(int) * (ac % rows) * bc);
                bufferMultiply(leftBuffer, rightBuffer, writeBuffer, ac % rows);
            }

            if (toFile) {
                fout.write((char *)&writeBuffer[0], sizeof(int) * B.n_cols);
            }
            else {
                copy(writeBuffer.begin(), writeBuffer.end(), &p->data[j * B.n_cols]);
            }
            generate(writeBuffer.begin(), writeBuffer.end(), [](){return 0;});
            finr.clear();
            finr.seekg(0, ios::beg);
        }
    }
    return *p;
}

void matOperations::bufferMultiply(vector<int>& leftBuffer, vector<int>& rightBuffer,
      vector<int>& writeBuffer, int rows) {
      for (int i = 0; i < rows; i++) {
          for (int j = 0; j < rightBuffer.size() / rows; j++) {
              writeBuffer[j] += leftBuffer[i] * rightBuffer[rightBuffer.size() / rows * i + j];
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
