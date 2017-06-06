#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/math/constants/constants.hpp>
#include <map>
#include <iostream>


#include "SimplifyFunctions.h"
#include "ProductExpression.h"
#include "FunctionTags.h"
#include "Expression.h"
#include "RationalExpression.h"
#include "UndefinedExpression.h"
#include "ExponentExpression.h"
#include "SumExpression.h"
#include "ProductExpression.h"
#include "LogExpression.h"

namespace SF = SimplifyFunctions;
namespace BM = boost::multiprecision;
namespace FT = FunctionTags;

//
// Identification functions
//

bool SF::isInteger(Expression * expr){
  return isRational(expr) && BM::denominator(expr->getValue()) == 1;
}

bool SF::isRational(Expression * expr){
  return expr->getTag() == FT::RATIONAL;
}

bool SF::isVariable(Expression * expr){
  return expr->getTag() == FT::VARIABLE;
}

bool SF::isUndefined(Expression * expr){
  return expr->getTag() == FT::UNDEFINED;
}

bool SF::isExponent(Expression * expr){
  return expr->getTag() == FT::EXPONENT;
}

bool SF::isSum(Expression * expr){
  return expr->getTag() == FT::SUM;
}

bool SF::isProduct(Expression * expr){
  return expr->getTag() == FT::PRODUCT;
}

bool SF::isLogorithm(Expression * expr){
  return expr->getTag() == FT::LOGORITHM;
}

std::vector<Expression * > SF::buildBinaryVector(Expression * E1, Expression * E2){
  std::vector<Expression *> to_return = {E1,E2};
  return to_return;
}

bool SF::ptrLessThan(Expression * lhs, Expression * rhs){
  return (*lhs) < (*rhs);
}

bool SF::isUndefinedExponent(Expression * base, Expression * exponent){
  if(SF::isUndefined(base) || SF::isUndefined(exponent)){
    return true;
  }
  else if(SF::isRational(base) && base->getValue() == 0){
    return !SF::isRational(exponent) || exponent->getValue() <= 0;
  }
  return false;
}



Expression * SF::makeUndefinedExponenet(Expression * base, Expression * exponent){
  //TODO: check if this works need to watch that ExponentExpression that is created
  // is not destroyed when this function goes out of range, could cause some nasty bugs
  return new UndefinedExpression(ExponentExpression(base,exponent));
}

bool SF::simplifiableToRational(Expression * base,Expression * exponent){
  // want to come up with maximal bout on number of digits
  //TODO: extend this to be more useful really don't want to simplify 2 ^ 100000
  return SF::isInteger(exponent);
}

Expression * SF::simplifyBothRational(Expression * base,Expression * exponent){
  BM::cpp_rational base_value = base->getValue();
  BM::cpp_rational exponent_value = exponent->getValue();
  if(SF::isUndefinedExponent(base,exponent)){
    return SF::makeUndefinedExponenet(base,exponent);
  }
  else if(SF::simplifiableToRational(base,exponent)){
    if(base_value == 0 && exponent_value == 0){
      return new RationalExpression(1);
    }
    if(base_value == 0){
      return new RationalExpression(0);
    }
    else if(base_value == 1){
      return new RationalExpression(0);
    }
    else{
      return SF::rational_pow(base,exponent);
    }
  }
  else{
    return new ExponentExpression(base,exponent);
  }
}

