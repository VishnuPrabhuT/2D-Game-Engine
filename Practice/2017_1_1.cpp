# include<iostream>
# include<string>
class A{
public:
	A(int n) : number(n) { }
	~A() { std::cout << "deleting A"<< std::endl;}
	int getNumber() const { return number; }
	virtual std::string getName() const =0;
private:
	int number;
};

class B : public A{
public:
	B(int m, int n) : A(m),number(n) { }
	~B() { std::cout << "deleting B" << std::endl; }
	int getNumber() const { return number; }
	std::string getName() const { return "I ’m B";}
private:
	int number;
};

int main () {
A* x = new B(12,13);
B* y = new B(66,77);
A* z = new B(1,2);
std::cout << x->getNumber() << std::endl;
std::cout << x->getName() << std::endl;
std::cout << z->getNumber() << std::endl;
std::cout << z->getName() << std::endl;
//delete z;
delete y;
}
