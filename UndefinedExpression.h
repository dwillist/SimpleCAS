#ifndef _UNDEFINED_EXPRESSION_H
#define _UNDEFINED_EXPRESSION_H

#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>

#include "Expression.h"

//purpose of this class is basically to wrap another Expression just so it is clear
//that it is undefined

class UndefinedExpression : public Expression{
  public:

    //
    // CONSTRUCTORS
    //

    UndefinedExpression(std::vector<Expression * > sum_operands);
    UndefinedExpression(const Expression * E); // wrapping constructor
    UndefinedExpression(const Expression & E);


    //
    // CAS functions
    //

    //virtual std::string toString() const;

    virtual boost::multiprecision::cpp_rational getValue() const;

    virtual Expression * simplify();

};


#endif
