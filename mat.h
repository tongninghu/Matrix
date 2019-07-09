#ifndef MAT_H
#define	MAT_H

using namespace std;

class row {
    public:
        int * data;
        int length;
        row();
        int& operator[] (const int index);
};

class mat {
    public:
        int * data;
        string filename;
        int n_rows;
        int n_cols;
        int counter;
        mat();
        mat(int row, int col);
        ~mat();
        void print();
        void bufferPrint(vector<int>& buffer, int size, int& count);
        void set_size(int row, int col);
        void fill(int num);
        void fillRand(int minValue, int maxValue);
        void bufferFill(ofstream& fout, vector<int>& buffer, bool random = false,
            int minValue = 0, int maxValue = 0);

        mat& operator<< (const int input);
        mat& operator= (const mat& ref);
        row operator[] (const int index);
        bool compare(const mat& ref);
        int getElement(int row, int col);

        void t(); //sequential transpose
        void bufferTranspose(int * input, int * output, int n_rows, int n_rows2,
            int row, int col);
};

#endif
