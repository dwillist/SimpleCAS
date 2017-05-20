#ifndef _FUNCTION_TAGS_
#define _FUNCTION_TAGS_

#include <map>
#include <string>

namespace FunctionTags{
  extern std::string UNDEFINED;
  extern std::string SUM;
  extern std::string PRODUCT;
  extern std::string EXPONENT;
  extern std::string DIFFERENCE;
  extern std::string QUOTENT;
  extern std::string VARIABLE;
  extern std::string RATIONAL;
  extern std::map<std::string,std::string> tag_to_print;
  enum PRECIDENCE {UNDEFINED_PREC,RATIONAL_PREC,VARIABLE_PREC,SUM_PREC,PRODUCT_PREC,EXPONENT_PREC};
  extern std::map<std::string,int> precidence_map;
};



#endif
