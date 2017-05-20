#ifndef _EXPONENT_EXPRESSION_H_
#define _EXPONENT_EXPRESSION_H_


#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>

#include "Expression.h"

class ExponentExpression : public Expression{
  public:

    //
    // CONSTRUCTORS
    //

    ExponentExpression(std::vector<Expression * > exponent_operands);
    ExponentExpression(Expression * base,Expression * exponent);
    ExponentExpression(const Expression & E);

    /**
      params: None
      return: rational number 0, exponents should not have constants
    */
    virtual boost::multiprecision::cpp_rational getValue();

    //
    // CAS functions
    //

    virtual Expression * simplify();

};

#endif
