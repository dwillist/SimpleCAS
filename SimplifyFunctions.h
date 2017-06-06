#ifndef _SIMPLIFY_FUNCTIONS_
#define _SIMPLIFY_FUNCTIONS_

#include <boost/multiprecision/cpp_int.hpp>

#include "Expression.h"
#include "RationalExpression.h"


#include <vector>

namespace SimplifyFunctions{
// Simplify verbosity
  namespace BM = boost::multiprecision;

  bool isInteger(Expression * expr);

  bool isRational(Expression * expr);

  bool isVariable(Expression * expr);

  bool isUndefined(Expression * expr);

  bool isExponent(Expression * expr);

  bool isSum(Expression * expr);

  bool isProduct(Expression * expr);
  
  bool isLogorithm(Expression * expr);

  std::vector<Expression * > buildBinaryVector(Expression * E1, Expression * E2);

  bool ptrLessThan(Expression * lhs, Expression * rhs);

///
/// Exponent Simplification Functions
///

  /**
    params: two expressions representing base and exponent of a ExponentExpression
    return: boolean value indicating if expression is UNDEFINED
  */
  bool isUndefinedExponent(Expression * base, Expression * exponent);

  /**
    params: two expressions representing the base and exponenet of an ExponentExpression
    return: Expression of
  */
  Expression * makeUndefinedExponenet(Expression * base, Expression * exponent);

  bool simplifiableToRational(Expression * base,Expression * exponent);

  Expression * simplifyBothRational(Expression * base,Expression * exponent);

  Expression * simplifyBaseRational(Expression * base,Expression * exponent);

  Expression * simplifyExponentRational(Expression * base,Expression * exponent);

  /**
    params: a rational base and a rational (with 1 as the denominator) integer_exponent
    return: the rational value equivalent to base^integer_exponent
      -watch out conversion could be very lossy due to forced conversion from
      integer_exponent to type int (anything larger results in uncomputable exponenets)
  */
  RationalExpression* rational_pow(Expression * base,Expression * integer_exponent);

  bool hasRationalExponent(Expression * E);
  ///
  /// General Addition and Multiplication transformations
  ///

  /**
   @params: an expression expr
   @return: weather or not the expression is a negative (does not include rational)
      - not that due to negative numbers begin stored as -1 * expr, this checks if the
      - expression is of this form
      - Note: will not work for rational numbers
  */
  bool isNegativeExpr(Expression * expr);

  bool hasConstant(Expression * expr);

  /**
   @params: an expression to strip of constant
   @return: an expression where we have taken away constant
   - Note if passed a RationalExpression will return the RationalExpression(0);
   - generally used to strip constants from product during factoring transformations
  */
  Expression * stripConstant(Expression * expr);

  BM::cpp_rational getConstant(Expression * expr,BM::cpp_rational default_val = 0);

  BM::cpp_rational getExponentConstant(Expression * expr,BM::cpp_rational default_val = 1);

  ///
  /// Level Reducer (for all associative operations)
  ///

  Expression * levelReduce(
          Expression * to_simplify,
          Expression * expression_create_function(std::vector<Expression*>)
        );

  Expression * sum_create_function(std::vector<Expression * > operand_vector);
  Expression * product_create_function(std::vector<Expression * > operand_vector);

  ///
  /// Addition Reduction
  ///

  Expression * sumSimplfy(Expression * E);

  ///
  /// Product Reduction
  ///

  Expression * productSimplify(Expression * E);


  ///
  /// Logorithm Reduction
  ///

  Expression * logorithmBothRational(Expression * base, Expression * argument);
  
  Expression * logorithmNonRationalBase(Expression * base, Expression * argument);

  Expression * logorithmSum(Expression * base, Expression * argument);

  Expression * logorithmProduct(Expression * base, Expression * argument);
  
  Expression * logorithmExponent(Expression * base, Expression * argument);
  
  Expression * logorithmRational(Expression * base, Expression * argument);

  ///
  /// Logorithm Creation
  ///
  
  Expression * makeNaturalLog(Expression * argument);
  
  //
  // Difference Creation
  //
  
  Expression * makeDifference(Expression * minuend,Expression * subtrahend);
  
  //
  // Quotent Creation
  //
  
  Expression * makeQuotent(Expression * dividend,Expression * divisor);
  
}

#endif
