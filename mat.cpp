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

mat::mat(int row, int col): data(new double[row * col]) {
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
    data = new double[row * col];
    counter = 0;
    n_rows = row;
    n_cols = col;
}

void mat::fill(double num) {
    for (int i = 0; i < n_rows * n_cols; i++) {
        data[i] = num;
    }
    counter = n_rows * n_cols;
}

mat& mat::operator<< (const double input) {
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

row::row(): data(NULL) {
    length = 0;
}


double row::operator[] (const int index) {
    if (index < length) {
        return data[index];
    }
    else {
        cout << "Out of range!" << endl;
    }
}
