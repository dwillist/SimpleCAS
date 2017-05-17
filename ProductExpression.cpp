#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>

#include "ProductExpression.h"
#include "Expression.h"
#include "FunctionTags.h"

//
// CONSTRUCTORS
//

ProductExpression::ProductExpression(std::vector<Expression * > product_operands) :
  Expression(FunctionTags::PRODUCT,
    -1, // this is max value of size_t due to two's complement
    0,
    false,
    false,
    false,
    boost::multiprecision::cpp_rational(),
    std::string(),
    product_operands)
    {}

ProductExpression::ProductExpression(const Expression & E) : Expression(E){
    tag = FunctionTags::PRODUCT;
  }

//
// CAS functions
//

Expression * ProductExpression::simplify(){
    return this;
}
