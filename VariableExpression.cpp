#include <string>
#include <stdexcept>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

#include "RationalExpression.h"
#include "VariableExpression.h"
#include "Expression.h"
#include "FunctionTags.h"

//
// CONSTRUCTORS
//
VariableExpression::VariableExpression(std::string name) :
  Expression(FunctionTags::VARIABLE,0,0,false,false,boost::multiprecision::cpp_rational(),name)
  {}


//
// virtual functions
//

// See Base class comments
boost::multiprecision::cpp_rational VariableExpression::getValue() const{
  throw "VariableExpression has no value to get";
}

// See Base class comments
std::string VariableExpression::getName() const{
  return var_name;
}

std::string VariableExpression::toString() const{
  return VariableExpression::getName();
}

//
// Setters
//

//
// Operators
//

Expression& VariableExpression::operator=(const Expression & other){
  var_name = other.getName();
  return *this;
}

// Relational Operators
bool VariableExpression::operator==(const Expression& rhs) const{
  return getTag() == rhs.getTag() && getName() == rhs.getName();
}
bool VariableExpression::operator< (const Expression& rhs) const{
  int lhs_prec = FunctionTags::precidence_map[getTag()];
  int rhs_prec = FunctionTags::precidence_map[rhs.getTag()];
  if(lhs_prec == rhs_prec){
    return getName() < rhs.getName();
  }
  return lhs_prec < rhs_prec;
}

// access operator, basically give us access to
Expression* VariableExpression::getOperand(int pos){
  throw "Variable expression has no operands to access[]";
  return 0;
}


//
// CAS functions
//

Expression * VariableExpression::simplify(){
  return clone();
}

Expression * VariableExpression::derivative(std::string with_respect_to){
  if(getName() == with_respect_to){
    return new RationalExpression(1);
  }
  return new RationalExpression(0);
}

//
// DeepCopy Functions
//

Expression * VariableExpression::clone() const{
  return clone(0,size());
}

Expression * VariableExpression::clone(std::size_t begin, std::size_t end) const{
  return new VariableExpression(this->getName());
}
