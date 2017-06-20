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

bool SF::isInteger(std::unique_ptr<Expression> const & expr){
  return isRational(expr) && BM::denominator(expr->getValue()) == 1;
}

bool SF::isRational(std::unique_ptr<Expression> const & expr){
  return expr->getTag() == FT::RATIONAL;
}

bool SF::isVariable(std::unique_ptr<Expression> const & expr){
  return expr->getTag() == FT::VARIABLE;
}

bool SF::isUndefined(std::unique_ptr<Expression> const & expr){
  return expr->getTag() == FT::UNDEFINED;
}

bool SF::isExponent(std::unique_ptr<Expression> const & expr){
  return expr->getTag() == FT::EXPONENT;
}

bool SF::isSum(std::unique_ptr<Expression> const & expr){
  return expr->getTag() == FT::SUM;
}

bool SF::isProduct(std::unique_ptr<Expression> const & expr){
  return expr->getTag() == FT::PRODUCT;
}

bool SF::isLogorithm(std::unique_ptr<Expression> const & expr){
  return expr->getTag() == FT::LOGORITHM;
}

std::vector<std::unique_ptr<Expression>  > SF::makeBinaryVector(std::unique_ptr<Expression> E1, std::unique_ptr<Expression> E2){
  std::vector<std::unique_ptr<Expression> > to_return = {E1,E2};
  return to_return;
}

bool SF::ptrLessThan(std::unique_ptr<Expression> const & lhs, std::unique_ptr<Expression> const & rhs){
  return (*lhs) < (*rhs);
}

bool SF::isUndefinedExponent(std::unique_ptr<Expression> const & base, std::unique_ptr<Expression> const & exponent){
  if(SF::isUndefined(base) || SF::isUndefined(exponent)){
    return true;
  }
  else if(SF::isRational(base) && base->getValue() == 0){
    return !SF::isRational(exponent) || exponent->getValue() <= 0;
  }
  return false;
}



std::unique_ptr<Expression> SF::makeUndefinedExponenet(std::unique_ptr<Expression> base, std::unique_ptr<Expression> exponent){
  //TODO: check if this works need to watch that ExponentExpression that is created
  // is not destroyed when this function goes out of range, could cause some nasty bugs
  return new unique_ptr<Expression>(UndefinedExpression(ExponentExpression(base,exponent)));
}

bool SF::simplifiableToRational(std::unique_ptr<Expression> const & base,std::unique_ptr<Expression> const & exponent){
  // want to come up with maximal bout on number of digits
  //TODO: extend this to be more useful really don't want to simplify 2 ^ 100000
  return SF::isInteger(exponent);
}

std::unique_ptr<Expression> SF::simplifyBothRational(
                                      std::unique_ptr<Expression> base,
                                      std::unique_ptr<Expression> exponent
                                      ){
  BM::cpp_rational base_value = base->getValue();
  BM::cpp_rational exponent_value = exponent->getValue();
  if(SF::isUndefinedExponent(base,exponent)){
    return SF::makeUndefinedExponenet(base,exponent);
  }
  else if(SF::simplifiableToRational(base,exponent)){
    if(base_value == 0 && exponent_value == 0){
      return std::unique_ptr<Expression>(new RationalExpression(1));
    }
    if(base_value == 0){
      return std::unique_ptr<Expression>(new RationalExpression(0));
    }
    else if(base_value == 1){
      return std::unique_ptr<Expression>(new RationalExpression(0));
    }
    else{
      return SF::rational_pow(base,exponent);
    }
  }
  else{
    return std::unique_ptr<Expression> (new ExponentExpression(base,exponent));
  }
}

