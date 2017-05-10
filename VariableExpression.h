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

    //
    // virtual functions
    //

    // See Base class comments
    virtual Rational getValue() const;

    // See Base class comments
    virtual string getName() const;

    virtual std::string toString() const;

    //
    // Operators
    //

    // Assignment / mutable operators
    virtual Expression& operator=(const Expression & other);

    // Relational Operators
    virtual bool operator==(const Expression& lhs, const Expression& rhs) const;
    virtual bool operator!=(const Expression& lhs, const Expresion& rhs) const;
    virtual bool operator< (const Expression& lhs, const Expression& rhs) const;
    virtual bool operator> (const Expression& lhs, const Expression& rhs) const;
    virtual bool operator<=(const Expression& lhs, const Expression& rhs) const;
    virtual bool operator>=(const Expression& lhs, const Expression& rhs) const;

    // access operator, basically give us access to
    virtual   Expression* operator[](int pos);


    //
    // CAS functions
    //

    Expression * simplify;
};


#endif
