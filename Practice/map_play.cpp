#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <algorithm>

void init(std::map<std::string, int> & mymap, const
          std::vector<std::string>& names) {
  for (const auto& n : names) {
    mymap[n] = rand() % 100;
  }
}

void print(const std::map<std::string, int>& mymap) {
  for (const auto& n : mymap) {
    std::cout << n.first << ", " <<  n.second << std::endl;
  }
}

bool nameFound(const std::map<std::string, int>& mymap, std::vector<std::string>& names, int index) {
  std::string searchString = names[index];
  return mymap.find(names[index]) != mymap.end();
}

int main(){
	std::vector<std::string> ;
}