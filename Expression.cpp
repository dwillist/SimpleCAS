#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

#include "FunctionTags.h"
#include "Expression.h"

#include "RationalExpression.h"
#include "SumExpression.h"
#include "ProductExpression.h"
#include "ExponentExpression.h"
#include "LogExpression.h"

///
/// CONSTRUCTORS
///

Expression::Expression(
    std::string tag_string, // A string denoting the type of expression
    std::size_t max_operands_size_t,
    std::size_t min_operands_size_t,
    bool communative_bool,
    bool associative_bool,
    boost::multiprecision::cpp_rational value_rational,
    std::string var_name_string,
    std::vector<std::unique_ptr<Expression>> operands_vector
  ) :
      tag(tag_string),
      max_operands(max_operands_size_t),
      min_operands(min_operands_size_t),
      communative(communative_bool),
      associative(associative_bool),
      value(value_rational),
      var_name(var_name_string),
      operands(std::move(operands_vector))
      {
        if(size() > max_operands || size() < min_operands){
          throw "invalid number of arguments to Expression constructor";
        }
      }

Expression::Expression(const Expression & other){
  if(*this != other){
    tag = other.getTag();
    max_operands = other.max_operands;
    min_operands = other.min_operands;
    associative = other.associative;
    communative = other.communative;
    value = other.value;
    var_name = other.var_name;
    deletePtrVec(std::move(operands));
    operands = other.clone_operands(0,other.size());
    //for(std::unique_ptr<Expression> operand : other.operands){
      //operands
    //}
  }
}

// Move constructor
Expression::Expression(Expression && other):
tag(std::move(other.tag)),
max_operands(std::move(other.max_operands)),
min_operands(std::move(other.min_operands)),
associative(std::move(other.associative)),
communative(std::move(other.communative)),
value(std::move(other.value)),
var_name(std::move(other.var_name)){
  deletePtrVec(std::move(operands));
  operands = other.clone_operands(0,other.size());
}

///
/// Destructor
///

Expression::~Expression(){
  for( std::unique_ptr<Expression>& E : operands){
    E.reset();
  }
}

//
// Getters
//

std::string Expression::getTag() const{
  return tag;
}

bool Expression::isCommunative() const{
  return communative;
}

bool Expression::isAssociative() const{
  return associative;
}

std::size_t Expression::size() const{
  return operands.size();
}

boost::multiprecision::cpp_rational Expression::getValue() const{
  throw "Expression has no value";
  return value;
}

std::string Expression::getName() const{
  throw "tried to get name from Expression class";
  return std::string();
}

//
// Setters
//

std::string Expression::toString() const{
  std::string to_return = "";
  for(std::unique_ptr<Expression> const & operand : operands){
    to_return += " " + operand->toString();
  }
  return "( " + FunctionTags::tag_to_print[getTag()] + to_return + " )";
}

void Expression::swap(Expression & other){
  using std::swap;
  swap(tag,other.tag);
  swap(max_operands,other.max_operands);
  swap(tag,other.tag);
  swap(min_operands,other.min_operands);
  swap(communative,other.communative);
  swap(associative,other.associative);
  swap(value,other.value);
  swap(var_name,other.var_name);
  swap(operands,other.operands);
}

//
// Operators
//


// implementation makes use of Copy-swap idiom for assignment
Expression& Expression::operator=(const Expression & other){
  Expression to_swap = Expression(other);
  to_swap.swap(*this);
  return *this;
}

// NOTE: all compairison operators assume that both lhs, and rhs are in cononical form
// so they are equivalent if and only if their syntax trees are equivalent.
// this is not alwasy a valid assumption.

// assumes both sides have been simplified to a cononical form
bool Expression::operator==(const Expression& rhs) const{
  if(getTag() == rhs.getTag() && size() == rhs.size()){
    for(int i = 0; i < size(); ++i){
      if(getOperand(i) != rhs.getOperand(i)){ //
        return false;
      }
    }
    return true;
  }
  return false;
}

bool Expression::operator!=(const Expression& rhs)  const{
  return !(*this == rhs);
}

