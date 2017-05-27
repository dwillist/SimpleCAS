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
  VariableExpression * Y2 = new VariableExpression("y");
  RationalExpression * R2 = new RationalExpression(5);
  VariableExpression * X = new VariableExpression("x");
  ProductExpression * P = new ProductExpression(Y,X);
  ExponentExpression * E = new ExponentExpression(P,R1);
  Expression * simplifiedE = E->simplify();
  std::cout <<"sum Expression E" << std::endl;
  std::cout << E -> toString() << std::endl;
  std::cout <<"simplified sum Expression E" << std::endl;
  std::cout << simplifiedE->toString() << std::endl;
  /*
  std::cout << "baseic operands " << std::endl;
  std::cout << R1->toString() << std::endl;
  std::cout << R2->toString() << std::endl;
  std::cout << Y->toString() << std::endl;
  //ProductExpression* S = new ProductExpression(R1,Y);
  SumExpression * S = new SumExpression(R1,Y);
  SumExpression* E = new SumExpression(S,Y2);
  Expression * simplifiedE = E->simplify();
  std::cout <<"sum Expression E" << std::endl;
  std::cout << E -> toString() << std::endl;
  std::cout <<"simplified sum Expression E" << std::endl;
  std::cout << simplifiedE->toString() << std::endl;
  */

}
