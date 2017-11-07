#include <iostream>
#include "string.h"

int main() {
  string s1 = "Hello";
  std::cout << s1[0];  // calls non-const []
  s1[0] = 'x';    // writing non-const string

  const string s2 = "World";
  std::cout << s2[0];  // calls const []
  //s2[0] = 'x';    // error! Writing const string
}
