#include <string>
#include <stdexcept>

#include "Expression.h"
#include "Rational.h"

//
// CONSTRUCTORS
//
RationalExpression(const Rational & R) :
  Expression(0,0,false,false,R) // rest of args we let be default see Expression constructor

}

//
// Dtor
//
virtual ~RationalExpression();

//overwritten functions

// see base class comments
virtual Rational getValue(){
  return value;
}

// see base class comments
virtual std::string get_name(){
  throw std::exception("Rational expression has no name")
}

virtual std::string to_string(){
  return value.to_string(); // uses Rational interface to get string.
}

//
// Setters
//

//
// Operators
//

// Relational Operators
virtual bool operator==(const Expression& lhs, const Expression& rhs){
  return lhs.getTag() == rhs.getTag() && lhs.getValue() == rhs.getValue();
}
//virtual bool operator!=(const Expression& lhs, const Expresion& rhs)
virtual bool operator< (const Expression& lhs, const Expression& rhs){
  int lhs_prec = FunctionTags::precidence_map[lhs.getTag()];
  int rhs_prec = FunctionTags::precidence_map[rhs.getTag()];
  if lhs_prec == rhs_prec{ //should work
    return lhs.getValue() < rhs.getValue();
  }
}

// access operator, basically give us access to
virtual Expression* operator[](int pos){
  throw std::exception("no operands to access[] for RationalExpression");
}


//
// CAS functions
//

Expression * simplify(){
  return this;
}
