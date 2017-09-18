#include <iostream>
int i = 7;

namespace MySpace {
  void f(int& x) {
    x = x + 1;
  }
  int i = 17;
}

void f(int x) {
  x = x + 1;
}

int main() {
  int i = 99;
  MySpace::f(i);
  std::cout << "i is: " << i << std::endl;
  std::cout << "::i is: " << ::i << std::endl;
  std::cout << "MySpace::i is: " << MySpace::i << std::endl;
}
