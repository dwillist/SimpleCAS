#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>

#include "ExponentExpression.h"
#include "Expression.h"
#include "FunctionTags.h"
#include "SimplifyFunctions"



//
// CONSTRUCTORS
//

ExponentExpression::ExponentExpression(std::vector<Expression * > exponent_operands) :
  Expression(FunctionTags::EXPONENT,
    2, // this is max value of size_t due to two's complement
    2,
    false,
    false,
    boost::multiprecision::cpp_rational(),
    std::string(),
    exponent_operands)
    {}

ExponentExpression::ExponentExpression(Expression * base,Expression * exponent) :
Expression(boost::assign::list_of(base)(exponent)){}

ExponentExpression::ExponentExpression(const Expression & E) : Expression(E){
    tag = FunctionTags::EXPONENT;
  }



//Virtual Functions
boost::multiprecision::cpp_rational getValue(){
  return boost::multiprecision::cpp_rational(0);
}

//
// CAS functions
//




Expression * ExponentExpression::simplify(){
  namespace SF = SimplifyFunctions;
  Expression * base =  getOperand(0)->simplify();
  Expression * exponent = getOperand(1)->simplify();
  if(SF::isRational(base) && SF::isRational(exponent){
    return simplify_both_rational(base,exponent);
  }
  else if(SF::isRational(base){
    return simplify_base_rational(base,exponent);
  }
  else if(SF::isRational(exponent){
    return simplify_exponent_rational(exponent);
  }
  // other simplifications
  vector<Expression * > temp = {base,exponent};
  Expression * to_return = new ExponentExpression(temp);
  return to_return;
}
