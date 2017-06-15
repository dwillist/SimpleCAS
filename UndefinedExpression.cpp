#include <boost/multiprecision/cpp_int.hpp>
#include <boost/assign/list_of.hpp>
#include <string>
#include <vector>
#include <stdexcept>

#include "Expression.h"
#include "UndefinedExpression.h"
#include "FunctionTags.h"

  //
  // CONSTRUCTORS
  //


UndefinedExpression::UndefinedExpression(std::vector<std::unique_ptr<Expression>  > undefined_operands):
  Expression(
    FunctionTags::UNDEFINED,
    1,
    0,
    false,
    false,
    boost::multiprecision::cpp_rational(),
    std::string(),
    undefined_operands)
    {}

UndefinedExpression::UndefinedExpression(std::unique_ptr<Expression>  E) :
  UndefinedExpression(wrapWithVector(E)){}

//
UndefinedExpression::UndefinedExpression(const Expression & E) : Expression(E){
  tag = FunctionTags::UNDEFINED;
}



std::unique_ptr<Expression>  UndefinedExpression::clone() const{
  return clone(0,size());
}

std::unique_ptr<Expression>  UndefinedExpression::clone(std::size_t begin, std::size_t end) const{
  return std::unique_ptr<Expression>(new UndefinedExpression(clone_operands(begin,end)));
}
//
// CAS functions
//


boost::multiprecision::cpp_rational UndefinedExpression::getValue() const{
  throw "UndefinedExpression has no value";
}

std::unique_ptr<Expression>  UndefinedExpression::UndefinedExpression::simplify(){
  return std::unique_ptr<Expression>(new UndefinedExpression(operands[0]->simplify()));
}

std::unique_ptr<Expression>  UndefinedExpression::derivative(std::string with_respect_to){
  return std::unique_ptr<Expression>(new UndefinedExpression(operands[0]->derivative(with_respect_to)));
}




std::vector<std::unique_ptr<Expression>  > wrapWithVector(std::unique_ptr<Expression>  E){
  std::vector<std::unique_ptr<Expression> > to_return;
  to_return.push_back(E);
  return to_return;
}
