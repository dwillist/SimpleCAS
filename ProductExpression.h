#ifndef _PRODUCT_EXPRESSION_H_
#define _PRODUCT_EXPRESSION_H_

#include "Expression.h"
#include "Rational.h"

class ProductExpression : public Expression{
  public:
    //
    // CONSTRUCTORS
    //

    ProductExpression(std::vector<Expression * > product_operands);
    ProductExpression(const ProductExpression & R); // Copy constuctor
    ProductExpression(const Expression & E); // conversion of arbitrary expression to sum

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
