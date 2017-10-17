#include<iostream>
class Number{
public:
	Number(){
		std::cout<<"default"<<std::endl;
	}
	Number(float f):number(f){
		std::cout<<"convert"<<std::endl;
	}
	Number(const Number& n):number(n.number){
		std::cout<<"copy"<<std::endl;
	}
	~Number(){
		std::cout<<"destructor"<<std::endl;
	}
	Number& operator=(const Number&){
		std::cout<<"assign"<<std::endl;
		return *this;
	}
private:
	float number;
};

class Student{
public:
	Student(float g){
		//gpa=g;
	}
private:
	Number gpa;
};
int main(){
	Student* npc =new Student(5.5);
	delete npc;
}