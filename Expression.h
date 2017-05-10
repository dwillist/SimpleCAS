#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <vector>
#include <string>
#include <map>

#include "Rational.h"

/**
  NOTE: this is an Abstract class
*/
class Expression{
  private:
    std::string tag; // A string denoting the type of expression
    int max_operands;
    std::string tag;
    int min_operands;
    bool communative;
    bool associative;
    bool undefined;
    Rational value;
    std::string var_name;
    std::vector<*Expression> operands;

  public:
    ///
    /// CONSTRUCTOR
    ///
    Expression(
      int max_operands_int,
      int min_operands_int,
      bool communative_bool,
      bool associative_bool,
      Rational value_rational,
      std::string var_name_string,
      std::vector<*Expression> operands_vector,
    );

    Expression(const Expression & E); // copy constructor

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
    std::string getTag() const;

    /**
      @params: None
      @return: boolean telling if expression is a communative operation
    */
    bool isCommunative() const;

    /**
      @params: None
      @return: boolean telling if expression uses an associative operation
    */
    bool isAssociative() const;

    /**
      @params: None;
      @return: boolean value indicating if current expression is a VARIABLE
    */
    bool isVariable() const;

    /**
      @params: None;
      @return: boolean value indicating if current expression is a RATIONAL
    */
    bool isRational() const;

    /**
      @params: None
      @return boolean indicating if current expression is undefined
          ie 1/0
    */
    bool isUndefined() const;

    /**
      @params: None
      @return: integer indicating size of operands vector
    */
    int size() const;

    /**
      @params: None
      @return: Rational indicating value of expression
      //NOTE: should only be used if tag = RATIONAL
      will raise and exception if above condition is not met
    */
    virtual Rational getValue() const = 0;

    /**
      @params: None
      @return: string indicating name of variable
      //NOTE: should only be used if tag = VARIABLE
      will raise and exception if the above condition is not met
    */
    virtual string getName() const = 0;


    /**
      @params: None
      @return: returns a string representation of current expression
    */
    virtual std::string toString() const;

    //
    // Setters
    //

    virtual void swap(Expression & other) throw(){
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

  // Assignment / mutable operators
  virtual Expression& operator=(const Expression & other);

  // Relational Operators
  virtual bool operator==(const Expression& lhs, const Expression& rhs) const;
  virtual bool operator!=(const Expression& lhs, const Expresion& rhs) const;
  virtual bool operator< (const Expression& lhs, const Expression& rhs) const;
  virtual bool operator> (const Expression& lhs, const Expression& rhs) const;
  virtual bool operator<=(const Expression& lhs, const Expression& rhs) const;
  virtual bool operator>=(const Expression& lhs, const Expression& rhs) const;

  // access operator, basically give us access to
  virtual   Expression* operator[](int pos);


  //
  // CAS functions
  //

  Expression * simplify() = 0;


  //
  // Helper Functions;
  //

  // TODO: might want to make this a private member
  void _delete_operands();

  void _deep_copy_operands(const Expression & other);

};

#endif
