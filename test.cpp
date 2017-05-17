#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "RationalExpression.h"

int main(){

  RationalExpression R = RationalExpression(5);
  std::cout << R.getValue() << std::endl;
}
