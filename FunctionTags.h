#ifndef _FUNCTION_TAGS_
#define _FUNCTION_TAGS_

#include <map>
#include <string>
#include "Expression.h"

namespace FunctionTags{
  std::string SUM = "SUM";
  std::string PRODUCT = "PRODUCT";
  std::string EXPONENT = "EXPONENT";
  std::string VARIABLE = "VARIABLE";
  std::string RATIONAL = "RATIONAL";

  // tag_map below just maps the above strings to their respective evaluation function
  std::map<string,Expression (*operator)(std::vector<*Expression>)> tag_map;
}

//TODO: need to define tag_map




#endif
