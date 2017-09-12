#include<iostream>
#include<cstdlib>
#include<vector>
const int MAX=1000;
int main(){
	std::vector<int> vec;
	for(int i=0;i<MAX;i++){
		vec.push_back(rand()%100);
	}
	std::cout<<vec.size()<<std::endl;
	std::cout<<vec.capacity()<<std::endl;
}
