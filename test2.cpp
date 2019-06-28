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
  mat A(7, 6);
  A.fillRand(0, 10);
  cout << "after fill, A: " << endl;
  A.print();

  A.t();
  A.t_m();
  cout << "after transpose twice, A: " << endl;
  A.print();

  mat B(6, 11);
  B.fillRand(0, 10);
  cout << "after fill, B: " << endl;
  B.print();

  B.t();
  B.t_m();
  cout << "after transpose twice, B: " << endl;
  B.print();

  mat C(11, 30);
  C.fillRand(0, 10);
  cout << "after fill, C: " << endl;
  C.print();

  C.t();
  C.t_m();
  cout << "after transpose twice, C: " << endl;
  C.print();

  cout << "A*B: " << endl;
  mat O1 = matOperations::mul(A, B);
  O1.print();

  cout << "A*B: " << endl;
  mat O2 = matOperations::mul_m(A, B);
  O2.print();

  cout << "A*B*C: " << endl;
  mat O3 = matOperations::mul(O1, C);
  O3.print();

  cout << "A*B*C: " << endl;
  mat O4 = matOperations::mul_m(O2, C);
  O4.print();
  return 0;
}
