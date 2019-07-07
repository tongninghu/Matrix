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
  mat A(11, 12);
  A.fillRand(0, 10);
  A.print();
  cout << endl;
  /*
  A.t();
  A.print();  */

  mat B(12, 10);
  B.fillRand(0, 10);
  B.print();
//  cout << endl << A.getElement(0, 4) << " " << A.getElement(1, 5) << endl;
 /*
  mat C;
  C = A;
  A.t();
  A.t_m();
  cout << C.compare(A) << endl;

  mat B(60, 110);
  B.fillRand(0, 10);
*/
  cout << endl;
  mat * t = &matOperations::mul(A, B);
  t->print();
  delete t;
  return 0;
}
