#include <vector>
#include <string>
#include <map>
#include <stdexcept>

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
    Rational value_rational = Rational(),
    std::string var_name_string = "",
    std::vector<*Expression> operands_vector = std::vector<*Expression>(),
  ) : max_operands(max_operands_int),
      min_operands(min_operands_int),
      communative(communative_bool),
      associative(associative_bool),
      value(value_rational),
      var_name(var_name_string),
      operands(operands_vector)
      {
        if(size() > max_operands || size < min_operands){
          throw std::exception("invalid number of arguments to Expression constructor");
        }
      }

Expression::Expression(const Expression & other){
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

bool Expression::isCommunative(){
  return communative;
}

bool Expression::isAssociative(){
  return associative;
}

bool Expression::isVariable(){
  return getTag() == FunctionTags::VARIABLE;
}

bool Expression::isRational(){
  return getTag() == FunctionTags::RATIONAL;
}

bool Expression::isUndefined(){
  return undefined;
}

int Expression::size(){
  return operands.size();
}

//virtual Rational getValue() = 0;

//virtual string get_name() = 0;

//
// Setters
//

virtual std::string Expression::to_string(){
  std:: string to_return = "";
  for(Expression*& operand : operands){
    to_return += " " + operand.to_string() + " ";
  }
  return "( " + FunctionTags[getTag()] + to_return + " )";
}

void Expression::swap(Expression & other) throw(){
  using std::swap;
  swap(tag,other.tag);
  swap(max_operands,other.max_operands);
  swap(tag,other.tag);
  swap(min_operands,other.min_operands);
  swap(communative,other.communative);
  swap(associative,other.associative);
  swap(undefined,other.undefined);
  swap(value,other.value);
  swap(var_name,other.var_name);
  swap(operands,other.operands);
}

//
// Operators
//


// implementation makes use of Copy-swap idiom for assignment
virtual Expression::Expression& operator=(const Expression & other){
  other.swap(*this);
  return *this;
}

// NOTE: all compairison operators assume that both lhs, and rhs are in cononical form
// so they are equivalent if and only if their syntax trees are equivalent.
// this is not alwasy a valid assumption.

// assumes both sides have been simplified to a cononical form
virtual bool Expression::operator==(const Expression& lhs, const Expression& rhs){
  if(lhs.getTag() == rhs.getTag() && lhs.size() == rhs.size()){
    for(int i = 0; i < lhs.size(); ++i){
      if(*lhs[i] != *rhs[i]){ //
        return false;
      }
    }
    return true;
  }
  return false;
}
virtual bool Expression::operator!=(const Expression& lhs, const Expresion& rhs){
  return !(lhs == rhs);
}
virtual bool Expression::operator< (const Expression& lhs, const Expression& rhs){
  int lhs_prec = FunctionTags::precidence_map[lhs.getTag()];
  int rhs_prec = FunctionTags::precidence_map[rhs.getTag()];
  if lhs_prec == rhs_prec{ //should work
    return std::less(lhs.operator.begin(),lhs.operator.end(),
                 rhs.operator.begin(),rhs.operator.end(),
                 [](const Expression*new_lhs,const Expression*new_rhs){*new_lhs < *new_rhs;});
  }
  return lhs_prec < rhs_prec;
}

virtual bool Expression::operator> (const Expression& lhs, const Expression& rhs){
  return !(lhs < rhs) && (lhs != rhs)
}
virtual bool Expression::operator<=(const Expression& lhs, const Expression& rhs){
  return (lhs < rhs) || (lhs == rhs);
}
virtual bool Expression::operator>=(const Expression& lhs, const Expression& rhs){
  return (lhs > rhs) || (lhs == rhs);
}

virtual Expression* Expression::operator[](int pos){
  return operands[pos];
}


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
