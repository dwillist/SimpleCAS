#ifndef _UNDEFINED_EXPRESSION_H
#define _UNDEFINED_EXPRESSION_H

#include <boost/multiprecision/cpp_int.hpp>
#include <string>
#include <vector>

#include "Expression.h"

//purpose of this class is basically to wrap another Expression just so it is clear
//that it is undefined

class UndefinedExpression : public Expression{
  public:

    //
    // CONSTRUCTORS
    //

    UndefinedExpression(std::vector<std::unique_ptr<Expression>  > undefined_operands);
    UndefinedExpression(std::unique_ptr<Expression>  E); // wrapping constructor
    // have to watch out for this copy constructor it probably does not do what you want
    // as it basically erases the operation and replaces it with undefined
    UndefinedExpression(const Expression & E);



    //
    // CAS functions
    //

    //virtual std::string toString() const;

    virtual boost::multiprecision::cpp_rational getValue() const;

    virtual std::unique_ptr<Expression>  simplify();
  
    virtual std::unique_ptr<Expression>  derivative(std::string with_respect_to);


    //
    // DeepCopy Functions
    //

    virtual std::unique_ptr<Expression>  clone() const;

    virtual std::unique_ptr<Expression>  clone(std::size_t begin, std::size_t end) const;


};

//
// helper functions
//

std::vector<std::unique_ptr<Expression>  > wrapWithVector(std::unique_ptr<Expression>  E);


#endif
