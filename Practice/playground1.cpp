#include<cstring>
#include<iostream>

class Game{
	public:
	Game():iniBuf(new char[1]){
		iniBuf[1]='\0';
		std::cout<<"Default"<<std::endl;	
	}
	Game(const char* name):iniBuf(new char[strlen(name)+1]){
		std::cout<<"Convert"<<std::endl;
		strcpy(iniBuf,name);
	}
	Game(const Game& g):iniBuf(new char[strlen(g.iniBuf)+1]){
		strcpy(iniBuf,g.iniBuf);
		std::cout<<"Copy"<<std::endl;
	}
	Game& operator=(const Game& rhs){
		if(this==&rhs) return *this;
		delete [] iniBuf;
		iniBuf=new char[strlen(rhs.iniBuf)+1];
		strcpy(iniBuf,rhs.iniBuf);
		std::cout<<"Assign"<<std::endl;
		return *this;
	}
	~Game(){	
		delete [] iniBuf;
		std::cout<<"Destructor"<<std::endl;
	}
	const char* getGame() const{	return iniBuf;	}
	private:
	char* iniBuf;	
};
int main(){
	Game g,z("Little Fighter!"),c=z;
	g=c;
	//Game z("Little Fighter!");
	//Game c(z);
	//std::cout<<c.getGame()<<std::endl;
	//g=z;
	std::cout<<g.getGame()<<std::endl;
}

