#include<iostream>

	void x(int x){
		static int i=x;
		i++;	
		std::cout<<"x()-"<<i<<std::endl;	
	}
	void y(){
		int i=0;
		i++;
		std::cout<<"y()-"<<i<<std::endl;
	}
	
int main(){
			
		x(100);
		x(10);
		y();
		y();
	}


