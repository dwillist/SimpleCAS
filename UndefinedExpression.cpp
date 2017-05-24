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


UndefinedExpression::UndefinedExpression(std::vector<Expression * > undefined_operands):
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

UndefinedExpression::UndefinedExpression(Expression * E) :
  UndefinedExpression(wrapWithVector(E)){}

//
UndefinedExpression::UndefinedExpression(const Expression & E) : Expression(E){
  tag = FunctionTags::UNDEFINED;
}



Expression * UndefinedExpression::clone() const{
  return clone(0,size());
}

Expression * UndefinedExpression::clone(std::size_t begin, std::size_t end) const{
  return new UndefinedExpression(clone_operands(begin,end));
}
//
// CAS functions
//


boost::multiprecision::cpp_rational UndefinedExpression::getValue() const{
  throw "UndefinedExpression has no value";
}

Expression * UndefinedExpression::UndefinedExpression::simplify(){
  return new UndefinedExpression(operands[0]->simplify());
}


std::vector<Expression * > wrapWithVector(Expression * E){
  std::vector<Expression *> to_return;
  to_return.push_back(E);
  return to_return;
}
