#ifndef _RATIONAL_EXPRESSION_H
#define _RATIONAL_EXPRESSION_H

#include <string>
#include <boost/multiprecision/cpp_int.hpp>

#include "Expression.h"

class RationalExpression : public Expression{
  public:

    //
    // CONSTRUCTORS
    //
    RationalExpression(boost::multiprecision::cpp_rational R);

    //overwritten functions

    // see base class comments
    virtual boost::multiprecision::cpp_rational getValue() const;

    // see base class comments
    virtual std::string getName() const;

    virtual std::string toString() const;

    //
    // Setters
    //

    //
    // Operators
    //

    // Assignment / mutable operators
    virtual Expression& operator=(const Expression & other);

    // Relational Operators
    virtual bool operator==(const Expression& rhs) const;
    virtual bool operator< (const Expression& rhs) const;

    // access operator, basically give us access to
    virtual Expression* getOperand(int pos);


    //
    // CAS functions
    //

    virtual Expression * simplify();

    //
    // DeepCopy Functions
    //

    virtual Expression * clone() const;

    virtual Expression * clone(std::size_t begin, std::size_t end) const;

};


#endif
