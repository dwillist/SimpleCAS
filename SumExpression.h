#ifndef _SUM_EXPRESSION_H_
#define _SUM_EXPRESSION_H_

#include "Expression.h"
#include "Rational.h"

class SumExpression : public Expression{
  public:

    //
    // CONSTRUCTORS
    //

    SumExpression(std::vector<Expression * > sum_operands);
    SumExpression(const SumExpression & R); // Copy constuctor
    SumExpression(const Expression & E); // conversion of arbitrary expression to sum

    //
    // Dtor
    //
    virtual ~VariableExpression();

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
