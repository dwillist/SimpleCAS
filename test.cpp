#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "RationalExpression.h"
#include "VariableExpression.h"
#include "SumExpression.h"
#include "ProductExpression.h"
#include "ExponentExpression.h"
#include "UndefinedExpression.h"
#include "SimplifyFunctions.h"

int main(){
  RationalExpression * R1 = new RationalExpression(3);
  VariableExpression * Y = new VariableExpression("y");
  RationalExpression * R2 = new RationalExpression(5);
  std::cout << "baseic operands " << std::endl;
  std::cout << R1->toString() << std::endl;
  std::cout << R2->toString() << std::endl;
  std::cout << Y->toString() << std::endl;
  //ProductExpression* S = new ProductExpression(R1,Y);
  ExponentExpression * S = new ExponentExpression(R1,Y);
  ExponentExpression* E = new ExponentExpression(S,R2);
  Expression * simplifiedE = E->simplify();
  std::cout <<"Exponent Expression E" << std::endl;
  std::cout << E -> toString() << std::endl;
  std::cout <<"simplified Exponent Expression E" << std::endl;
  std::cout << simplifiedE->toString() << std::endl;
}
