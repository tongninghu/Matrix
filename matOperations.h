#ifndef MATOPERATIONS_H
#define	MATOPERATIONS_H

#include "mat.h"
using namespace std;

class matOperations {
    public:
        static mat& mul(mat& A, mat& B); //sequential multiply
        static mat& mul_m(mat& A, mat& B);  //multi thread multiply
        static void bufferMultiply(vector<int>& leftBuffer,
            vector<int>& rightBuffer, vector<int>& writeBuffer, int rows);
};

#endif