Expression * SF::simplifyBaseRational(Expression * base,Expression * exponent){
  if(SF::isUndefinedExponent(base,exponent)){
    return SF::makeUndefinedExponenet(base,exponent);
  }
  if(SF::isExponent(exponent)){
    // no simplification can result of
    // x ^ y ^ z if y ^ z cannot be simplified
    return new ExponentExpression(base,exponent);
  }
  else if(SF::isProduct(exponent)){
    if(isInteger(exponent->getOperand(0))
       && SF::simplifiableToRational(base,exponent->getOperand(0))){
      // then we have a simplification of the following form
      // r^5*y -> (r^5)^y where r is rational
      return new ExponentExpression(
                  rational_pow(base,exponent->getOperand(0)),
                  exponent->clone(1,exponent->size())
                );
    }
    return new ExponentExpression(base,exponent);
  }
  else if(SF::isSum(exponent)){
    if(isInteger(exponent->getOperand(0))
       && SF::simplifiableToRational(base,exponent->getOperand(0))){
         // we have a a simplification of the folowing form
         // r^5+y -> r^5 * r^y where r is rational
         Expression * newBase = rational_pow(base,exponent->getOperand(0));
         Expression * newExponent = new SumExpression(exponent->clone_operands(1,exponent->size()));
      std::cout << "new Exponenet String " + newExponent->toString() << std::endl;
         return new ProductExpression(newBase, new ExponentExpression(base,newExponent));
    }
  }
  //else
  return new ExponentExpression(base,exponent);
}

// here i make the dubious simplification that (expr)^0 == 1, which is obviously not
// always true (eg expr = 0);
Expression * SF::simplifyExponentRational(Expression * base,Expression * exponent){
  BM::cpp_rational exponent_value = exponent->getValue();
  if(SF::isUndefinedExponent(base,exponent)){
    return SF::makeUndefinedExponenet(base,exponent);
  }
  else if(exponent_value == 0){
    return new RationalExpression(1);
  }
  else if(SF::isExponent(base)){
    return new ExponentExpression(
      base -> getOperand(0),
      new ProductExpression(exponent,base->getOperand(1))
    );
  }
  //else
  return new ExponentExpression(base,exponent);
}

// need this to be able to deal with negative exponents,
RationalExpression * SF::rational_pow(Expression * base,Expression * integer_exponent){
  std::cout << "rational pow called " << std::endl;
  BM::cpp_rational base_value = base->getValue();
  BM::cpp_rational integer_exponent_value = integer_exponent->getValue();
  if(BM::denominator(integer_exponent_value) != 1){
    throw std::range_error("exponent not integer");
  }
  // otherwise we have an integer exponenet
  int int_exponent = integer_exponent_value.convert_to<int>();
  BM::cpp_int new_num;
  BM::cpp_int new_denom;
  if(integer_exponent_value < 0){
    new_num = BM::pow(BM::denominator(base_value),abs(int_exponent));
    new_denom = BM::pow(BM::numerator(base_value),abs(int_exponent));
  }
  else{
    new_num = BM::pow(BM::numerator(base_value),int_exponent);
    new_denom = BM::pow(BM::denominator(base_value),int_exponent);
  }
  return new RationalExpression(BM::cpp_rational(new_num,new_denom));
}

bool SF::hasRationalExponent(Expression * E){
  return SF::isExponent(E) && SF::isRational(E->getOperand(1));
}

///
/// General Addition and Multiplication transformations
///

bool SF::isNegativeExpr(Expression * expr){
  return(expr->getTag() == FT::PRODUCT && *(expr->getOperand(0)) == RationalExpression(-1));
}

// assumes simplification
bool SF::hasConstant(Expression * expr){
  return (expr->size() > 0) && SF::isRational(expr->getOperand(0));
}

Expression * SF::stripConstant(Expression * expr){
  return expr->clone(1,expr->size());
}

BM::cpp_rational SF::getConstant(Expression * expr,BM::cpp_rational default_val){
  if(expr->getTag() == FT::RATIONAL){
    return expr->getValue();
  }
  else if(expr->size() > 0 && expr->getOperand(0)->getTag() == FT::RATIONAL){
    return expr->getOperand(0)->getValue();
  }
  return BM::cpp_rational(default_val);
}


BM::cpp_rational SF::getExponentConstant(Expression * expr,BM::cpp_rational default_val){
  if(SF::isExponent(expr) && SF::hasRationalExponent(expr)){
    return expr->getOperand(1)->getValue();
  }
  return BM::cpp_rational(default_val);
}


