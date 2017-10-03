#include<iostream>

class Change{
public:
	Change(int x):i(x){
		i++;
	}
	int operator++(const int lhs){
		return lhs+5;
	}
	int getI() const{
		return i;
	}
private:
	int i;
};

int main(){
	
	Change c(0);	
	std::cout<<c.getI()<<std::endl;
}
