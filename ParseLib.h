#ifndef _PARSELIB_H_
#define _PARSELIB_H_

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "RationalExpression.h"
#include "VariableExpression.h"
#include "SumExpression.h"
#include "ProductExpression.h"
#include "ExponentExpression.h"
#include "UndefinedExpression.h"
#include "SimplifyFunctions.h"


namespace ParseLib{

  bool isOpenParen(std::string c);

  bool isCloseParen(std::string c);

  bool isRational(std::string & s);

  bool isVariable(std::string & s);

  bool isSumSymbol(std::string & s);

  bool isProductSymbol(std::string & s);

  bool isExponentSymbol(std::string & s);

  Expression * makeSum(std::vector<Expression *> expression_vec);

  Expression * makeProduct(std::vector<Expression *> expression_vec);

  Expression * makeExponent(std::vector<Expression *> expression_vec);

  Expression * makeRational(std::string & rational_string);

  Expression * makeVariable(std::string & variable_string);

  Expression * makeExpression(std::vector<std::string> & s, std::size_t & pos);

  std::vector<std::string> breakString(std::string & s, std::string break_on);

  Expression * parse(std::string & s);

}


#endif
