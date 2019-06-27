/*
 ** A general description for your program.
 ** Author name and date list here, too.
 */
#include <fstream>
#include <iostream>
#include <string>
#include "mat.h"

using namespace std;

int main(int argc, char * argv[]) {
    mat A;
    A.set_size(2, 3);
    A.fill(1);
    cout << "A: " << endl;
    A.print();
    mat B(3, 4);
    cout << "B: " << endl;
    B.print();
    B.set_size(5, 6);
    cout << "after set_size, B: " << endl;
    B.print();
    B << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8;
    cout << "after insert, B: " << endl;
    B.print();
    cout << "counter = " << B.counter << endl;
    cout << B[0][3] << endl;
    B.t();
    cout << "after transpose, B: " << endl;
    B.print();
    return 0;
}
