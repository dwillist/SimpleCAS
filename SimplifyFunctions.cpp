#include <boost/multiprecision/cpp_int.hpp>

#include "SimplifyFunctions.h"
#include "FunctionTags.h"
#include "Expression.h"
#include "RationalExpression.h"


namespace SF = SimplifyFunctions;
namespace BM = boost::multiprecision;
namespace FT = FunctionTags;
namespace SFEXP = SimplifyFunctions::ExponentSimplify;

bool SF::isInteger(RationalExpression * expr){
  return BM::denominator(expr->getValue()) == 1;
}

bool SF::isRational(Expression * expr){
  return expr->getTag() == FT::RATIONAL;
}

bool SF::isVariable(Expression * expr){
  return expr->getTag == FT::VARIABLE;
}

bool SF::isUndefined(Expression * expr){
  return expr->getTag == FT::UNDEFINED;
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

Expression * makeUndefinedExponenet(Expression * base, Expression * exponent){
  //TODO: implement
}

bool SF::simplifiableToRational(RationalExpression * base,RationalExpression * exponent){
  // want to come up with maximal bout on number of digits
  //TODO: extend this to be more useful really don't want to simplify 2 ^ 100000
  return isInteger(exponent);
}

Expression * SF::simplifyBothRational(RationalExpression * base,RationalExpression * exponent){
  BM::base_value = base->getValue();
  BM::exponent_value = exponent->getValue();
  if(SF::EXP::isUndefinedExponent(base,exponent)){
    return makeUndefinedExponenet(base,exponent);
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
      return rational_pow(base,exponent);
    }
  }
  else{
    return new ExponentExpression(base,exponent);
  }
}

Expression * SF::simplifyBaseRational(Expression * base,Expression * exponent){
  if(SFEXP::undefinedExponent(base,exponent)){
    return SFEXP::makeUndefinedExponenet(base,exponent);
  }
  // the below is for the following simplification
  // 3^(x+3) = 3^x + 9
  else if(exponent->getValue() != 0){
    Expresson * new_exp_expression = new ExponentExpression(base,exponent->removeValue()).simplify();
    Expression * new_const_expression = new ExponentExpression(base,exponent->getValue()).simplify();
    std::vector<Expression *> new_args = {new_exp_expression,new_const_expression}

    return SumExpression(new_args).simplify();
  }
  return ExponentExpression(base,exponent);
}

// here i make the dubious simplification that (expr)^0 == 1, which is obviously not
// always true (eg expr = 0);
Expression * SF::simplifyExponentRational(Expression * base,Expression * exponent){
  BM::cpp_rational exponent_value = exponent->getValue();
  if(SFEXP:undefinedExponent(base,exponent)){
    return SFEXP::makeUndefinedExponenet(base,exponent);
  }
  else if(exponent_value == 0){
    return new RationalExpression(1);
  }
  else{
    return ExponentExpression(base,exponent);
  }
}

RationalExpression * rational_pow(RationalExpression * base,RationalExpression * integer_exponent){
  BM::cpp_rational base_value = base->getValue();
  BM::cpp_rational integer_exponent_value = integer_exponent->getValue();
  if(BM::denominator(integer_exponent_value) != 1){
    throw std::range_error("exponent not integer");
  }
  // otherwise we have an integer exponenet
  int exponent = integer_exponent_value.convert_to<int>;
  BM::new_num = BM::pow(BM::numerator(base_value),exponent_value);
  BM::new_denom = BM::pow(BM::denominator(base_value),exponent_value);
  new RationalExpression(BM::rational(new_num,new_denom));
}
}
