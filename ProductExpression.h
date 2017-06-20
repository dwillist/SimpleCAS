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

    ProductExpression(std::vector<std::unique_ptr<Expression>  > product_operands);
    ProductExpression(const Expression & E);
    ProductExpression(std::unique_ptr<Expression>  E1, std::unique_ptr<Expression>  E2); //binary constructor
    ProductExpression(const Expression & E,std::size_t begin,std::size_t end);
    ProductExpression(Expression && E);

    //
    // CAS functions
    //

    virtual std::unique_ptr<Expression>  simplify();

    virtual std::unique_ptr<Expression>  derivative(std::string with_respect_to);

    //
    // DeepCopy Functions
    //

    virtual std::unique_ptr<Expression> clone() const;

    virtual std::unique_ptr<Expression> clone(std::size_t begin, std::size_t end) const;

};

#endif
