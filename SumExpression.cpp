#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>
#include <iostream>

#include "SumExpression.h"
#include "Expression.h"
#include "FunctionTags.h"
#include "SimplifyFunctions.h"

namespace SF = SimplifyFunctions;

//
// CONSTRUCTORS
//

SumExpression::SumExpression(std::vector<Expression * > sum_operands) :
  Expression(FunctionTags::SUM,
    -1, // this is max value of size_t due to two's complement
    0,
    true,
    true,
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
  Expression * to_return = new SumExpression(clone_operands(begin,end));
  return to_return->simplify();
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
  if(size() == 0){
    return new RationalExpression(0);
  }
  if(size() == 1){
    return getOperand(0)->clone();
  }
  else{
    std::vector<Expression *> simp_ops;
    for(std::size_t i = 0; i < size(); ++i){
      simp_ops.push_back(getOperand(i)->simplify());
    }
    Expression * new_sum = SimplifyFunctions::levelReduce(
            new SumExpression(simp_ops),
            SF::sum_create_function);
    return SF::sumSimplfy(new_sum);
  }
}

Expression * SumExpression::derivative(std::string with_respect_to){
  std::vector<Expression * > derivative_operands;
  for(auto && operand : operands){
    derivative_operands.push_back(operand->derivative((with_respect_to)));
  }
  return new SumExpression(derivative_operands);
}
