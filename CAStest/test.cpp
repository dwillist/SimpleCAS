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

namespace mp = boost::multiprecision;
mp::cpp_rational rational_pow(const mp::cpp_rational & R,int exp){
  mp::cpp_int num_squared = mp::pow(mp::numerator(R),exp);
  mp::cpp_int den_squared = mp::pow(mp::denominator(R),exp);
  return mp::cpp_rational(num_squared,den_squared);
}

int main(){
  namespace mp = boost::multiprecision;
  mp::cpp_rational R = mp::cpp_rational("10/3");
  mp::cpp_rational F = 2;
  mp::cpp_int Num = mp::numerator(R);
  mp::cpp_int Den = mp::denominator(R);
  std::cout << R << std::endl;
  std::cout << "numerator squared: " << mp::pow(Num,F.convert_to<int>()) << std::endl;
  std::cout << "denominator squared: " << mp::pow(Den,F.convert_to<int>()) << std::endl;
  std::cout << "rational squared: " << rational_pow(R,F.convert_to<int>()) << std::endl;
  //std::cout << R/3 << std::endl;
  //std::cout << 1/(R/3) << std::endl;
}
