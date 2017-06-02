

#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>

#include "LogExpression.h"
#include "Expression.h"
#include "SimplifyFunctions.h"
#include "FunctionTag.h"

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
  {}


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
  
}

Expression * LogExpression::derivative(std::string with_respect_to);

