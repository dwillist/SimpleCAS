#ifndef _EXPONENT_EXPRESSION_H_
#define _EXPONENT_EXPRESSION_H_

#include "Expression.h"
#include "Rational.h"

class ExponentExpression : public Expression{
  public:
    //
    // CONSTRUCTORS
    //

    ExponentExpression(std::vector<Expression * > product_operands);
    ExponentExpression(const ExponentExpression & R); // Copy constuctor
    ExponentExpression(const Expression & E); // conversion of arbitrary expression to sum

    //
    // Dtor
    //
    virtual ~ExponentExpression();

    //
    // Virtual functions
    //

    // See Base class comments
    virtual Rational getValue();

    // See Base class comments
    virtual string get_name();

    //
    // CAS functions
    //
    Expression * simplify();

};


#endif
