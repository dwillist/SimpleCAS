#include <vector>
#include <string>
#include <map>

#include "Rational.h"
#include "FunctionTags.h"

///
/// CONSTRUCTORS
///
Expression::Expression(
    int max_operands_int,
    int min_operands_int,
    bool communative_bool,
    bool associative_bool,
    Rational value_rational,
    std::string var_name_string,
    std::vector<*Expression> operands_vector,
  ) : max_operands(max_operands_int),
      min_operands(min_operands_int),
      communative(communative_bool),
      associative(associative_bool),
      value(value_rational),
      var_name(var_name_string),
      operands(operands_vector)
      {}

Expression(const Expression & other){
  if(*this != other){
    max_operands = E.max_operands;
    min_operands = E.min_operands;
    communative = E.communative;
    value = E.value;
    var_name = E.var_name;
    _delete_operands();
    for(Expression*& operand : other.operands){
      Expression to_add = (*operand); // will call copy constructor and recurse
      operands.push_back(to_add)
    }
  }
}


virtual Expression::~Expression(){
  for( Expresion*& E : operands){
    if( E != 0){
      delete E;
      E = 0;
    }
  }
}

//
// Getters
//

std::string Expression::getTag(){
  return tag;
}

bool isCommunative(){
  return communative;
}

bool isAssociative(){
  return associative;
}

bool isVariable(){
  return variable;
}

bool isRational(){
  return tag == FunctionTags.VARIABLE;
}

bool isUndefined(){
  return undefined;
}

int size(){
  return operands.size();
}

//virtual Rational getValue() = 0;

//virtual string get_name() = 0;

virtual std::string to_string(){
  std:: string to_return = "";
  for(Expression*& operand : operands){
    to_return += " " + operand.to_string() + " ";
  }
  return "( " + FunctionTags[getTag()] + to_return + " )";
}

virtual Expression& operator=(const Expression & other){
  if(this != other){
    _delete_operands();
    
  }
}

virtual bool operator==(const Expression& lhs, const Expression& rhs);
virtual bool operator!=(const Expression& lhs, const Expresion& rhs);
virtual bool operator< (const Expression& lhs, const Expression& rhs);
virtual bool operator> (const Expression& lhs, const Expression& rhs);
virtual bool operator<=(const Expression& lhs, const Expression& rhs);
virtual bool operator>=(const Expression& lhs, const Expression& rhs);

virtual   Expression* operator[](int pos);


//
// CAS functions
//

Expression * simplify() = 0;


//
// Helper Functions
//
void _delete_operands(){
  for(Expression*& operand : operands){
    delete operand; // should recurively delete all operands in our Expression Tree
    operand = 0; // set pointer to null
  }
  operands.clear();
}
