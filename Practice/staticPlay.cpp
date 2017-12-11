#include<iostream>
static int count=0;

class Number{
public:
  Number(int i):number(i){
    count++;
  }
private:
  int number;
};
int main(){
  for(int x=0;x<3;x++){
    Number n(x);
  }
  std::cout << count << '\n';
}
