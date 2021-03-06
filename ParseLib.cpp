#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>


#include "FunctionTags.h"
#include "RationalExpression.h"
#include "VariableExpression.h"
#include "SumExpression.h"
#include "ProductExpression.h"
#include "ExponentExpression.h"
#include "LogExpression.h"
#include "UndefinedExpression.h"
#include "SimplifyFunctions.h"

#include "ParseLib.h"



namespace PL = ParseLib;
namespace BM = boost::multiprecision;
namespace FT = FunctionTags;

bool PL::isOpenParen(std::string c){
  return c == "(";
}

bool PL::isCloseParen(std::string c){
  return c == ")";
}

bool PL::isRational(std::string & s){
  bool slash = false;
  std::size_t i = 0;
  if(s[i] == '-'){
    ++i;
  }
  for(; i < s.size(); ++i){
    if(s[i] == '/'){
      if(slash){
        return false;
      }
      slash = true;
    }
    else if(!('0' <= s[i] && s[i] <= '9')){
      return false;
    }
  }
  return true;
}

bool PL::isVariable(std::string & s){
  for(std::size_t i = 0; i < s.size(); ++i){
    if(!(('a' <= s[i] && s[i] <= 'z') || ('A' <= s[i] && s[i] <= 'Z'))){
      return false;
    }
  }
  return true;
}


bool PL::isSumSymbol(std::string & s){
  return s == FT::tag_to_print[FT::SUM];
}

bool PL::isProductSymbol(std::string & s){
  return s == FT::tag_to_print[FT::PRODUCT];
}

bool PL::isExponentSymbol(std::string & s){
  return s == FT::tag_to_print[FT::EXPONENT];
}

bool PL::isLogorithmSymbol(std::string & s){
  return s == FT::tag_to_print[FT::LOGORITHM];
}

std::unique_ptr<Expression> PL::makeSum(std::vector<std::unique_ptr<Expression> > expression_vec){
  return std::unique_ptr<Expression>(new SumExpression(std::move(expression_vec)));
}

std::unique_ptr<Expression> PL::makeProduct(std::vector<std::unique_ptr<Expression> > expression_vec){
  return std::unique_ptr<Expression>(new ProductExpression(std::move(expression_vec)));
}

std::unique_ptr<Expression> PL::makeExponent(std::vector<std::unique_ptr<Expression> > expression_vec){
  return std::unique_ptr<Expression>(new ExponentExpression(std::move(expression_vec)));
}

std::unique_ptr<Expression> PL::makeRational(std::string & rational_string){
  if(isRational(rational_string)){
    return std::unique_ptr<Expression>(new RationalExpression(BM::cpp_rational(rational_string)));
  }
  throw "non rational name";
  return 0;
}

std::unique_ptr<Expression> PL::makeLogorithm(std::vector<std::unique_ptr<Expression> > expression_vec){
  return std::unique_ptr<Expression>(new LogExpression(std::move(expression_vec)));
}

std::unique_ptr<Expression> PL::makeVariable(std::string & variable_string){
  if(isVariable(variable_string)){
    return std::unique_ptr<Expression>(new VariableExpression(variable_string));
  }
  throw "non variable name";
  return std::unique_ptr<Expression>(nullptr);
}

std::unique_ptr<Expression> PL::makeExpression(std::vector<std::string> & s_vector, std::size_t & pos){
  std::size_t original_pos = pos;
  std::vector<std::unique_ptr<Expression>> expressions;
  std::unique_ptr<Expression> (*expression_build)(std::vector<std::unique_ptr<Expression>>);
  for(; pos < s_vector.size(); pos++){
    std::cout << "current string : " << s_vector[pos] << std::endl;
    if(PL::isOpenParen(s_vector[pos]) && pos > original_pos){
      expressions.push_back(PL::makeExpression(s_vector,pos));
    }
    else if(PL::isOpenParen(s_vector[pos])){
      continue;
    }
    else if(PL::isRational(s_vector[pos])){
      expressions.push_back(PL::makeRational(s_vector[pos]));
    }
    else if(PL::isSumSymbol(s_vector[pos])){
      expression_build = PL::makeSum;
    }
    else if(PL::isProductSymbol(s_vector[pos])){
      expression_build = PL::makeProduct;
    }
    else if(PL::isExponentSymbol(s_vector[pos])){
      expression_build = PL::makeExponent;
    }
    else if (PL::isLogorithmSymbol(s_vector[pos])){
      expression_build = PL::makeLogorithm;
    }
    else if(PL::isVariable(s_vector[pos])){
      expressions.push_back(PL::makeVariable(s_vector[pos]));
    }
    else if(isCloseParen(s_vector[pos])){
      return expression_build(std::move(expressions));
    }
    else{
      std::cout << "unknown expression element: " << s_vector[pos] << std::endl;
    }
  }
  return 0;
}


std::vector<std::string> PL::breakString(std::string & s, std::string break_on){
  std::vector<std::string> to_return;
  std::string::iterator iter = s.begin();
  std::string::iterator next;
  while(iter < s.end()){
    while(std::count(break_on.begin(),break_on.end(),*iter))
      iter++;
  next = std::find_first_of(iter,s.end(),break_on.begin(),break_on.end());
  to_return.push_back(std::string(iter,next));
  iter = next;
  }
  return to_return;
}



std::unique_ptr<Expression> PL::parse(std::string & s){
  std::vector<std::string> s_vector = PL::breakString(s," ");
  std::size_t pos = 0;
  return PL::makeExpression(s_vector,pos);
}
