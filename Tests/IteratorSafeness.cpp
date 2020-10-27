//============================================================================
// Name        : Tests.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char **argv) {

  std::vector<int> v{0, 1, 2, 3};
  std::vector<int> w{4, 5, 6, 7};
  std::vector<std::vector<int>> U{v,w};
  std::vector<int>::iterator a(v.begin()), b(w.begin());
  cout << *a << " " << U[0][0] << endl;
  cout << *b << " " << U[1][0] << endl;
  std::swap(U[0], U[1]);
  cout << *a << " " << U[0][0] << endl;
  cout << *b << " " << U[1][0] << endl;
  return 0;
}
