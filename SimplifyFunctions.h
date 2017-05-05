#ifndef _SIMPLIFY_FUNCTIONS_
#define _SIMPLIFY_FUNCTIONS_

#include "Expression.h"
#include "Rational.h"
#include "RationalExpression.h"
#include "Factories.h"


#include <vector>

namespace SimplifyFunctions{
  /**
    @params: expression
    @return: returns true if Expression is a basic algebraic expression
  */
  bool isBAE(Expression* expr);

  bool isASE(Expression * expr);

  SimplifySum(Expression* sum_expression);
  SimplifyProduct(Expression* prod_expression);
  SimplifyPower(Expression* power_expreesion);

}

// implementaion below



bool SimplifyFunctions::isASE(Expression * expr){
  if(expr -> isRational() || expr-> isVariable()){
    return true;
  }
  return false;
}

bool SimplifyFunctions:isBAE(Expression * expr){
  if(expr -> isVariable() || expr-> isRational()){ return true;}
  else if()
}

#endif
