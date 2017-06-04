#include <string>
#include <map>

#include "FunctionTags.h"

std::string FunctionTags::UNDEFINED = "UNDEFINED";
std::string FunctionTags::SUM = "SUM";
std::string FunctionTags::PRODUCT = "PRODUCT";
std::string FunctionTags::EXPONENT = "EXPONENT";
std::string FunctionTags::DIFFERENCE = "DIFFERENCE";
std::string FunctionTags::QUOTENT = "QUOTENT";
std::string FunctionTags::VARIABLE = "VARIABLE";
std::string FunctionTags::RATIONAL = "RATIONAL";
std::string FunctionTags::LOGORITHM = "LOGORITHM";

std::map<std::string,std::string> FunctionTags::tag_to_print = std::map<std::string,std::string> {
                                    {FunctionTags::UNDEFINED, "undefined"},
                                    {FunctionTags::SUM, "+"},
                                    {FunctionTags::PRODUCT, "*"},
                                    {FunctionTags::EXPONENT,"^"},
                                    {FunctionTags::VARIABLE,"V"},
                                    {FunctionTags::RATIONAL,"#"},
                                    {FunctionTags::LOGORITHM, "LOG"}
                                  };

std::map<std::string,int> FunctionTags::precidence_map  = std::map<std::string,int> {
                                  {FunctionTags::UNDEFINED, FunctionTags::UNDEFINED_PREC},
                                  {FunctionTags::SUM, FunctionTags::SUM_PREC},
                                  {FunctionTags::PRODUCT, FunctionTags::PRODUCT_PREC},
                                  {FunctionTags::EXPONENT, FunctionTags::EXPONENT_PREC},
                                  {FunctionTags::VARIABLE, FunctionTags::VARIABLE_PREC},
                                  {FunctionTags::RATIONAL, FunctionTags::RATIONAL_PREC},
                                  {FunctionTags::LOGORITHM, FunctionTags::LOGORITHM_PREC}
                                };
