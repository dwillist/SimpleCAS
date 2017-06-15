#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "Expression.h"

int main(){
  Expression E = Expression(
      "testType",
      2,
      0,
      false,
      false
    );

    std::cout << "general Expression created" << std::endl;
}
