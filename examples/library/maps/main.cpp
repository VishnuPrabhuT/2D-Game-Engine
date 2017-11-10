#include <iostream>
#include <cstdlib>
#include <map>

void print(const std::map<std::string, int>& mymap) {
  for ( const auto& x : mymap ) {
    std::cout << x.first << ", " << x.second << std::endl;
  }
}

int main() {
  std::map<std::string, int> mymap;
  std::pair<std::string, int> temp("dog", 99);
  mymap.insert( temp );
  print( mymap );

  std::pair<std::string, int> temp2("dog", 17);
  mymap.insert( temp2 );
  print( mymap );
  std::cout << "size: " << mymap.size() << std::endl;
}
