#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "RationalExpression.h"
#include "VariableExpression.h"
#include "SumExpression.h"
#include "ProductExpression.h"
#include "ExponentExpression.h"

int main(){
  VariableExpression * X = new VariableExpression("x");
  VariableExpression * Y = new VariableExpression("x");
  RationalExpression * R = new RationalExpression(5);
  std::cout << R->toString() << std::endl;
  std::cout << X->toString() << std::endl;
  std::cout << Y->toString() << std::endl;
  std::vector<Expression*> sum_operands {X,R};
  std::cout << "attempting to build sum" << std::endl;
  //SumExpression S = SumExpression(sum_operands);
  //ProductExpression S = ProductExpression(sum_operands);
  ExponentExpression S = ExponentExpression(sum_operands);
  std::cout <<"attempting to print" << std::endl;
  std::cout << S.toString() << std::endl;
}
