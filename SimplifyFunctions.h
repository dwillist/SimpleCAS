#ifndef _SIMPLIFY_FUNCTIONS_
#define _SIMPLIFY_FUNCTIONS_

#include <boost/multiprecision/cpp_int.hpp>

#include "Expression.h"
#include "RationalExpression.h"


#include <vector>

// Note:
// all simplify and make functions consume the pointers passed to them

namespace SimplifyFunctions{
// Simplify verbosity
  namespace BM = boost::multiprecision;

  bool isInteger(std::unique_ptr<Expression> const & expr);

  bool isRational(std::unique_ptr<Expression> const & expr);

  bool isVariable(std::unique_ptr<Expression> const & expr);

  bool isUndefined(std::unique_ptr<Expression> const & expr);

  bool isExponent(std::unique_ptr<Expression> const & expr);

  bool isSum(std::unique_ptr<Expression> const & expr);

  bool isProduct(std::unique_ptr<Expression> const & expr);

  bool isLogorithm(std::unique_ptr<Expression> const & expr);

  std::vector<std::unique_ptr<Expression> > makeBinaryVector(std::unique_ptr<Expression> E1,
                                                              std::unique_ptr<Expression> E2);

  bool ptrLessThan(std::unique_ptr<Expression> const & lhs, std::unique_ptr<Expression> const & rhs);

///
/// Exponent Simplification Functions
///

  /**
    params: two expressions representing base and exponent of a ExponentExpression
    return: boolean value indicating if expression is UNDEFINED
  */
  bool isUndefinedExponent(std::unique_ptr<Expression> const & base,
                           std::unique_ptr<Expression> const & exponent);

  /**
    params: two expressions representing the base and exponenet of an ExponentExpression
    return: Expression of
  */
  std::unique_ptr<Expression> makeUndefined(std::unique_ptr<Expression> expr);
  
  std::unique_ptr<Expression> makeUndefinedExponenet(std::unique_ptr<Expression> base,
                                                     std::unique_ptr<Expression> exponent);


  bool simplifiableToRational(std::unique_ptr<Expression> const & base,
                              std::unique_ptr<Expression> const & exponent);

  std::unique_ptr<Expression> simplifyBothRational(std::unique_ptr<Expression> base,
                                                    std::unique_ptr<Expression> exponent);

  std::unique_ptr<Expression> simplifyBaseRational(std::unique_ptr<Expression> base,
                                                    std::unique_ptr<Expression> exponent);

  std::unique_ptr<Expression> simplifyExponentRational(std::unique_ptr<Expression> base,
                                                        std::unique_ptr<Expression> exponent);

  /**
    params: a rational base and a rational (with 1 as the denominator) integer_exponent
    return: the rational value equivalent to base^integer_exponent
      -watch out conversion could be very lossy due to forced conversion from
      integer_exponent to type int (anything larger results in uncomputable exponenets)
  */
  std::unique_ptr<Expression> rational_pow(std::unique_ptr<Expression> base,
                                   std::unique_ptr<Expression> integer_exponent);

  bool hasRationalExponent(std::unique_ptr<Expression> const & E);
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
  bool isNegativeExpr(std::unique_ptr<Expression> const & expr);

  bool hasConstant(std::unique_ptr<Expression> const & expr);

  /**
   @params: an expression to strip of constant
   @return: an expression where we have taken away constant
   - Note if passed a RationalExpression will return the RationalExpression(0);
   - generally used to strip constants from product during factoring transformations
  */
  std::unique_ptr<Expression> stripConstant(std::unique_ptr<Expression> const & expr);

  BM::cpp_rational getConstant(std::unique_ptr<Expression> const & expr,
                               BM::cpp_rational default_val = 0);

  BM::cpp_rational getExponentConstant(std::unique_ptr<Expression> const & expr,
                                       BM::cpp_rational default_val = 1);

  ///
  /// Level Reducer (for all associative operations)
  ///

  std::unique_ptr<Expression> levelReduce(std::unique_ptr<Expression> to_simplify,
                                          std::unique_ptr<Expression> expression_create_function( std::vector< std::unique_ptr<Expression> >)
                                          );

  // The below are two functions that are passed to the level-reducer above as the expression_create_function
  // depending on the context.
  std::unique_ptr<Expression> makeSumFunction(std::vector<std::unique_ptr<Expression> > operand_vector);
  std::unique_ptr<Expression> makeProductFunction(std::vector<std::unique_ptr<Expression> > operand_vector);
  
  ///
  /// Addition Reduction
  ///

  std::unique_ptr<Expression> sumSimplfy(std::unique_ptr<Expression> E);

  ///
  /// Product Reduction
  ///

  std::unique_ptr<Expression> productSimplify(std::unique_ptr<Expression> E);


  ///
  /// Logorithm Reduction
  ///

  std::unique_ptr<Expression> simplifyLogorithmBothRational(std::unique_ptr<Expression> base,
                                                    std::unique_ptr<Expression> argument);

  std::unique_ptr<Expression> simplifyLogorithmNonRationalBase(std::unique_ptr<Expression> base,
                                                       std::unique_ptr<Expression> argument);

  std::unique_ptr<Expression> simplifyLogorithmSum(std::unique_ptr<Expression> base,
                                           std::unique_ptr<Expression> argument);

  std::unique_ptr<Expression> simplifyLogorithmProduct(std::unique_ptr<Expression> base,
                                               std::unique_ptr<Expression> argument);

  std::unique_ptr<Expression> simplifyLogorithmExponent(std::unique_ptr<Expression> base,
                                                std::unique_ptr<Expression> argument);

  std::unique_ptr<Expression> simplifyLogorithmRational(std::unique_ptr<Expression> base,
                                                std::unique_ptr<Expression> argument);

  ///
  /// Logorithm Creation
  ///

  std::unique_ptr<Expression> makeNaturalLog(std::unique_ptr<Expression> argument);

  //
  // Difference Creation
  //

  std::unique_ptr<Expression> makeDifference(std::unique_ptr<Expression> minuend,
                                             std::unique_ptr<Expression> subtrahend);

  //
  // Quotent Creation
  //

  std::unique_ptr<Expression>  makeQuotent(std::unique_ptr<Expression> dividend,
                                           std::unique_ptr<Expression> divisor);
}

#endif
