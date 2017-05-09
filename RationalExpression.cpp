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
  return lhs.getTag() == rhs.getTag() // PICK UP HERE
}
virtual bool operator!=(const Expression& lhs, const Expresion& rhs);
virtual bool operator< (const Expression& lhs, const Expression& rhs);
virtual bool operator> (const Expression& lhs, const Expression& rhs);
virtual bool operator<=(const Expression& lhs, const Expression& rhs);
virtual bool operator>=(const Expression& lhs, const Expression& rhs);

// access operator, basically give us access to
virtual   Expression* operator[](int pos);


//
// CAS functions
//

Expression * simplify(){
  return this;
}
