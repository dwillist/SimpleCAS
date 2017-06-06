#include <boost/multiprecision/cpp_int.hpp>
#include <boost/assign/list_of.hpp>
#include <string>
#include <vector>
#include <iostream>

#include "SumExpression.h"
#include "ProductExpression.h"
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
  Expression * to_return = new ExponentExpression(clone_operands(begin,end));
  return to_return->simplify();
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
    std::cout << "both ratonal: " << toString() << std::endl;
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

Expression * ExponentExpression::derivative(std::string with_respect_to){
  Expression * base_derivative = getOperand(0)->derivative(with_respect_to);
  Expression * exponent_derivative = getOperand(1)->derivative(with_respect_to);
  Expression * base_clone = getOperand(0)->clone();
  Expression * exponent_clone = getOperand(1)->clone();
  
  Expression * first_prod = new ProductExpression(base_derivative->clone(),SimplifyFunctions::makeQuotent(exponent_clone->clone(), base_clone->clone()));
  Expression * second_prod = new ProductExpression(exponent_derivative->clone(),SimplifyFunctions::makeNaturalLog(base_clone->clone()));
  Expression * sum_expr = new SumExpression(first_prod,second_prod);
  return new ProductExpression(new ExponentExpression(base_clone,exponent_clone),sum_expr);
}
