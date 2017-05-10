#ifndef _DIFFERENCE_EXPRESSION_H_
#define _DIFFERENCE_EXPRESSION_H_

#include "Expression.h"
#include "Rational.h"

class DifferenceExpression : public Expression{
  public:

    //
    // CONSTRUCTORS
    //

    DifferenceExpression(std::vector<Expression * > sum_operands);
    DifferenceExpression(const DifferenceExpression & R); // Copy constuctor
    DifferenceExpression(const Expression & E); // conversion of arbitrary expression to sum

    //
    // Dtor
    //
    virtual ~DifferenceExpression();

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
