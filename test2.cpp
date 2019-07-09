/*
 ** A general description for your program.
 ** Author name and date list here, too.
 */
#include <fstream>
#include <iostream>
#include <string>
#include "mat.h"
#include "matOperations.h"

using namespace std;


int main(int argc, char * argv[]) {
    mat A(14, 11);
    A.fillRand(0, 10);
    A.print();

    mat B(11, 9);
    B.fillRand(0, 10);
    B.print();

    mat * t = &matOperations::mul(A, B, true);
    t->print();
    delete t;

    mat C;
    C = A;

    mat * k = &matOperations::mul(C, B, true);
    k->print();
    delete k;
/*
    A.t();
    A.print();

    B.t();
    B.print();   */
    return 0;
}
