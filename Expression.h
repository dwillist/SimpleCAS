#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <vector>
#include <string>
#include <map>
#include "Rational.h"

class Expression{
  private:
    std::string tag; // A string denoting the type of expression
    int max_operands;
    int min_operands;
    Expression (*operator)(std::vector<*Expression>); // function pointer
    bool communative;
    bool associative;
    std::vector<std::string> distributes_over; // list of tags
  public:
    //
    // Variables
    //
    std::vector<*Expression> operands;

    Rational value;

    std::string var_name;

    ///
    /// CONSTRUCTOR
    ///
    Expression(
      std::string tag_string
      max_operands_int,
      min_operands_int,
      Expression (*operator_ptr)(std::vector<*Expression>),
      bool communative_bool,
      bool associative_bool,
      std::vector<std::string> distributes_over_vector,
      std::vector<*Expression> operands_vector,
    );

    //
    // Destructor
    //

    virtual ~Expression();

    //
    // Getters
    //

    /**
      @params: None
      @return: returns tag representing the operation this expression uses
               such tags are defined in FunctionTags.h
    */
    std::string getTag();

    /**
      @params: None
      @return: boolean telling if expression is a communative operation
    */
    bool isCommunative();

    /**
      @params: None
      @return: boolean telling if expression uses an associative operation
    */
    bool isAssociative();

    /**
      @params: None;
      @return: boolean value indicating if current expression is a VARIABLE
    */
    bool isVariable();

    /**
      @params: None;
      @return: boolean value indicating if current expression is a RATIONAL
    */
    bool isRational();
    /**
      @params: None
      @return: return vector of tags the current operation distrubutes over
    */
    vector<string> getDistributeOver();

    /**
      @params: None
      @return: integer indicating size of operands vector
    */
    int size();

    /**
      @params: None
      @return: Rational indicating value of expression
      //NOTE: should only be used if tag = RATIONAL
      will raise and exception if above condition is not met
    */
    Rational getValue();

    /**
      @params: None
      @return: string indicating name of variable
      //NOTE: should only be used if tag = VARIABLE
      will raise and exception if the above condition is not met
    */
    string get_name();

    //
    // Setters
    //

    //
    // Operators
    //

  // Assignment / mutable operators
  Expression& operator=(const Expression & other);

  // Relational Operators
  bool operator==(const Expression& lhs, const Expression& rhs);
  bool operator!=(const Expression& lhs, const Expresion& rhs);
  bool operator< (const Expression& lhs, const Expression& rhs);
  bool operator> (const Expression& lhs, const Expression& rhs);
  bool operator<=(const Expression& lhs, const Expression& rhs);
  bool operator>=(const Expression& lhs, const Expression& rhs);

  Expression* operator[](int pos);

};

#endif
