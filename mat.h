#ifndef MAT_H
#define	MAT_H

#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class row {
    public:
        int * data;
        int length;
        row();
        int operator[] (const int index);
};

class mat {
    private:
        int * data;
    public:
        int n_rows;
        int n_cols;
        int counter;
        mat();
        mat(int row, int col);
        ~mat();
        void print();
        void set_size(int row, int col);
        void fill(int num);
        void fillRand(int minValue, int maxValue);
        mat& operator<< (const int input);
        row operator[] (const int index);

        void t();
};

#endif
