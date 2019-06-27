/*
 ** A general description for your program.
 ** Author name and date list here, too.
 */
#include <fstream>
#include <iostream>
#include <string>
#include "mat.h"

#define MAX_THREAD 4
using namespace std;

int num = MAX_THREAD;

int main(int argc, char * argv[]) {
  mat A(23, 14);
  A.fillRand(0, 30);
  cout << "after fill, A: " << endl;
  A.print();

  A.t();
  A.t(num);
  cout << "after transpose twice, B: " << endl;
  A.print();

  mat B(7, 11);
  B.fillRand(0, 30);
  cout << "after fill, B: " << endl;
  B.print();

  B.t();
  B.t(num);
  cout << "after transpose twice, B: " << endl;
  B.print();
  return 0;
}
