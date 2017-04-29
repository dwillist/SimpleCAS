#ifndef _FACTORIES_H_
#define _FACTORIES_H_

#include <vector>

namespace Factories{
    Expression* makeRational(long long num, long long denom = 1);
    Expression* makeVariable(string var_name);
    Expression* makeSum(std::vector<Expression> E);
    Expression* makeProduct(std::vector<Exprssion> E);
    Expression* makeExponent(setd::vector<Expression> E);
}


#endif
