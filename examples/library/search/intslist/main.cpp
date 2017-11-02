#include <iostream>
#include <list>
#include <cstdlib>
#include <algorithm>
const int MAX = 20;
const int MAX_NUMBER = 100;

void init(std::list<int> & vec) {
  for (unsigned int i = 0; i < MAX; ++i) {
    vec.push_back( rand() % MAX_NUMBER );
  }
}

void print(const std::list<int> & vec) {
  std::list<int>::const_iterator ptr = vec.begin();
  while ( ptr != vec.end() ) {
    std::cout << (*ptr)  << ", ";
    ++ptr;
  }
  std::cout << std::endl;
}

int main() {
  std::list<int> vec;
  init(vec);
  print(vec);
  vec.sort();
  print(vec);
}
