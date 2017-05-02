// class of Rational Expressions
#ifndef _RATIONAL_EXPRESSION_H_
#define _RATIONAL_EXPRESSION_H_

#include "Rational.h"
#include "Expression.h"

class RationalExpression : public Expression{
private:
  Rational expr_value;
public:
  //
  // Constructor
  //
  RationalExpression(const Rational & value);
  RationalExpression(const RationalExpression & expr);

  //
  // Destructor
  //
  virtual ~RationalExpression();

  //
  // Operand Manipulations
  //

    /**
      @params: E is an expresion we are going to add to operands
      @return: False we cannot add operands to a RationalExpression
    */
    bool virtual addOperand(Expression * E);

    /**
      @params: position of Expression in operands vector
      @return: False Rational expression have no Operands.
    */
    bool virtual deleteOperand(int pos);

};



#endif
