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
    ExponentExpression(const Expression & E);

    //
    // CAS functions
    //

    virtual Expression * simplify();

};

#endif
