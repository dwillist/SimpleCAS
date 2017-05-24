#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>

#include "FunctionTags.h"
#include "Expression.h"

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
    std::vector<Expression*> operands_vector
  ) :
      tag(tag_string),
      max_operands(max_operands_size_t),
      min_operands(min_operands_size_t),
      communative(communative_bool),
      associative(associative_bool),
      value(value_rational),
      var_name(var_name_string),
      operands(operands_vector)
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
    deletePtrVec(operands);
    operands = other.clone_operands(0,other.size());
    //for(Expression* operand : other.operands){
      //operands
    //}
  }
}


Expression::~Expression(){
  for( Expression*& E : operands){
    if( E != 0){
      delete E;
      E = 0;
    }
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
  for(Expression* operand : operands){
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
      if(this->operands[i] != rhs.operands[i]){ //
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
      if(operands[i] == rhs.operands[i]){
        continue;
      }
      else{
        return operands[i] < rhs.operands[i];
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

Expression* Expression::getOperand(std::size_t pos) const{
  return operands[pos];
}



//
// CAS functions
//

Expression * Expression::simplify(){
  return new Expression(*this);
}


//
// Helper Functions
//

std::vector<Expression *> Expression::clone_operands(std::size_t begin,std::size_t end) const{
  std::vector<Expression *> to_return;
  for(std::size_t i = begin; i < end; ++i){
    to_return.push_back(getOperand(i)->clone());
  }
  return to_return;
}

Expression * Expression::clone(std::size_t begin,std::size_t end) const{
  throw "base Expression should not be cloned";
}
Expression * Expression::clone() const{
  throw "base Expression should not be cloned";
}

void Expression::deletePtrVec(std::vector<Expression * > to_delete){
  for(Expression*& operand : to_delete ){
    delete operand; // should recurively delete all operands in our Expression Tree
    operand = 0; // set pointer to null
  }
  operands.clear();
}
