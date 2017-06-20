
#include <boost/multiprecision/cpp_int.hpp>

#include "Expression.h"
#include "DifferenceExpression.h"
#include "SumExpression.h"
#include "ProductExpression.h"
#include "SimplifyFunctions.h"
#include "FunctionTags.h"

//
// CONSTRUCTORS
//

namespace BM = boost::multiprecision;
namespace SF = SimplifyFunctions;
namespace FT = FunctionTags;


DifferenceExpression::DifferenceExpression(std::vector<Expression * > difference_operands):
  Expression(FunctionTags::DIFFERENCE,
             -1, // this is max value of size_t due to two's complement
             0,
             true,
             true,
             boost::multiprecision::cpp_rational(0),
             std::string(),
             difference_operands)
  {}

DifferenceExpression::DifferenceExpression(const DifferenceExpression & R){ // Copy constuctor
    
}
DifferenceExpression::DifferenceExpression(const Expression & E); // conversion of arbitrary expression to sum


ExponentExpression::ExponentExpression(Expression && other) :
Expression(other)
{
  tag = FT::EXPONENT;
}

//
// Dtor
//
DifferenceExpression::~DifferenceExpression();

//
// Virtual functions
//

// See Base class comments
BM::cpp_rational getValue();

// See Base class comments
std::string get_name();

//
// CAS functions
//

Expression * simplify();
