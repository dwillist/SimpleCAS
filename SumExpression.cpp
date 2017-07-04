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

SumExpression::SumExpression(std::vector<std::unique_ptr<Expression>  > sum_operands) :
  Expression(FunctionTags::SUM,
    -1, // this is max value of size_t due to two's complement
    0,
    true,
    true,
    boost::multiprecision::cpp_rational(0),
    std::string(),
    std::move(sum_operands))
    {}

/*SumExpression::SumExpression(std::vector<std::unique_ptr<Expression>  > && sum_operands) :
Expression(FunctionTags::SUM,
           -1, // this is max value of size_t due to two's complement
           0,
           true,
           true,
           boost::multiprecision::cpp_rational(0),
           std::string(),
           std::move(sum_operands))
{}
*/

SumExpression::SumExpression(const Expression & E) : Expression(E){
  tag = FunctionTags::SUM;
}

SumExpression::SumExpression(Expression && E) : Expression(E){
  tag = FunctionTags::SUM;
}



SumExpression::SumExpression(std::unique_ptr<Expression> E1, std::unique_ptr<Expression> E2) :
  SumExpression(SimplifyFunctions::makeBinaryVector(E1->clone(),E2->clone())){}

std::unique_ptr<Expression>  SumExpression::clone() const{
  return clone(0,size());
}

std::unique_ptr<Expression>  SumExpression::clone(std::size_t begin, std::size_t end) const{
  std::unique_ptr<Expression>  to_return(new SumExpression(clone_operands(begin,end)));
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

std::unique_ptr<Expression> SumExpression::simplify(){
  if(size() == 0){
    return std::unique_ptr<Expression>(new RationalExpression(0));
  }
  if(size() == 1){
    return getOperand(0)->clone();
  }
  else{
    std::vector<std::unique_ptr<Expression> > simp_ops;
    for(std::size_t i = 0; i < size(); ++i){
      simp_ops.push_back(getOperand(i)->simplify());
    }
    std::unique_ptr<Expression>  new_sum(
                                         SimplifyFunctions::levelReduce(
                                                                        std::unique_ptr<Expression>(new SumExpression(std::move(simp_ops))),
                                                    SF::makeSumFunction));
    return SF::sumSimplfy(std::move(new_sum));
  }
}

std::unique_ptr<Expression>  SumExpression::derivative(std::string with_respect_to){
  std::vector<std::unique_ptr<Expression>  > derivative_operands;
  for(auto && operand : operands){
    derivative_operands.push_back(operand->derivative((with_respect_to)));
  }
  return std::unique_ptr<Expression>(new SumExpression(std::move(derivative_operands)));
}
