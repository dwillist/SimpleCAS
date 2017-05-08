#ifndef _RATIONAL_EXPRESSION_H
#define _RATIONAL_EXPRESSION_H

#include <string>

#include "Expression.h"
#include "Rational.h"

class RationalExpression : public Expression{
  public:

    //
    // CONSTRUCTORS
    //
    RationalExpression(Rational R);
    RationalExpression(const RationalExpression & R);

    //
    // Dtor
    //
    virtual ~RationalExpression();

    //overwritten functions

    // see base class comments
    virtual Rational getValue();

    // see base class comments
    virtual std::string get_name();

    virtual std::string to_string();

    //
    // Setters
    //

    //
    // Operators
    //

    // Assignment / mutable operators
    virtual Expression& operator=(const Expression & other);

    // Relational Operators
    virtual bool operator==(const Expression& lhs, const Expression& rhs);
    virtual bool operator!=(const Expression& lhs, const Expresion& rhs);
    virtual bool operator< (const Expression& lhs, const Expression& rhs);
    virtual bool operator> (const Expression& lhs, const Expression& rhs);
    virtual bool operator<=(const Expression& lhs, const Expression& rhs);
    virtual bool operator>=(const Expression& lhs, const Expression& rhs);

    // access operator, basically give us access to
    virtual   Expression* operator[](int pos);


    //
    // CAS functions
    //

    Expression * simplify();

};


#endif