std::unique_ptr<Expression> SF::simplifyBaseRational(std::unique_ptr<Expression> base,std::unique_ptr<Expression> exponent){
  if(SF::isUndefinedExponent(base,exponent)){
    return SF::makeUndefinedExponenet(base,exponent);
  }
  if(SF::isExponent(exponent)){
    // no simplification can result of
    // x ^ y ^ z if y ^ z cannot be simplified
    return unique_ptr<Expression>(new ExponentExpression(base,exponent));
  }
  else if(SF::isProduct(exponent)){
    if(isInteger(exponent->getOperand(0))
       && SF::simplifiableToRational(base,exponent->getOperand(0))){
      // then we have a simplification of the following form
      // r^5*y -> (r^5)^y where r is rational
      return unique_ptr<Expression>(new ExponentExpression(
                  rational_pow(base,exponent->getOperand(0)),
                  exponent->clone(1,exponent->size())
                ));
    }
    return unique_ptr<Expression>(new ExponentExpression(base,exponent));
  }
  else if(SF::isSum(exponent)){
    if(isInteger(exponent->getOperand(0)) && SF::simplifiableToRational(base,exponent->getOperand(0))){
      // we have a a simplification of the folowing form
      // r^5+y -> r^5 * r^y where r is rational
      std::unique_ptr<Expression> rational_base(rational_pow(base,exponent->getOperand(0)))
      std::unique_ptr<Expression> exponent_without_rational(new SumExpression(exponent->clone_operands(1,exponent->size())));
      std::cout << "new Exponenet String " + exponenet_without_rational->toString() << std::endl;
      // below consumes exponenet_without_rational variable via move constructor
      std::unique_ptr<Expression> variable_exponent(new ExponentExpression(base,exponent_without_rational));
      return unique_ptr<Expression>(new ProductExpression(newBase, variable_exponent));
    }
  }
  //else
  return unique_ptr<Expression>(new ExponentExpression(base,exponent));
}

// here i make the dubious simplification that (expr)^0 == 1, which is obviously not
// always true (eg expr = 0);
std::unique_ptr<Expression> SF::simplifyExponentRational(std::unique_ptr<Expression> base,std::unique_ptr<Expression> exponent){
  BM::cpp_rational exponent_value = exponent->getValue();
  if(SF::isUndefinedExponent(base,exponent)){
    return SF::makeUndefinedExponenet(base,exponent);
  }
  else if(exponent_value == 0){
    return std::unique_ptr<Expression>(new RationalExpression(1));
  }
  else if(SF::isExponent(base)){
    return std::unique_ptr<Expression>(new ExponentExpression(
      base -> getOperand(0),
      std::unique_ptr<Expression>(new ProductExpression(exponent,base->getOperand(1))
    )));
  }
  //else
  return std::unique_ptr<Expression>(new ExponentExpression(base,exponent));
}

// need this to be able to deal with negative exponents,
std::unique_ptr<RationalExpression> SF::rational_pow(std::unique_ptr<Expression> base,
                                                     std::unique_ptr<Expression> integer_exponent
                                                     ){
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
  return std::unique_ptr<RationalExpresison>(new RationalExpression(BM::cpp_rational(new_num,new_denom)));
}

bool SF::hasRationalExponent(std::unique_ptr<Expression> const & E){
  return SF::isExponent(E) && SF::isRational(E->getOperand(1));
}

///
/// General Addition and Multiplication transformations
///

bool SF::isNegativeExpr(std::unique_ptr<Expression> const & expr){
  return(expr->getTag() == FT::PRODUCT && *(expr->getOperand(0)) == RationalExpression(-1));
}

// assumes simplification
bool SF::hasConstant(std::unique_ptr<Expression> const & expr){
  return (expr->size() > 0) && SF::isRational(expr->getOperand(0));
}

std::unique_ptr<Expression> SF::stripConstant(std::unique_ptr<Expression> const & expr){
  return expr->clone(1,expr->size());
}

BM::cpp_rational SF::getConstant(std::unique_ptr<Expression> const & expr,BM::cpp_rational default_val){
  if(expr->getTag() == FT::RATIONAL){
    return expr->getValue();
  }
  else if(expr->size() > 0 && expr->getOperand(0)->getTag() == FT::RATIONAL){
    return expr->getOperand(0)->getValue();
  }
  return BM::cpp_rational(default_val);
}


BM::cpp_rational SF::getExponentConstant(std::unique_ptr<Expression> const & expr,BM::cpp_rational default_val){
  if(SF::isExponent(expr) && SF::hasRationalExponent(expr)){
    return expr->getOperand(1)->getValue();
  }
  return BM::cpp_rational(default_val);
}


///
/// Level Reducer (for all associative operations)
///

