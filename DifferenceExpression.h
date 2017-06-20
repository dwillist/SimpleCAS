#ifndef _DIFFERENCE_EXPRESSION_H_
#define _DIFFERENCE_EXPRESSION_H_

#include <boost/multiprecision/cpp_int.hpp>

#include "Expression.h"

class DifferenceExpression : public Expression{
  public:

    //
    // CONSTRUCTORS
    //

    DifferenceExpression(std::vector<Expression * > sum_operands);
    DifferenceExpression(const DifferenceExpression & R); // Copy constuctor
    DifferenceExpression(const Expression & E); // conversion of arbitrary expression to sum
    DifferenceExpression(Expression && other);

    //
    // Dtor
    //
    virtual ~DifferenceExpression();

    //
    // Virtual functions
    //

    // See Base class comments
  virtual boost::multiprecision::cpp_rational getValue();

    // See Base class comments
  virtual std::string get_name();

    //
    // CAS functions
    //

    Expression * simplify();

};

#endif
