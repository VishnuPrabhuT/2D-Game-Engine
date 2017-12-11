#include <iostream>
#include <functional>
#include <ctime>

int main(){
  int x=5;
  std::function<int()> globalIncr=[&x]()->int{
    return x+5;
  };
  std::function<int(int)> fact=[&fact](int x) {
    if(x==1){
      return 1;
    }
    else {
      return x*fact(x-1);
    }
  };
  std::cout << x << "- fact() - " << fact(5) << '\n';
  std::cout << x << "- globalIncr() - " << globalIncr() << '\n';

  //auto isLetter = [](char c)->bool { return ((c>='A' && c<='Z') || (c>='a' && c<='z')); };
  //std::cout << isLetter('1') << '\n';
}
