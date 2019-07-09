#ifndef MATOPERATIONS_H
#define	MATOPERATIONS_H

#include "mat.h"
using namespace std;

class matOperations {
    public:
        static mat& mul(mat& A, mat& B, bool multiThread = false); //sequential multiply
        static void bufferMultiply(int * left, int * right, int * output,
            int n_rows, int n_cols, bool multiThread);
};

#endif
