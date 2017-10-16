#include <iostream>
#include <sstream>

int main() {
  double x = 2.5;
  std::stringstream strm;
  strm << "CAT" << std::endl;
  std::cout << strm.str() << std::endl;
  strm >> x;
  std::cout << x << std::endl;
}