///
/// Level Reducer (for all associative operations)
///

Expression * SF::levelReduce(
          Expression * to_simplify,
          Expression * expression_create_function(std::vector<Expression*>)
        ){
  std::string current_tag = to_simplify->getTag();
  if(!to_simplify->isAssociative()){
    std::cout << "operation invalid on non-associative operators" << std::endl;
    throw "operation invalid on non-associative operators";
  }
  // otherwise we may simplify
  std::vector<Expression *> new_operands;
  for(std::size_t i = 0; i < to_simplify->size(); ++i){
    Expression * current_expression = to_simplify->getOperand(i);
    if(current_expression -> getTag() == current_tag){
      for(std::size_t j = 0; j < current_expression->size(); ++j){
        new_operands.push_back(current_expression->getOperand(j)->clone());
      }
    }
    else{
      new_operands.push_back(current_expression->clone());
    }
  }
    return expression_create_function(new_operands);
}


Expression * SF::sum_create_function(std::vector<Expression * > operand_vector){
  return new SumExpression(operand_vector);
}

Expression * SF::product_create_function(std::vector<Expression * > operand_vector){
  return new ProductExpression(operand_vector);
}

///
/// Addition Reduction
///



Expression * SF::sumSimplfy(Expression * E){
  // assumed we are passed an expression E that has been simplified then levelReduced

  //create function pointer comp_ptr to use in map
  BM::cpp_rational constant;
  //
  std::vector<Expression *> new_operands;
  bool (*comp_ptr)(Expression*,Expression*) = SF::ptrLessThan;
  std::map<Expression*,BM::cpp_rational,bool(*)(Expression*,Expression*)> op_map (comp_ptr);
  for(std::size_t i = 0; i < E->size(); ++i){
    Expression * current_operand = E->getOperand(i);
    if(SF::isRational(current_operand)){
      constant += SF::getConstant(current_operand);
    }
    else{
      // we assume that if current_operand is a product it must have 2 or more operands
      if(SF::isProduct(current_operand) && hasConstant(current_operand)){
        op_map[current_operand->clone(1,current_operand->size())] += SF::getConstant(current_operand,1);
      }
      else if(SF::isSum(current_operand)){
        std::cout << "Sum detected in general Reduce, this should not be here" << std::endl;
      }
      else{
        op_map[current_operand->clone()]++;
      }
    }
  }
  // now we need to turn our map into Expressions
  //std::vector<Expression *> new_operands; declared above
  if(constant != 0){
    new_operands.push_back(new RationalExpression(constant));
  }
  for(auto map_element: op_map){
    if(map_element.second != 1){
      //NOTE: really should use unique pointers
      RationalExpression * factor = new RationalExpression(map_element.second);
      ProductExpression * prod = new ProductExpression(factor,map_element.first->clone());
      new_operands.push_back(prod->simplify());
      //delete factor; // should clean up memory leaks
      //delete prod;
    }
    else{
      new_operands.push_back(map_element.first);
    }
  }
  if(new_operands.size() == 1){
    return new_operands[0];
  }
  return new SumExpression(new_operands);
}

///
/// Product Simplification
///


