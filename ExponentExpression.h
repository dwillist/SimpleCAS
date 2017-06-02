#ifndef _EXPONENT_EXPRESSION_H_
#define _EXPONENT_EXPRESSION_H_


#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>

#include "Expression.h"
#include "SimplifyFunctions.h"

class ExponentExpression : public Expression{
  public:

    //
    // CONSTRUCTORS
    //

    ExponentExpression(std::vector<Expression * > exponent_operands);
    ExponentExpression(Expression * base,Expression * exponent);
    ExponentExpression(const Expression & E);

    /**
      params: None
      return: rational number 0, exponents should not have constants
    */
    virtual boost::multiprecision::cpp_rational getValue() const;


    virtual Expression * clone() const;

    virtual Expression * clone(std::size_t begin, std::size_t end) const;
    //
    // CAS functions
    //

    virtual Expression * simplify();
  
    virtual Expression * derivative(std::string with_respect_to);

};


#endif
