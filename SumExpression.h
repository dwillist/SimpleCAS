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

    SumExpression(std::vector<std::unique_ptr<Expression>  > sum_operands);
    SumExpression(const Expression & E);
    SumExpression(std::unique_ptr<Expression>  E1, std::unique_ptr<Expression>  E2); // binary sum constructor
    SumExpression(const Expression & E,std::size_t begin,std::size_t end);
    SumExpression(Expression && E);


    // See Base class comments
    //virtual boost::multiprecision::cpp_rational getValue() const;

    // See Base class comments
    //virtual std::string getName() const;

    //
    // CAS functions
    //

    virtual std::unique_ptr<Expression>  simplify();

    virtual std::unique_ptr<Expression>  derivative(std::string with_respect_to);


    //
    // DeepCopy Functions
    //

    virtual std::unique_ptr<Expression>  clone() const;

    virtual std::unique_ptr<Expression>  clone(std::size_t begin, std::size_t end) const;

};

#endif
