#include <boost/multiprecision/cpp_int.hpp>
#include <boost/assign/list_of.hpp>
#include <string>
#include <vector>
#include <iostream>

#include "ExponentExpression.h"
#include "Expression.h"
#include "FunctionTags.h"
#include "SimplifyFunctions.h"



//
// CONSTRUCTORS
//

ExponentExpression::ExponentExpression(std::vector<Expression * > exponent_operands) :
  Expression(FunctionTags::EXPONENT,
    2,
    2,
    false,
    false,
    boost::multiprecision::cpp_rational(),
    std::string(),
    exponent_operands)
    {}

ExponentExpression::ExponentExpression(Expression * base,Expression * exponent) :
  ExponentExpression(SimplifyFunctions::buildBinaryVector(base,exponent)){}

ExponentExpression::ExponentExpression(const Expression & E) : Expression(E){
    tag = FunctionTags::EXPONENT;
  }


Expression * ExponentExpression::clone() const{
  return clone(0,size());
}

Expression * ExponentExpression::clone(std::size_t begin, std::size_t end) const{
  return new ExponentExpression(clone_operands(begin,end));
}


//Virtual Functions
boost::multiprecision::cpp_rational ExponentExpression::getValue() const{
  return boost::multiprecision::cpp_rational(0);
}

//
// CAS functions
//



Expression * ExponentExpression::simplify(){
  std::cout << "calling Exponent simplify" << std::endl;
  namespace SF = SimplifyFunctions;
  Expression * base =  getOperand(0)->simplify();
  Expression * exponent = getOperand(1)->simplify();
  if(SF::isRational(base) && SF::isRational(exponent)){
    std::cout << "both ratonal" << std::endl;
    return SF::simplifyBothRational(base,exponent);
  }
  else if(SF::isRational(base)){
    std::cout << "base ratonal" << std::endl;
    return SF::simplifyBaseRational(base,exponent);
  }
  else if(SF::isRational(exponent)){
    std::cout << "exponent ratonal" << std::endl;
    return SF::simplifyExponentRational(base,exponent);
  }
  // other simplifications
  std::cout << "no simplification" << std::endl;
  Expression * to_return = new ExponentExpression(base,exponent);
  return to_return;
}
