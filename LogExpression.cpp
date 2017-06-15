

#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>

#include "LogExpression.h"
#include "Expression.h"
#include "SimplifyFunctions.h"
#include "FunctionTags.h"
#include "ProductExpression.h"
#include "RationalExpression.h"

namespace SF = SimplifyFunctions;
namespace BM = boost::multiprecision;

  
//
// CONSTRUCTORS
//

LogExpression::LogExpression(std::vector<std::unique_ptr<Expression>  > log_operands) :
Expression(FunctionTags::LOGORITHM,
           2,
           2,
           false,
           false,
           BM::cpp_rational(),
           std::string(),
           log_operands)
  {
    
  }


LogExpression::LogExpression(std::unique_ptr<Expression>  base,std::unique_ptr<Expression>  argument) :
LogExpression(SimplifyFunctions::buildBinaryVector(base,argument)){}

LogExpression::LogExpression(const Expression & E) : Expression(E){
  tag = FunctionTags::LOGORITHM;
}


std::unique_ptr<Expression>  LogExpression::clone() const{
  return clone(0,size());
}

std::unique_ptr<Expression>  LogExpression::clone(std::size_t begin, std::size_t end) const{
  std::unique_ptr<Expression>  to_return(new LogExpression(clone_operands(begin,end)));
  return to_return->simplify();
}


//Virtual Functions
BM::cpp_rational LogExpression::getValue() const{
  return BM::cpp_rational(0);
}

std::unique_ptr<Expression>  LogExpression::simplify(){
  std::unique_ptr<Expression>  base = getOperand(0)->simplify();
  std::unique_ptr<Expression>  argument = getOperand(1)->simplify();
  if(SF::isRational(base) && SF::isRational(argument)){
    return SF::logorithmBothRational(std::move(base),std::move(argument));
  }
  else if(!SF::isRational(base)){
    return SF::logorithmNonRationalBase(std::move(base), std::move(argument));
  }
  else if(SF::isSum(argument)){
    return SF::logorithmSum(std::move(base), std::move(argument));
  }
  else if(SF::isProduct(argument)){
    return SF::logorithmProduct(std::move(base), std::move(argument));
  }
  else if(SF::isExponent(argument)){
    return SF::logorithmExponent(std::move(base), std::move(argument));
  }
  else if(SF::isRational(base)){
    return SF::logorithmRational(std::move(base), std::move(argument));
  }
  else{
    std::cout<< "Error log simplification not found" << std::endl;
    return 0;
  }
}

std::unique_ptr<Expression>  LogExpression::derivative(std::string with_respect_to){
  // need lots of parts to do this
  std::unique_ptr<Expression>  argument_derivative = getOperand(1)->derivative(with_respect_to);
  std::unique_ptr<Expression>  base_clone = getOperand(0)->clone();
  std::unique_ptr<Expression>  argument_clone = getOperand(1)->clone();
  
  std::unique_ptr<Expression>  denom_product(new ProductExpression(std::move(argument_clone),
                                                                   SF::makeNaturalLog(base_clone)));
  return std::unique_ptr<Expression>(new ProductExpression(argument_derivative,SF::makeQuotent(new RationalExpression(1), denom_product)));
  
}

