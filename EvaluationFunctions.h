#ifndef _EVALUATION_FUNCTIONS_
#define _EVALUATION_FUNCTIONS_

#include "Expression.h"
#include "Factories.h"
#include <vector>

// For evaluation of all base functions we assume the following
// our expression vector E consists only of Rationals
namespace BaseFunctions{
  Expression sum(const std::vector<*Expression> & E){
    long long denom = 1;
    long long numer = 0;
    for(auto current_op:E){
      long long d = denom*current_op.getRator()

    }
  }
}


#endif