std::unique_ptr<Expression> SF::levelReduce(
          std::unique_ptr<Expression> to_simplify,
          std::unique_ptr<Expression> expression_create_function(std::vector<std::unique_ptr<Expression> >)
        ){
  std::string current_tag = to_simplify->getTag();
  if(!to_simplify->isAssociative()){
    std::cout << "operation invalid on non-associative operators" << std::endl;
    throw "operation invalid on non-associative operators";
  }
  // otherwise we may simplify
  std::vector<std::unique_ptr<Expression> > new_operands;
  for(std::size_t i = 0; i < to_simplify->size(); ++i){
    std::unique_ptr<Expression> current_expression = to_simplify->getOperand(i);
    if(current_expression -> getTag() == current_tag){
      for(std::size_t j = 0; j < current_expression->size(); ++j){
        new_operands.push_back(current_expression->getOperand(j)->clone());
      }
    }
    else{
      new_operands.push_back(current_expression->clone());
    }
  }
    return expression_create_function(std::move(new_operands));
}


std::unique_ptr<Expression> SF::makeSumFunction(std::vector<std::unique_ptr<Expression> > operand_vector){
  return std::unique_ptr<Expression>(new SumExpression(operand_vector));
}

std::unique_ptr<Expression> SF::makeProductFunction(std::vector<std::unique_ptr<Expression> > operand_vector){
  return std::unique_ptr<Expression>(new ProductExpression(operand_vector));
}

///
/// Addition Reduction
///



