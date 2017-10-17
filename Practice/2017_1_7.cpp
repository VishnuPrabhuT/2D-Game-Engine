#include<cstdlib>
#include<vector>
#include<iostream>

void display(const std::vector<int>& numbers){
	for(auto n : numbers){
		std::cout<<n<<std::endl;
	}
	std::vector<int>::const_iterator its=numbers.begin();
	while(its!=numbers.end()){
		std::cout<<*its<<std::endl;	
	} 
}

int main(){
	std::vector<int> numbers;
	numbers.reserve(5);
	for(unsigned int i=0;i<5;i++){
		numbers.push_back(rand()%100);
	}
	display(numbers);
}