#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>

#include "ProductExpression.h"
#include "Expression.h"
#include "FunctionTags.h"
#include "SimplifyFunctions.h"

//
// CONSTRUCTORS
//

ProductExpression::ProductExpression(std::vector<Expression * > product_operands) :
  Expression(FunctionTags::PRODUCT,
    -1, // this is max value of size_t due to two's complement
    0,
    false,
    false,
    boost::multiprecision::cpp_rational(),
    std::string(),
    product_operands)
    {}

ProductExpression::ProductExpression(const Expression & E) : Expression(E){
    tag = FunctionTags::PRODUCT;
  }

// binary constructor
ProductExpression::ProductExpression(Expression * E1, Expression * E2) :
  ProductExpression(SimplifyFunctions::buildBinaryVector(E1,E2)){}


Expression * ProductExpression::clone() const{
  return clone(0,size());
}

Expression * ProductExpression::clone(std::size_t begin, std::size_t end) const{
  return new ProductExpression(clone_operands(begin,end));
}

//
// CAS functions
//

Expression * ProductExpression::simplify(){
    return this;
}
