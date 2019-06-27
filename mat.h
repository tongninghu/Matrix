#ifndef MAT_H
#define	MAT_H

#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class row {
    public:
        double * data;
        int length;
        row();
        double operator[] (const int index);
};

class mat {
    private:
        double * data;
    public:
        int n_rows;
        int n_cols;
        int counter;
        mat();
        mat(int row, int col);
        ~mat();
        void print();
        void set_size(int row, int col);
        void fill(double num);
        mat& operator<< (const double input);
        row operator[] (const int index);
};

#endif
