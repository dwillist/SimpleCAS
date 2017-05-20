#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>

#include "SumExpression.h"
#include "Expression.h"
#include "FunctionTags.h"



//
// CONSTRUCTORS
//

SumExpression::SumExpression(std::vector<Expression * > sum_operands,
  boost::multiprecision::cpp_rational value = boost::multiprecision::cpp_rational(0)) :
  Expression(FunctionTags::SUM,
    -1, // this is max value of size_t due to two's complement
    0,
    false,
    false,
    value,
    std::string(),
    sum_operands)
    {}

SumExpression::SumExpression(const Expression & E) : Expression(E){
    tag = FunctionTags::SUM;
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
