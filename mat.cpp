#include <vector>
#include <fstream>
#include <iostream>
#include "mat.h"

using namespace std;

mat::mat (): data(NULL) {
    data = NULL;
    counter = 0;
    n_rows = 0;
    n_cols = 0;
}

mat::mat(int row, int col): data(new int[row * col]) {
    counter = 0;
    n_rows = row;
    n_cols = col;
}

mat::~mat() {
    if (data) {
        delete [] data;
    }
}

void mat::print() {
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            cout << data[i * n_cols + j] << ", ";
        }
        cout << endl;
    }
}

void mat::set_size(int row, int col) {
    delete [] data;
    data = new int[row * col];
    counter = 0;
    n_rows = row;
    n_cols = col;
}

void mat::fill(int num) {
    for (int i = 0; i < n_rows * n_cols; i++) {
        data[i] = num;
    }
    counter = n_rows * n_cols;
}

void mat::fillRand(int minValue, int maxValue) {
    for (int i = 0; i < n_rows * n_cols; i++) {
        data[i] = rand() % maxValue + minValue;
    }
}

mat& mat::operator<< (const int input) {
    if (counter < n_rows * n_cols) {
        data[counter++] = input;
    }
    return *this;
}

row mat::operator[] (const int index) {
    if (index < n_rows) {
        row A;
        A.data = &data[index * n_cols];
        A.length = n_cols;
        return A;
    }
    else {
        cout << "Out of range!" << endl;
    }
}

void mat::t() {
    int * tmp = new int[n_rows * n_cols];
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            tmp[j * n_rows + i] = data[i * n_cols + j];
        }
    }
    delete [] data;
    data = tmp;

    int a = n_rows;
    n_rows = n_cols;
    n_cols = a;
}




row::row(): data(NULL) {
    length = 0;
}

int row::operator[] (const int index) {
    if (index < length) {
        return data[index];
    }
    else {
        cout << "Out of range!" << endl;
    }
}
