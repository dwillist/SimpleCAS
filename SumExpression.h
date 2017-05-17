#ifndef _SUM_EXPRESSION_H_
#define _SUM_EXPRESSION_H_

#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>

#include "Expression.h"

class SumExpression : public Expression{
  public:

    //
    // CONSTRUCTORS
    //

    SumExpression(std::vector<Expression * > sum_operands);
    SumExpression(const Expression & E);

    // See Base class comments
    //virtual boost::multiprecision::cpp_rational getValue() const;

    // See Base class comments
    //virtual std::string getName() const;

    //
    // CAS functions
    //

    virtual Expression * simplify();

};

#endif
