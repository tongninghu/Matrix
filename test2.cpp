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
  mat A(23, 14);
  A.fillRand(0, 30);
  cout << "after fill, A: " << endl;
  A.print();

  A.t();
  A.t_m();
  cout << "after transpose twice, B: " << endl;
  A.print();

  mat B(7, 11);
  B.fillRand(0, 30);
  cout << "after fill, B: " << endl;
  B.print();

  B.t();
  B.t_m();
  cout << "after transpose twice, B: " << endl;
  B.print();
  return 0;
}
