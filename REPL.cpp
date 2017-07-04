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
#include "ParseLib.h"

int main(){
  std::string input;
  while(true){
    input = "";
    std::cin.ignore();
    std::getline(std::cin,input);
    std::unique_ptr<Expression> to_print = ParseLib::parse(input);
    std::cout << "pre simplification" <<std::endl;
    std::cout << to_print->toString() << std::endl;
    std::cout << "post simplification" <<std::endl;
    std::cout << to_print->simplify()->toString() << std::endl;
    std::unique_ptr<Expression> deriv = to_print->derivative("x");
    std::cout << "post Derivative wrt x: " << deriv->toString() <<std::endl;
    std::unique_ptr<Expression> deriv_simp = deriv->simplify();
    std::cout << "simplified derivative" << std::endl;
    std::cout << deriv_simp->toString() << std::endl;
    
  }
}
