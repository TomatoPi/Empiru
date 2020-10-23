#include <iostream>
using namespace std;

template <int val>
struct Counter { 
  static constexpr int value = val;
};

template <typename T>
struct Call {
  static constexpr int value = 0;
};

int main() {
  cout << Counter<5>::value << endl;
  cout << Counter<7>::value << endl;
  return 0;
}
