#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <cmath>

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
  namespace mp = boost::multiprecision;
  mp::cpp_rational R = mp::cpp_rational("2");
  mp::cpp_rational F = 2;
  std::cout << "log test: " << mp::log2(F) << std::endl;
}
