#include <boost/multiprecision/cpp_int.hpp>
#include <boost/assign/list_of.hpp>
#include <string>
#include <vector>
#include <iostream>

#include "SumExpression.h"
#include "ProductExpression.h"
#include "ExponentExpression.h"
#include "Expression.h"
#include "FunctionTags.h"
#include "SimplifyFunctions.h"

//Namespaces to reduce verbosity
namespace SF = SimplifyFunctions;
namespace FT = FunctionTags;


//
// CONSTRUCTORS
//

ExponentExpression::ExponentExpression(std::vector<std::unique_ptr<Expression> > exponent_operands) :
  Expression(FT::EXPONENT,
    2,
    2,
    false,
    false,
    boost::multiprecision::cpp_rational(),
    std::string(),
    exponent_operands)
    {}

ExponentExpression::ExponentExpression(std::unique_ptr<Expression> base,std::unique_ptr<Expression> exponent) :
  ExponentExpression(SF::makeBinaryVector(base,exponent)){}

ExponentExpression::ExponentExpression(const Expression & E) : Expression(E){
    tag = FT::EXPONENT;
  }


std::unique_ptr<Expression> ExponentExpression::clone() const{
  return clone(0,size());
}

std::unique_ptr<Expression> ExponentExpression::clone(std::size_t begin, std::size_t end) const{
  std::unique_ptr<Expression> to_return (new ExponentExpression(clone_operands(begin,end)));
  return to_return->simplify();
}

ExponentExpression::ExponentExpression(Expression && other) :
Expression(other)
{
  tag = FT::EXPONENT;
}


//Virtual Functions
boost::multiprecision::cpp_rational ExponentExpression::getValue() const{
  return boost::multiprecision::cpp_rational(0);
}

//
// CAS functions
//



std::unique_ptr<Expression> ExponentExpression::simplify(){
  std::cout << "calling Exponent simplify" << std::endl;
  std::unique_ptr<Expression> base(getOperand(0)->simplify());
  std::unique_ptr<Expression> exponent(getOperand(1)->simplify());
  if(SF::isRational(base) && SF::isRational(exponent)){
    std::cout << "both ratonal: " << toString() << std::endl;
    return SF::simplifyBothRational(base,exponent);
  }
  else if(SF::isRational(base)){
    std::cout << "base ratonal" << std::endl;
    return SF::simplifyBaseRational(base,exponent);
  }
  else if(SF::isRational(exponent)){
    std::cout << "exponent ratonal" << std::endl;
    return SF::simplifyExponentRational(base,exponent);
  }
  // other simplifications
  std::cout << "no simplification" << std::endl;
  std::unique_ptr<Expression> to_return = new ExponentExpression(base,exponent);
  return to_return;
}

std::unique_ptr<Expression> ExponentExpression::derivative(std::string with_respect_to){
  std::unique_ptr<Expression> base_derivative(getOperand(0)->derivative(with_respect_to));
  std::unique_ptr<Expression> exp_derivative(getOperand(1)->derivative(with_respect_to));
  std::unique_ptr<Expression> base_clone(getOperand(0)->clone());
  std::unique_ptr<Expression> exp_clone(getOperand(1)->clone());

  std::unique_ptr<Expression> first_prod(
                                      new ProductExpression( base_derivative->clone(), SF::makeQuotent(exp_clone->clone(),base_clone->clone()))
                                         );
  std::unique_ptr<Expression> second_prod(new ProductExpression(exp_derivative->clone(),SF::makeNaturalLog(base_clone->clone())));
  std::unique_ptr<Expression> sum_expr(new SumExpression(first_prod,second_prod));
  return new ProductExpression(new ExponentExpression(base_clone,exp_clone),sum_expr);
}
