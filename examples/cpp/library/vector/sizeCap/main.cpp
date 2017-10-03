// 1. How does size and capacity grow?
// 2. reserve
// 3. Use a ranged for-loop to write display(vec)
// 4. Erase all of the even numbers in the vector

#include <iostream>
#include <cstdlib>
#include <vector>
const int MAX = 10;

void display(std::vector<int>& vec){
	for(auto i : vec){
		std::cout<<i<<std::endl;
	}
}

int main() {
  std::vector<int> vec;
  vec.push_back(2);
  for (int i = 0; i < MAX; ++i) {
    vec.push_back( rand()%100 );
  }
  int x=0;
  auto i=vec.begin();
  while(i!=vec.end()){
	if(i%2==0){
		vec.erase(vec.begin()+i);	
	}
	i++;
  }
  display(vec);
}
