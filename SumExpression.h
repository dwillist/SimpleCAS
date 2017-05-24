#ifndef _SUM_EXPRESSION_H_
#define _SUM_EXPRESSION_H_

#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>


#include "Expression.h"

// to reduce verbosity
namespace BM = boost::multiprecision;

class SumExpression : public Expression{
  public:

    //
    // CONSTRUCTORS
    //

    SumExpression(std::vector<Expression * > sum_operands);
    SumExpression(const Expression & E);
    SumExpression(Expression * E1, Expression * E2); // binary sum constructor
    SumExpression(const Expression & E,std::size_t begin,std::size_t end);


    // See Base class comments
    //virtual boost::multiprecision::cpp_rational getValue() const;

    // See Base class comments
    //virtual std::string getName() const;

    //
    // CAS functions
    //

    virtual Expression * simplify();

    //
    // DeepCopy Functions
    //

    virtual Expression * clone() const;

    virtual Expression * clone(std::size_t begin, std::size_t end) const;

};

#endif
