#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>

#include "ExponentExpression.h"
#include "Expression.h"
#include "FunctionTags.h"

//
// CONSTRUCTORS
//

ExponentExpression::ExponentExpression(std::vector<Expression * > exponent_operands) :
  Expression(FunctionTags::EXPONENT,
    2, // this is max value of size_t due to two's complement
    0,
    false,
    false,
    false,
    boost::multiprecision::cpp_rational(),
    std::string(),
    exponent_operands)
    {}

ExponentExpression::ExponentExpression(const Expression & E) : Expression(E){
    tag = FunctionTags::EXPONENT;
  }

//
// CAS functions
//

Expression * ExponentExpression::simplify(){
    return this;
}
