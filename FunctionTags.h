#ifndef _FUNCTION_TAGS_
#define _FUNCTION_TAGS_

#include <map>
#include <string>
#include "Expression.h"

namespace FunctionTags{
  std::string SUM = "SUM";
  std::string PRODUCT = "PRODUCT";
  std::string EXPONENT = "EXPONENT";
  std::string DIFFERENCE = "DIFFERENCE"
  std::string QUOTENT = "QUOTENT"
  std::string VARIABLE = "VARIABLE";
  std::string RATIONAL = "RATIONAL";
  std::map<std::string,std::string> tag_to_print = {
                                  {SUM, "+"}
                                  {PRODUCT, "*"},
                                  {EXPONENT,"^"},
                                  {VARIABLE,"V"},
                                  {RATIONAL,"#"}
                                };

  enum PRECIDENCE {RATIONAL,VARIABLE,SUM,PRODUCT,EXPONENT,}
}



#endif