Expression * SF::productSimplify(Expression * E){
  // assumed we are passed an expression E that has been simplified then levelReduced

  //create function pointer comp_ptr to use in map
  BM::cpp_rational constant = BM::cpp_rational(1);
  //
  std::vector<Expression *> new_operands;
  bool (*comp_ptr)(Expression*,Expression*) = SF::ptrLessThan;
  std::map<Expression*,BM::cpp_rational,bool(*)(Expression*,Expression*)> op_map (comp_ptr);
  for(std::size_t i = 0; i < E->size(); ++i){
    Expression * current_operand = E->getOperand(i);
    if(SF::isRational(current_operand)){
      constant *= SF::getConstant(current_operand);
    }
    else{
      // we assume that if current_operand is a sum it must have 2 or more operands
      if(SF::isExponent(current_operand) && hasRationalExponent(current_operand)){
        //TODO: check if this is vaid
        op_map[current_operand->getClone(0)] += SF::getExponentConstant(current_operand);
      }
      else if(SF::isProduct(current_operand)){
        std::cout << "Sum detected in general Reduce, this should not be here" << std::endl;
      }
      else{
        op_map[current_operand->clone()]++;
      }
    }
  }
  // now we need to turn our map into Expressions
  //std::vector<Expression *> new_operands; declared above
  if( constant == 0){
    deletePtrVec(new_operands);
    return new RationalExpression(0);
  }

  else if(constant != 1){
    new_operands.push_back(new RationalExpression(constant));
  }
  for(auto map_element: op_map){
    if(map_element.second != 1){
      //NOTE: really should use unique pointers
      RationalExpression * exponent = new RationalExpression(map_element.second);
      ExponentExpression * new_exp_expr = new ExponentExpression(map_element.first->clone(),exponent);
      new_operands.push_back(new_exp_expr->simplify());
      //delete factor; // should clean up memory leaks
      //delete prod;
    }
    else{
      new_operands.push_back(map_element.first);
    }
  }
  if(new_operands.size() == 1){
    return new_operands[0];
  }
  return new ProductExpression(new_operands);
}



///
/// Logorithm Reduction
///

Expression * SF::logorithmBothRational(Expression * base, Expression * argument){
  BM::cpp_rational base_rational = base->getValue();
  BM::cpp_rational argument_rational = argument->getValue();
  BM::cpp_dec_float_100 base_dec = static_cast<BM::cpp_dec_float_100>(base_rational);
  BM::cpp_dec_float_100 argument_dec = static_cast<BM::cpp_dec_float_100>(argument_rational);
  BM::cpp_dec_float_100 log_result = BM::log(argument_dec) / BM::log(base_dec);
  return new RationalExpression(log_result.convert_to<BM::cpp_rational>());
}

Expression * SF::logorithmNonRationalBase(Expression * base, Expression * argument){
  Expression * denom = new ExponentExpression(new LogExpression(new RationalExpression(2),base->clone()), new RationalExpression(-1));
  Expression * num = new LogExpression(new RationalExpression(2),argument->clone());
  return new ProductExpression(num,denom);
}

Expression * SF::logorithmSum(Expression * base, Expression * argument){
  return new LogExpression(base->clone(),argument->clone());
}

Expression * SF::logorithmProduct(Expression * base, Expression * argument){
  std::vector<Expression * > sum_vector;
  for(std::size_t i = 0; i < argument->size(); ++i){
    sum_vector.push_back(new LogExpression(base->clone(),argument->getClone(i)));
  }
  return new SumExpression(sum_vector);
}

Expression * SF::logorithmExponent(Expression * base, Expression * argument){
  Expression * exp_base = argument ->getClone(0);
  Expression * exp_exponent = argument -> getClone(1);
  Expression * new_log = new LogExpression(base, exp_base);
  return new ProductExpression(exp_exponent,new_log);
}

Expression * SF::logorithmRational(Expression * base, Expression * argument){
  return new LogExpression(base,argument);
}

///
/// Logorithm Creation
///

Expression * SF::makeNaturalLog(Expression * argument){
  return new LogExpression(new RationalExpression(static_cast<BM::cpp_rational>(boost::math::float_constants::e)),argument->clone());
}

//
// Difference Creation
//

Expression * SF::makeDifference(Expression * minuend,Expression * subtrahend){
  Expression * subtrahend_expr = new ProductExpression(new RationalExpression(-1),subtrahend->clone());
  return new SumExpression(minuend->clone(),subtrahend_expr);
}


//
// Quotent Creation
//

Expression * SF::makeQuotent(Expression * dividend,Expression * divisor){
  Expression * divisor_expr = new ExponentExpression(divisor->clone(),new RationalExpression(-1));
  return new ProductExpression(dividend->clone(),divisor_expr);
}


