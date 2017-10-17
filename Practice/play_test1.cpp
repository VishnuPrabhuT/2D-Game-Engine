#include<iostream>

class A{
public:
	
	virtual int getNumber() const{
		return num;
	}
	int num;
	A(){

	}
	A(const A& a):num(a.num){
		std::cout<<"Copy"<<std::endl;
	}
	A(int i):num(i){
		std::cout<<"Convert"<<std::endl;
	}
	friend std::ostream& operator<<(std::ostream& out,const A& a){
		return out<<a.getNumber();
	}
	~A(){
		std::cout<<"Destructor"<<std::endl;
	}
private:
	
};

class B: public A{
public:
	int getNumber(){
		return num;
	}
private:
	int num;
};

int main(){
	A a(5),b=a;
	//b=a;
	std::cout<<b<<std::endl;
	//std::cout<<a.getNumber()<<std::endl;
}
