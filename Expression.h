#ifndef _EXPRESSION_H_
#define _EXPRESSION_H_

#include <vector>
#include <string>

class Expression{
  private:
    std::string tag; // A string denoting the type of expression
    int max_operands;
    int min_operands;
    Expression (*operator)(std::vector<*Expression>); // function pointer
    bool communative;
    bool associative;
    std::vector<std::string> distributes_over; // list of tags
  protected:
    std::vector<*Expression> operands;
  public:
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
      @params: position of operand in operands vector to return
      @return: operand at given position
    */
    Expression getRator(int pos);

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
    bool isAssociative()

    /**
      @params: None
      @return: return vector of tags the current operation distrubutes over
    */
    vector<string> getDistributeOver();

    //
    // Setters
    //

    /**
      @params: E is an expresion we are going to add to operands
      @return: boolean value indicating if operation was successful
    */
    bool virtual addOperand(Expression * E);

    /**
      @params: position of Expression in operands vector
      @return: boolean value indicating if operation was sucessful
    */
    bool virtual deleteOperand(int pos);


    //
    // Misc
    //
};


///
/// CONSTRUCTOR
///
Expression::Expression(
  std::string tag_string
  max_operands_int,
  min_operands_int,
  Expression (*operator_ptr)(std::vector<*Expression>),
  bool communative_bool,
  bool associative_bool,
  std::vector<std::string> distributes_over_vector,
  std::vector<*Expression> operands_vector,
) : tag(tag_string),
    operands(operands_vector);
    max_operands(max_operand_int),
    min_operands(min_operands_int),
    operator(operator_ptr),
    communative(communative_bool),
    associative(associative_bool),
    distributes_over(distributes_over_vector)
  {
    if(operands.size() > max_operands){
      throw "too many operands";
    }
    else if(operands.size() < min_operands){
      throw "too few operands";
    }
  }


virtual Expression::~Expression(){
  for(auto &operand : operands){
    delete operand;
  }
}


const Expression * Expression::getRator(int pos){
  return operands[pos]; // might not work so watch out here...
}

std::string Expression::getTag(){
  return tag;
}

bool isCommunative(){
  return communative;
}

bool isAssociative(){
  return associative;
}

vector<string> getDistributeOver(){
  return distributes_over;
}


#endif
