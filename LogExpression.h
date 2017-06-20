#ifndef LogExpression_h
#define LogExpression_h

#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>

#include "Expression.h"
#include "SimplifyFunctions.h"

class LogExpression : public Expression{
public:

  //
  // CONSTRUCTORS
  //

  LogExpression(std::vector<std::unique_ptr<Expression>  > exponent_operands);
  LogExpression(std::unique_ptr<Expression> base,std::unique_ptr<Expression> argument);
  LogExpression(const Expression & E);
  LogExpression(Expression && E);

  /**
   params: None
   return: rational number 0, exponents should not have constants
   */
  virtual boost::multiprecision::cpp_rational getValue() const;


  virtual std::unique_ptr<Expression>  clone() const;

  virtual std::unique_ptr<Expression>  clone(std::size_t begin, std::size_t end) const;

  //
  // CAS functions
  //

  virtual std::unique_ptr<Expression>  simplify();

  virtual std::unique_ptr<Expression>  derivative(std::string with_respect_to);

};


#endif
