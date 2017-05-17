#ifndef _PRODUCT_EXPRESSION_H_
#define _PRODUCT_EXPRESSION_H_

#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>

#include "Expression.h"

class ProductExpression : public Expression{
  public:

    //
    // CONSTRUCTORS
    //

    ProductExpression(std::vector<Expression * > product_operands);
    ProductExpression(const Expression & E);

    //
    // CAS functions
    //

    virtual Expression * simplify();

};

#endif
