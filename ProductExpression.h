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
    ProductExpression(Expression * E1, Expression * E2); //binary constructor
    ProductExpression(const Expression & E,std::size_t begin,std::size_t end);

    //
    // CAS functions
    //

    virtual Expression * simplify();

    virtual Expression * derivative(std::string with_respect_to);

    //
    // DeepCopy Functions
    //

    virtual Expression * clone() const;

    virtual Expression * clone(std::size_t begin, std::size_t end) const;

};

#endif
