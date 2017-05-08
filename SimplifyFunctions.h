#ifndef _SIMPLIFY_FUNCTIONS_
#define _SIMPLIFY_FUNCTIONS_

#include "Expression.h"
#include "Rational.h"
#include "RationalExpression.h"
#include "Factories.h"


#include <vector>

namespace SimplifyFunctions{
  /**
    @params: expression
    @return: returns true if Expression is a basic algebraic expression
  */
  bool isBAE(Expression* expr);

  bool isASE(Expression * expr);

  /**
    @params: takes an expression E
    @return: a pointer to a new expression created by applying associative transformation
        ie: (x+y) + z = x+y+z basically reducing depth of our syntax Tree
  */
  Expression* AssociativeTransform(Expression * E);

  /**
    @params: takes an Expression E to transform, and a depth,
    @returns: A new equivalent expression where we have distrubuted multiplication over addition
              in the levels root to depth,
              a depth of -1 indicates the entire expression
  */
  Expression* AlgebraicExpand(Expression * E,int depth = -1);

  /**
    @params: an expression E to transform
    @return: a new equivalent expression where we have sorted each subexpressions operands
              if the operation is communative
  */
  Expression* CommunativeTransform(Expression * E);

  /**
    @params: an Expression E to transform
    @return: a new equivalent expression where we have preformed the following transformations
              on exponents
              i) u^n * u^m = u^(n+m)
              ii) (u^n)^m = u^(n*m)
              iii) (u*v)^n = (u^n) * (v^n)
  */
  Expression* ExponentTransform(Expression *E);

  /**
    @params: an Expression E to transform
    @return: An expression where all differences(subtractions) have been repaced with the following
        u-v = u + (-1*v);
  */
  Expression* DifferenceTransform(Expression *E);

  /**
    @params: an Expression E to transform
    @return:
  */
  Expression* QuotentTransform(Expression *E);

  /**
    @params: an Expression E to transform,
    @return: a Expression simplified by using identies found in the identity table
    TODO: make sure that there are no identities in the table that create a cycle!
  */
  Expression* IdentityTransfrom(Expression *E);

  /**
    @params: and Expression E to transform
    @return: A expression where we have preformed unary simplifications
  */
  Expresion* UnaryTransforms(Expression *E);

  /**

  */
  Expression* NumericalTransforms(Expression *E);


  SimplifySum(Expression* sum_expression);
  SimplifyProduct(Expression* prod_expression);
  SimplifyPower(Expression* power_expreesion);

}

//
// IMPLEMENTATION
//


bool SimplifyFunctions::isASE(Expression * expr){
  if(expr -> isRational() || expr-> isVariable()){
    return true;
  }
  return false;
}

bool SimplifyFunctions:isBAE(Expression * expr){
  if(expr -> isVariable() || expr-> isRational()){ return true;}
  else if()
}

#endif
