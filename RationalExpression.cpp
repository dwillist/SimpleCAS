#include <string>
#include <stdexcept>
#include <sstream>

#include "RationalExpression.h"
#include "Expression.h"
#include "FunctionTags.h"
#include <boost/multiprecision/cpp_int.hpp>

//
// CONSTRUCTORS
//
RationalExpression::RationalExpression(boost::multiprecision::cpp_rational R) :
  Expression(FunctionTags::RATIONAL,0,0,false,false,R) // rest of args we let be default see Expression constructor
  {}

//overwritten functions

// see base class comments
boost::multiprecision::cpp_rational RationalExpression::getValue() const{
  return value;
}

// see base class comments
std::string RationalExpression::getName() const{
  throw "Rational expression has no name";
  return std::string();
}

std::string RationalExpression::toString() const{
  std::stringstream ss;
  ss << getValue();
  return ss.str();
}

//
// Setters
//

//
// Operators
//

Expression& RationalExpression::operator=(const Expression & other){
  value = other.getValue();
  return *this;
}
// Relational Operators
bool RationalExpression::operator==(const Expression& rhs) const{
  return getTag() == rhs.getTag() && getValue() == rhs.getValue();
}
//virtual bool operator!=(const Expression& lhs, const Expresion& rhs)
 bool RationalExpression::operator< (const Expression& rhs) const{
  int lhs_prec = FunctionTags::precidence_map[getTag()];
  int rhs_prec = FunctionTags::precidence_map[rhs.getTag()];
  if(lhs_prec == rhs_prec){ //should work
    return getValue() < rhs.getValue();
  }
  return lhs_prec < rhs_prec;
}

// access operator, basically give us access to
Expression* RationalExpression::getOperand(int pos){
  throw "no operands to access[] for RationalExpression";
  return 0;
}


//
// CAS functions
//

 Expression * RationalExpression::simplify(){
  return this;
}
