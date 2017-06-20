#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>

#include "UndefinedExpression.h"
#include "SumExpression.h"
#include "ProductExpression.h"
#include "Expression.h"
#include "FunctionTags.h"
#include "SimplifyFunctions.h"


namespace SF = SimplifyFunctions;


//
// CONSTRUCTORS
//

ProductExpression::ProductExpression(std::vector<std::unique_ptr<Expression>  > product_operands) :
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

ProductExpression::ProductExpression(Expression && E) : Expression(E){
  tag = FunctionTags::Product;
}

// binary constructor
ProductExpression::ProductExpression(std::unique_ptr<Expression>  E1, std::unique_ptr<Expression>  E2) :
  ProductExpression(SimplifyFunctions::makeBinaryVector(E1,E2)){}


std::unique_ptr<Expression>  ProductExpression::clone() const{
  return clone(0,size());
}

std::unique_ptr<Expression>  ProductExpression::clone(std::size_t begin, std::size_t end) const{
  std::unique_ptr<Expression>  to_return(new ProductExpression(clone_operands(begin,end)));
  return to_return->simplify();
}

//
// CAS functions
//

std::unique_ptr<Expression>  ProductExpression::simplify(){
  if(size() == 1){
    return getOperand(0)->clone();
  }
  else{
    std::vector<std::unique_ptr<Expression> > simp_ops;
    for(std::size_t i = 0; i < size(); ++i){
      simp_ops.push_back(getOperand(i)->simplify());
    }
    std::unique_ptr<Expression>  new_prod = SimplifyFunctions::levelReduce(
            new ProductExpression(simp_ops),
            SF::product_create_function);
    return SF::productSimplify(new_prod);
  }
}

std::unique_ptr<Expression>  ProductExpression::derivative(std::string with_respect_to){
  if(size() >= 2){
    std::unique_ptr<Expression>  lhs(new ProductExpression(operands[0]->derivative(with_respect_to),clone(1,size())));
    std::unique_ptr<Expression>  rhs(new ProductExpression(operands[0]->clone(),clone(1,size())->derivative(with_respect_to)));
    return std::unique_ptr<Expression>(new SumExpression(std::move(lhs),std::move(rhs)));
  }
  else if( size() == 1){
    return getOperand(0)->derivative(with_respect_to);
  }
  return std::unique_ptr<Expression>(new UndefinedExpression(this));
}
