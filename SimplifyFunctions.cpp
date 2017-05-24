#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

#include "SimplifyFunctions.h"
#include "FunctionTags.h"
#include "Expression.h"
#include "RationalExpression.h"
#include "UndefinedExpression.h"
#include "ExponentExpression.h"
#include "SumExpression.h"
#include "ProductExpression.h"

namespace SF = SimplifyFunctions;
namespace BM = boost::multiprecision;
namespace FT = FunctionTags;

//
// Identification functions
//

bool SF::isInteger(Expression * expr){
  return isRational(expr) && BM::denominator(expr->getValue()) == 1;
}

bool SF::isRational(Expression * expr){
  return expr->getTag() == FT::RATIONAL;
}

bool SF::isVariable(Expression * expr){
  return expr->getTag() == FT::VARIABLE;
}

bool SF::isUndefined(Expression * expr){
  return expr->getTag() == FT::UNDEFINED;
}

bool SF::isExponent(Expression * expr){
  return expr->getTag() == FT::EXPONENT;
}

bool SF::isSum(Expression * expr){
  return expr->getTag() == FT::SUM;
}

bool SF::isProduct(Expression * expr){
  return expr->getTag() == FT::PRODUCT;
}

std::vector<Expression * > SF::buildBinaryVector(Expression * E1, Expression * E2){
  std::vector<Expression *> to_return = {E1,E2};
  return to_return;
}

bool SF::isUndefinedExponent(Expression * base, Expression * exponent){
  if(SF::isUndefined(base) || SF::isUndefined(exponent)){
    return true;
  }
  else if(SF::isRational(base) && base->getValue() == 0){
    return !SF::isRational(exponent) || exponent->getValue() <= 0;
  }
  return false;
}



Expression * SF::makeUndefinedExponenet(Expression * base, Expression * exponent){
  //TODO: check if this works need to watch that ExponentExpression that is created
  // is not destroyed when this function goes out of range, could cause some nasty bugs
  return new UndefinedExpression(ExponentExpression(base,exponent));
}

bool SF::simplifiableToRational(Expression * base,Expression * exponent){
  // want to come up with maximal bout on number of digits
  //TODO: extend this to be more useful really don't want to simplify 2 ^ 100000
  return SF::isInteger(exponent);
}

Expression * SF::simplifyBothRational(Expression * base,Expression * exponent){
  BM::cpp_rational base_value = base->getValue();
  BM::cpp_rational exponent_value = exponent->getValue();
  if(SF::isUndefinedExponent(base,exponent)){
    return SF::makeUndefinedExponenet(base,exponent);
  }
  else if(SF::simplifiableToRational(base,exponent)){
    if(base_value == 0 && exponent_value == 0){
      return new RationalExpression(1);
    }
    if(base_value == 0){
      return new RationalExpression(0);
    }
    else if(base_value == 1){
      return new RationalExpression(0);
    }
    else{
      return SF::rational_pow(base,exponent);
    }
  }
  else{
    return new ExponentExpression(base,exponent);
  }
}

Expression * SF::simplifyBaseRational(Expression * base,Expression * exponent){
  if(SF::isUndefinedExponent(base,exponent)){
    return SF::makeUndefinedExponenet(base,exponent);
  }
  if(SF::isExponent(exponent)){
    // no simplification can result of
    // x ^ y ^ z if y ^ z cannot be simplified
    return new ExponentExpression(base,exponent);
  }
  else if(SF::isProduct(exponent)){
    if(isInteger(exponent->getOperand(0))
       && SF::simplifiableToRational(base,exponent->getOperand(0))){
      // then we have a simplification of the following form
      // r^5*y -> (r^5)^y where r is rational
      return new ExponentExpression(
                  rational_pow(base,exponent->getOperand(0)),
                  exponent->clone(1,exponent->size())
                );
    }
    return new ExponentExpression(base,exponent);
  }
  else if(SF::isSum(exponent)){
    if(isInteger(exponent->getOperand(0))
       && SF::simplifiableToRational(base,exponent->getOperand(0))){
         // we have a a simplification of the folowing form
         // r^5+y -> r^5 * r^y where r is rational
         Expression * newBase = rational_pow(base,exponent->getOperand(0));
         Expression * newExponent = new SumExpression(exponent->clone_operands(1,exponent->size()));
      std::cout << "new Exponenet String " + newExponent->toString() << std::endl;
         return new ProductExpression(newBase, new ExponentExpression(base,newExponent));
    }
  }
  //else
  return new ExponentExpression(base,exponent);
}

// here i make the dubious simplification that (expr)^0 == 1, which is obviously not
// always true (eg expr = 0);
Expression * SF::simplifyExponentRational(Expression * base,Expression * exponent){
  BM::cpp_rational exponent_value = exponent->getValue();
  if(SF::isUndefinedExponent(base,exponent)){
    return SF::makeUndefinedExponenet(base,exponent);
  }
  else if(exponent_value == 0){
    return new RationalExpression(1);
  }
  else if(SF::isExponent(base)){
    return new ExponentExpression(
      base -> getOperand(0),
      new ProductExpression(exponent,base->getOperand(1))
    );
  }
  //else
  return new ExponentExpression(base,exponent);
}

RationalExpression * SF::rational_pow(Expression * base,Expression * integer_exponent){
  BM::cpp_rational base_value = base->getValue();
  BM::cpp_rational integer_exponent_value = integer_exponent->getValue();
  if(BM::denominator(integer_exponent_value) != 1){
    throw std::range_error("exponent not integer");
  }
  // otherwise we have an integer exponenet
  int int_exponent = integer_exponent_value.convert_to<int>();
  BM::cpp_int new_num = BM::pow(BM::numerator(base_value),int_exponent);
  BM::cpp_int new_denom = BM::pow(BM::denominator(base_value),int_exponent);
  return new RationalExpression(BM::cpp_rational(new_num,new_denom));
}
