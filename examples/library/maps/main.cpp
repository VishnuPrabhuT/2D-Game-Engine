#include <iostream>
#include <cstdlib>
#include <map>
<<<<<<< HEAD
const int MAX = 10;

int main() {
  std::map<int,int> vec;
  vec.push_back(2);
  for (int i = 0; i < MAX; ++i) {
    vec.push_back( rand()%100 );
=======

void print(const std::map<std::string, int>& mymap) {
  for ( const auto& x : mymap ) {
    std::cout << x.first << ", " << x.second << std::endl;
<<<<<<< HEAD
>>>>>>> 4176c7c8cdc4d1d067d5c8be847bbf580297ab9e
=======
>>>>>>> d01adda67f0b50d25da75211bdd0a470444a3077
>>>>>>> 82e2df9edceebe46651df940fbc81a9173f1b59b
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
