#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>
#include <iostream>

#include "SumExpression.h"
#include "Expression.h"
#include "FunctionTags.h"
#include "SimplifyFunctions.h"



//
// CONSTRUCTORS
//

SumExpression::SumExpression(std::vector<Expression * > sum_operands) :
  Expression(FunctionTags::SUM,
    -1, // this is max value of size_t due to two's complement
    0,
    false,
    false,
    boost::multiprecision::cpp_rational(0),
    std::string(),
    sum_operands)
    {}

SumExpression::SumExpression(const Expression & E) : Expression(E){
    tag = FunctionTags::SUM;
  }


SumExpression::SumExpression(Expression * E1, Expression * E2) :
  SumExpression(SimplifyFunctions::buildBinaryVector(E1,E2)){}

Expression * SumExpression::clone() const{
  return clone(0,size());
}

Expression * SumExpression::clone(std::size_t begin, std::size_t end) const{
  return new SumExpression(clone_operands(begin,end));
}

/*
boost::multiprecision::cpp_rational SumExpression::getValue() const{
  throw "SumExpression has no value";
  return boost::multiprecision::cpp_rational();
}

std::string SumExpression::getName() const{
  throw "SumExpression has no name to get";
  return std::string();
}
*/
//
// CAS functions
//

Expression * SumExpression::simplify(){
    return this;
}
