
#include <string>
#include <stdexcept>

#include "Expression.h"
#include "Rational.h"
#include "FunctionTags.h"

//
// CONSTRUCTORS
//
VariableExpression(std::string name) :
  Expression(0,0,false,false,Rational(),name)
  {}


//
// virtual functions
//

// See Base class comments
virtual Rational getValue(){
  throw std::exception("VariableExpression has no value to get")
}

// See Base class comments
virtual string getName(){
  return var_name;
}

virtual std::string toString(){
  return get_name();
}

//
// Setters
//

//
// Operators
//

// Relational Operators
virtual bool operator==(const Expression& lhs, const Expression& rhs){
  return lhs.getTag() == rhs.getTag() && lhs.getName() == rhs.getName();
}
virtual bool operator< (const Expression& lhs, const Expression& rhs){
  int lhs_prec = FunctionTags::precidence_map[lhs.getTag()];
  int rhs_prec = FunctionTags::precidence_map[rhs.getTag()];
  if lhs_prec == rhs_prec{
    return lhs.getName() < rhs.getName();
  }
}

// access operator, basically give us access to
virtual Expression* operator[](int pos){
  throw std::exception("Variable expression has no operands to access[]");
  return 0;
}


//
// CAS functions
//

Expression * simplify{
  return this;
}
