// 1. size v capacity
// 2. value semantics
// 3. push_back 
// 4. reserve 
// 5. emplace_back
// 6. explicit
// 7. ranged for loops

#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

class Number {
public:
  //Number() : number(0) { std::cout << "default" << std::endl; }
  Number(int n) : number(n) { std::cout << "convert" << std::endl; }
  Number(const Number& a) : number(a.number) {
    std::cout << "copy" << std::endl;
  }
  Number& operator=(const Number& rhs) {
    if ( this != &rhs ) {
      number = rhs.number;
    }
    std::cout << "assign" << std::endl;
    return *this;
  }
  int getNumber() const { return number; }
private:
  int number;
};
std::ostream& operator<<(std::ostream& out, const Number& n) {
  return out << n.getNumber();
}

int main() {
  std::vector<Number> vec;
  vec.reserve(10);
  for (unsigned int i = 0; i < 5; ++i) {
    vec.emplace_back( Number(i) );
    std::cout<<vec[i]<<" Capacity - "<<vec.capacity()<<" Size - "<<vec.size()<<std::endl;
  }
  

}
