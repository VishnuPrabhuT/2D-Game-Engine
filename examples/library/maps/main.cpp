// 1. How does size and capacity grow?
// 2. reserve
// 3. Use a ranged for-loop to write display(vec)
// 4. Erase all of the even numbers in the vector

#include <iostream>
#include <cstdlib>
#include <map>
const int MAX = 10;

int main() {
  std::map<int,int> vec;
  vec.push_back(2);
  for (int i = 0; i < MAX; ++i) {
    vec.push_back( rand()%100 );
  }
}