bool Expression::operator< (const Expression& rhs) const{
  int lhs_prec = FunctionTags::precidence_map[getTag()];
  int rhs_prec = FunctionTags::precidence_map[rhs.getTag()];
  if(lhs_prec == rhs_prec){ //should work
    for(int i = 0; i < std::min(size(),rhs.size()); ++i){
      if(getOperand(i) == rhs.getOperand(i)){
        continue;
      }
      else{
        return getOperand(i) < getOperand(i);
      }
    }
    return size() < rhs.size();
  }
  return lhs_prec < rhs_prec;
}

bool Expression::operator>(const Expression& rhs) const{
  return !(*this < rhs) && (*this != rhs);
}

bool Expression::operator<=(const Expression& rhs) const{
  return (*this < rhs) || (*this == rhs);
}
bool Expression::operator>=(const Expression& rhs) const{
  return (*this > rhs) || (*this == rhs);
}


//TODO: fix this and below deffinition
std::unique_ptr<Expression> Expression::getOperand(std::size_t pos) const{
  return operands[pos]->clone();
}

//std::unique_ptr<Expression> Expression::getClone(std::size_t pos) const{
  //return operands[pos]->clone();
//}


//
// CAS functions
//

std::unique_ptr<Expression> Expression::simplify(){
  return clone();
}

 std::unique_ptr<Expression> Expression::derivative(std::string with_respect_to){
  return clone();
}


//
// Helper Functions
//

std::vector<std::unique_ptr<Expression> > Expression::clone_operands(std::size_t begin,std::size_t end) const{
  std::vector<std::unique_ptr<Expression> > to_return;
  for(std::size_t i = begin; i < std::min(end,size()); ++i){
    to_return.push_back(getOperand(i));
  }
  return to_return;
}

std::unique_ptr<Expression> Expression::clone(std::size_t begin,std::size_t end) const{
  throw "base Expression should not be cloned";
}
std::unique_ptr<Expression> Expression::clone() const{
  throw "base Expression should not be cloned";
}

void deletePtrVec(std::vector<std::unique_ptr<Expression> > to_delete){
  for(std::unique_ptr<Expression>& operand : to_delete ){
    operand.reset(); // should recurively delete all operands in our Expression Tree
  }
  to_delete.clear();
}


//
//Arithmetic operators
//

std::unique_ptr<Expression> operator+(std::unique_ptr<Expression> const & lhs,
                                      std::unique_ptr<Expression> const & rhs){
  return std::unique_ptr<Expression>(new SumExpression(lhs->clone(),rhs->clone()));
}

std::unique_ptr<Expression> operator-(std::unique_ptr<Expression> const & lhs,
                                      std::unique_ptr<Expression> const & rhs){
  std::unique_ptr<Expression> neg_rational(new RationalExpression(-1));
  std::unique_ptr<Expression> neg_product(rhs * neg_rational);
  return std::unique_ptr<Expression>(new SumExpression(lhs->clone(),std::move(neg_product)));
}

std::unique_ptr<Expression> operator*(std::unique_ptr<Expression> const & lhs,
                                      std::unique_ptr<Expression> const & rhs){
  return std::unique_ptr<Expression>(new ProductExpression(lhs->clone(),rhs->clone()));
}


std::unique_ptr<Expression> operator/(std::unique_ptr<Expression> const & lhs,
                                      std::unique_ptr<Expression> const & rhs){
  std::unique_ptr<Expression> neg_rational(new RationalExpression(-1));
  std::unique_ptr<Expression> neg_exp(exp(rhs->clone(),neg_rational));
  return std::unique_ptr<Expression>(new ExponentExpression(lhs->clone(),std::move(neg_exp)));
}

std::unique_ptr<Expression> log(std::unique_ptr<Expression> const & lhs,
                                std::unique_ptr<Expression> const & rhs){
  return std::unique_ptr<Expression>(new LogExpression(lhs->clone(),rhs->clone()));
}

std::unique_ptr<Expression> exp(std::unique_ptr<Expression> const & lhs,
                                std::unique_ptr<Expression> const & rhs){
  return std::unique_ptr<Expression>(new SumExpression(lhs->clone(),rhs->clone()));
}



