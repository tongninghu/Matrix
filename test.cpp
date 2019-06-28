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

    mat B(3, 4);
    B.set_size(5, 6);
    cout << "after set_size, B: " << endl;
    B.print();

    B << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8;
    cout << "after insert, B: " << endl;
    B.print();

    cout << B[0][3] << endl;
    B[0][3] = 40;
    cout << B[0][3] << endl;
}
