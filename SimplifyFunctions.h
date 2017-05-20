#ifndef _SIMPLIFY_FUNCTIONS_
#define _SIMPLIFY_FUNCTIONS_

#include <boost/multiprecision/cpp_int.hpp>

#include "Expression.h"
#include "Rational.h"
#include "RationalExpression.h"
#include "Factories.h"
#include "RationalFunctions.h"


#include <vector>

namespace SimplifyFunctions{
  // Simplify verbosity
  namespace BM = boost::multiprecision;

  bool isInteger(RationalExpression * expr);

  bool isRational(Expression * expr);

  bool isVariable(Expression * expr);

  bool isUndefined(Expnression * expr);

  namespace ExponentSimplification{

    /**
      params: two expressions representing base and exponent of a ExponentExpression
      return: boolean value indicating if expression is UNDEFINED
    */
    bool SF::isUndefinedExponent(Expression * base, Expression * exponent);

    /**
      params: two expressions representing the base and exponenet of an ExponentExpression
      return: Expression of
    */
    Expression * makeUndefinedExponenet(Expression * base, Expression * exponent);

    bool SF::simplifiableToRational(RationalExpression * base,RationalExpression * exponent);

    Expression * simplifyBothRational(Expression * base,Expression * exponent);

    Expression * simplifyBaseRational(Expression * base,Expression * exponent);

    Expression * simplifyExponentRational(Expression * base,Expression * exponent);

    /**
      params: a rational base and a rational (with 1 as the denominator) integer_exponent
      return: the rational value equivalent to base^integer_exponent
        -watch out conversion could be very lossy due to forced conversion from
        integer_exponent to type int (anything larger results in uncomputable exponenets)
    */
    RationalExpression* rational_pow(RationalExpression * base,RationalExpression * integer_exponent);
  }

}

#endif
