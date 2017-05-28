#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>

#include "ProductExpression.h"
#include "Expression.h"
#include "FunctionTags.h"
#include "SimplifyFunctions.h"


namespace SF = SimplifyFunctions;


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
  if(size() == 1){
    return getOperand(0)->clone();
  }
  else{
    std::vector<Expression *> simp_ops;
    for(std::size_t i = 0; i < size(); ++i){
      simp_ops.push_back(getOperand(i)->simplify());
    }
    Expression * new_prod = SimplifyFunctions::levelReduce(
            new ProductExpression(simp_ops),
            SF::product_create_function);
    return SF::productSimplify(new_prod);
  }
}
