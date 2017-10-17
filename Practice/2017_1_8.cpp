#include<iostream>
class Bird{
public:
	Bird():speed(0),wingSpan(0){
		std::cout<<"Default"<<std::endl;
	}
	Bird(int w):wingSpan(w),speed(2*wingSpan){
		std::cout<<wingSpan<<"-"<<speed<<std::endl;
		std::cout<<"Convert"<<std::endl;
	}
	Bird(Bird& b):wingSpan(b.wingSpan),speed(2*b.wingSpan){
		std::cout<<"Copy"<<std::endl;
	}
private:
	int wingSpan;
	int speed;
};

int main(int argc, char const *argv[])
{
	Bird robin(5);
	Bird hood(robin);
	return 0;
}