std::unique_ptr<Expression> SF::sumSimplfy(std::unique_ptr<Expression> E){
  // assumed we are passed an expression E that has been simplified then levelReduced

  //create function pointer comp_ptr to use in map
  BM::cpp_rational constant;
  //
  std::vector<std::unique_ptr<Expression> > new_operands;
  bool (*comp_ptr)(Expression*,Expression*) = SF::ptrLessThan;
  std::map<Expression*,BM::cpp_rational,bool(*)(Expression*,Expression*)> op_map (comp_ptr);
  for(std::size_t i = 0; i < E->size(); ++i){
    std::unique_ptr<Expression> current_operand = E->getOperand(i);
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
  if(constant != 0){
    std::unique_ptr<Expression> to_pb(new(RationalExpression(constant)));
    new_operands.push_back(to_pb);
  }
  for(auto map_element: op_map){
    if(map_element.second != 1){
      std::unique_ptr<Expression> factor(new RationalExpression(map_element.second));
      std::unique_ptr<Expression> prod(new ProductExpression(factor,map_element.first->clone()));
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
  return std::unique_ptr<Expression>(new SumExpression(new_operands));
}

///
/// Product Simplification
///


std::unique_ptr<Expression> SF::productSimplify(std::unique_ptr<Expression> E){
  // assumed we are passed an expression E that has been simplified then levelReduced

  //create function pointer comp_ptr to use in map
  BM::cpp_rational constant = BM::cpp_rational(1);
  //
  std::vector<std::unique_ptr<Expression> > new_operands;
  bool (*comp_ptr)(Expression*,Expression*) = SF::ptrLessThan;
  std::map<Expression*,BM::cpp_rational,bool(*)(Expression*,Expression*)> op_map (comp_ptr);
  for(std::size_t i = 0; i < E->size(); ++i){
    std::unique_ptr<Expression> current_operand = E->getOperand(i);
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
  //std::vector<std::unique_ptr<Expression> > new_operands; declared above
  if( constant == 0){
    deletePtrVec(new_operands);
    return unique_ptr<Expression>(new RationalExpression(0));
  }

  else if(constant != 1){
    new_operands.push_back(new RationalExpression(constant));
  }
  for(auto map_element: op_map){
    if(map_element.second != 1){
      //NOTE: really should use unique pointers
      Rationalstd::unique_ptr<Expression> exponent(new RationalExpression(map_element.second));
      Exponentstd::unique_ptr<Expression> new_exp_expr(new ExponentExpression(map_element.first->clone(),exponent));
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
  return unique_ptr<Expression>(new ProductExpression(new_operands));
}



///
/// Logorithm Reduction
///

std::unique_ptr<Expression> SF::simplifyLogorithmBothRational(std::unique_ptr<Expression> base,std::unique_ptr<Expression> argument){
  BM::cpp_rational base_rational = base->getValue();
  BM::cpp_rational argument_rational = argument->getValue();
  BM::cpp_dec_float_100 base_dec = static_cast<BM::cpp_dec_float_100>(base_rational);
  BM::cpp_dec_float_100 argument_dec = static_cast<BM::cpp_dec_float_100>(argument_rational);
  BM::cpp_dec_float_100 log_result = BM::log(argument_dec) / BM::log(base_dec);
  return std::unique_ptr<Expression>(new RationalExpression(log_result.convert_to<BM::cpp_rational>()));
}

std::unique_ptr<Expression> SF::simplifyLogorithmNonRationalBase(std::unique_ptr<Expression> base, std::unique_ptr<Expression> argument){
  std::unique_ptr<Expression> inner_log(new LogExpression(std::unique_ptr<Expression>(new RationalExpression(2)),base->clone()));
  std::unique_ptr<Expression> denom(new ExponentExpression(inner_log,std::unique_ptr<Expression>(new RationalExpression(-1))));
  //std::unique_ptr<Expression> denom(new ExponentExpression(new LogExpression(new RationalExpression(2),base->clone()), new RationalExpression(-1)));
  std::unique_ptr<Expression> num(new std::unique_ptr<Expression(new LogExpression(std::unique_ptr<Expression>(new RationalExpression(2)),argument->clone())));
  return std::unique_ptr<Expression>(new ProductExpression(num,denom));
}

std::unique_ptr<Expression> SF::simplifyLogorithmSum(std::unique_ptr<Expression> base, std::unique_ptr<Expression> argument){
  return std::unique_ptr<Expression>(new LogExpression(base,argument));
}

std::unique_ptr<Expression> SF::simplfyLogorithmProduct(std::unique_ptr<Expression> base, std::unique_ptr<Expression> argument){
  std::vector<std::unique_ptr<Expression> > sum_vector;
  for(std::size_t i = 0; i < argument->size(); ++i){
    sum_vector.push_back(std::unique_ptr<Expression>(new LogExpression(base->clone(),argument->getClone(i))));
  }
  return std::unique_ptr<Expression>(new SumExpression(sum_vector));
}

std::unique_ptr<Expression> SF::simplfyLogorithmExponent(std::unique_ptr<Expression> base, std::unique_ptr<Expression> argument){
  std::unique_ptr<Expression> exp_base = argument ->getClone(0);
  std::unique_ptr<Expression> exp_exponent = argument -> getClone(1);
  std::unique_ptr<Expression> new_log(new LogExpression(base, exp_base));
  return std::unique_ptr<Expression>(new ProductExpression(exp_exponent,new_log));
}

std::unique_ptr<Expression> SF::simplifyLogorithmRational(std::unique_ptr<Expression> base, std::unique_ptr<Expression> argument){
  return std::unique_ptr<Expression>(new LogExpression(base,argument));
}

///
/// Logorithm Creation
///

std::unique_ptr<Expression> SF::makeNaturalLog(std::unique_ptr<Expression> argument){
  return std::unique_ptr<Expression>(newLogExpression(
    std::unique_ptr<Expression>(new RationalExpression(
      static_cast<BM::cpp_rational>(boost::math::float_constants::e)),argument->clone())));
}

//
// Difference Creation
//

std::unique_ptr<Expression> SF::makeDifference(std::unique_ptr<Expression> minuend,std::unique_ptr<Expression> subtrahend){
  std::unique_ptr<Expression> subtrahend_expr(new ProductExpression(std::unique_ptr<Expression>(new RationalExpression(-1)),subtrahend->clone()));
  return std::unique_ptr<Expression>( new SumExpression(minuend->clone(),subtrahend_expr));
}


//
// Quotent Creation
//

std::unique_ptr<Expression> SF::makeQuotent(std::unique_ptr<Expression> dividend,std::unique_ptr<Expression> divisor){
  std::unique_ptr<Expression> divisor_expr = new ExponentExpression(divisor->clone(),new RationalExpression(-1));
  return new ProductExpression(dividend->clone(),divisor_expr);
}
)
