#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <vector>
#include <string>
#include <map>
#include <boost/multiprecision/cpp_int.hpp>


class Expression{
protected:
    std::string tag; // A string denoting the type of expression
    std::size_t max_operands;
    std::size_t min_operands;
    bool communative;
    bool associative;
    bool undefined;
    boost::multiprecision::cpp_rational value;
    std::string var_name;
    std::vector<Expression*> operands;

  public:
    ///
    /// CONSTRUCTOR
    ///
    Expression(
      std::string tag_string,
      std::size_t max_operands_size_t,
      std::size_t min_operands_size_t,
      bool communative_bool,
      bool associative_bool,
      bool undefined_bool,
      boost::multiprecision::cpp_rational value_rational = boost::multiprecision::cpp_rational(),
      std::string var_name_string = std::string(),
      std::vector<Expression*> operands_vector = std::vector<Expression*>()
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
    virtual boost::multiprecision::cpp_rational getValue() const;

    /**
      @params: None
      @return: string indicating name of variable
      //NOTE: should only be used if tag = VARIABLE
      will raise and exception if the above condition is not met
    */
    virtual std::string getName() const;


    /**
      @params: None
      @return: returns a string representation of current expression
    */
    virtual std::string toString() const;

    //
    // Setters
    //

    virtual void swap(Expression & other);

    //
    // Operators
    //

  // Assignment / mutable operators
  virtual Expression& operator=(const Expression & other);

  // Relational Operators
  virtual bool operator==(const Expression& rhs) const;
  virtual bool operator!=(const Expression& rhs) const;
  virtual bool operator< (const Expression& rhs) const;
  virtual bool operator> (const Expression& rhs) const;
  virtual bool operator<=(const Expression& rhs) const;
  virtual bool operator>=(const Expression& rhs) const;

  // access operator, basically give us access to
  virtual Expression* operator[](int pos);


  //
  // CAS functions
  //

  virtual Expression * simplify();


  //
  // Helper Functions;
  //

  // TODO: might want to make this a private member
  void _delete_operands();

};

#endif
