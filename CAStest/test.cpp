#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

void printV(std::vector<bool> & B){
  for(int i = 0; i < B.size(); ++i){
    if(B[i]){
      printf("1");
    }
    else{
      printf("0");
    }
  }
  printf("\n");
}

int main(){
  // copy constructor test
  int a = 5;
  int * b = new int(a);
  std::cout << *b << std::endl;

}
