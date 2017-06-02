#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>

#include "SumExpression.h"
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
    true,
    true,
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
  Expression * to_return = new ProductExpression(clone_operands(begin,end));
  return to_return->simplify();
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

Expression * ProductExpression::derivative(std::string with_respect_to){
  ProductExpression * lhs = new ProductExpression(operands[0]->derivative(with_respect_to),clone(1,size()));
  ProductExpression * rhs = new ProductExpression(operands[0],clone(1,size())->derivative(with_respect_to));
  return new SumExpression(lhs,rhs);
}
