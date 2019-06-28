#ifndef MAT_H
#define	MAT_H

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
        bool compare(const mat& ref);

        void t(); //sequential transpose
        void t_m();  //multi thread transpose
        void mul(); //sequential multipys
        void mul_m();  //multi thread transpose
};

#endif
