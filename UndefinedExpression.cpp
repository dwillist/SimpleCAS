#include <boost/multiprecision/cpp_int.hpp>
#include <boost/assign/list_of.hpp>
#include <string>
#include <vector>

#include "Expression.h"
#include "UndefinedExpression.h"
#include "FunctionTags.h"

  //
  // CONSTRUCTORS
  //


UndefinedExpression(std::vector<Expression * > undefined_operand):
  Expression(
    FunctionTags::UNDEFINED,
    0,
    0,
    false,
    false,
    boost::multiprecision::cpp_rational value_rational = boost::multiprecision::cpp_rational(),
    std::string var_name_string = std::string(),
    std::vector<Expression*> operands_vector = std::vector<Expression*>())
    {}

UndefinedExpression(const Expression * E) : UndefinedExpression(boost::assign::list_of(E)){}

UndefinedExpression(const Expression & E) : Expression(E){
  tag = FunctionTags::UNDEFINED;
}

//
// CAS functions
//


boost::multiprecision::cpp_rational getValue() const{
  return boost::multiprecision::cpp_rational(0);
}

Expression * UndefinedExpression::simplify(){
  return UndefinedExpression(operands[0]->simplify());
}
