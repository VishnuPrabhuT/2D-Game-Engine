#include<string>
#include<iostream>
#include<vector>
class Charizard{
	public:
		Charizard():attacks(){
			std::cout<<"Leer!"<<std::endl;
		}
		Charizard(const std::string& s):attacks(s){
			std::cout<<"Conversion - "<<attacks<<std::endl;
		}
		Charizard(const Charizard& c):attacks(c.attacks){
			std::cout<<"Copy - "<<attacks<<std::endl;
		}
		Charizard& operator=(const Charizard&){
			return *this;
		}
	private:
		std::string attacks;
};

int main()
{
	std::vector<Charizard> attacks;
	//attacks.reserve(2);
	attacks.push_back(std::string("Flamethrower!"));
	attacks.push_back(std::string("Fireblast!"));
	//attacks.push_back(std::string("Seismic Toss!"));
	//attacks.push_back(std::string("Dragon Rage!"));
	std::cout<<attacks.size()<<std::endl;
	std::cout<<attacks.capacity()<<std::endl;
	return 0;
}