

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
