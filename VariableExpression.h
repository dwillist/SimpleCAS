#ifndef _VARIABLE_EXPRESSION_H
#define _VARIABLE_EXPRESSION_H

#include <string>
#include <boost/multiprecision/cpp_int.hpp>

#include "Expression.h"

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
    virtual boost::multiprecision::cpp_rational getValue() const;

    // See Base class comments
    virtual std::string getName() const;

    virtual std::string toString() const;

    //
    // Operators
    //

    // Assignment / mutable operators
    virtual Expression& operator=(const Expression & other);

    // Relational Operators
    virtual bool operator==(const Expression& rhs) const;
    virtual bool operator< (const Expression& rhs) const;

    // access operator, basically give us access to
    virtual   Expression* operator[](int pos);


    //
    // CAS functions
    //

    virtual Expression * simplify();
};


#endif
