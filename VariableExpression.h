#ifndef _VARIABLE_EXPRESSION_H
#define _VARIABLE_EXPRESSION_H

#include <string>

#include "Expression.h"
#include "Rational.h"

class VariableExpression : public Expression{
  public:

    //
    // CONSTRUCTORS
    //
    VariableExpression(std::string name);
    VariableExpression(const VariableExpression & V);

    //
    // Dtor
    //
    virtual ~VariableExpression();

    //
    // virtual functions
    //

    // See Base class comments
    virtual Rational getValue();

    // See Base class comments
    virtual string get_name();

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

    Expression * simplify;
};


#endif
