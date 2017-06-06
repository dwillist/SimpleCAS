

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

LogExpression::LogExpression(std::vector<Expression * > log_operands) :
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


LogExpression::LogExpression(Expression * base,Expression * argument) :
LogExpression(SimplifyFunctions::buildBinaryVector(base,argument)){}

LogExpression::LogExpression(const Expression & E) : Expression(E){
  tag = FunctionTags::LOGORITHM;
}


Expression * LogExpression::clone() const{
  return clone(0,size());
}

Expression * LogExpression::clone(std::size_t begin, std::size_t end) const{
  Expression * to_return = new LogExpression(clone_operands(begin,end));
  return to_return->simplify();
}


//Virtual Functions
BM::cpp_rational LogExpression::getValue() const{
  return BM::cpp_rational(0);
}

Expression * LogExpression::simplify(){
  Expression * base = getOperand(0)->simplify();
  Expression * argument = getOperand(1)->simplify();
  if(SF::isRational(base) && SF::isRational(argument)){
    return SF::logorithmBothRational(base,argument);
  }
  else if(!SF::isRational(base)){
    return SF::logorithmNonRationalBase(base, argument);
  }
  else if(SF::isSum(argument)){
    return SF::logorithmSum(base, argument);
  }
  else if(SF::isProduct(argument)){
    return SF::logorithmProduct(base, argument);
  }
  else if(SF::isExponent(argument)){
    return SF::logorithmExponent(base, argument);
  }
  else if(SF::isRational(base)){
    return SF::logorithmRational(base, argument);
  }
  else{
    std::cout<< "Error log simplification not found" << std::endl;
    return 0;
  }
}

Expression * LogExpression::derivative(std::string with_respect_to){
  // need lots of parts to do this
  Expression * argument_derivative = getOperand(1)->derivative(with_respect_to);
  Expression * base_clone = getOperand(0)->clone();
  Expression * argument_clone = getOperand(1)->clone();
  
  Expression * denom_product = new ProductExpression(argument_clone,SF::makeNaturalLog(base_clone));
  return new ProductExpression(argument_derivative,SF::makeQuotent(new RationalExpression(1), denom_product));
  
}

