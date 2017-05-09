#ifndef _RATIONAL_H_
#define _RATIONAL_H_

#include "BigInt.h";
#include <string>

class Rational{
private:
  BigInt numerator;
  BigInt denominator;

public:

  //
  //Ctors
  //
  Rational(long long num, long long denom);
  Rational(const BigInt& num,const BigInt& denom);
  Rational(const Rational & R) // copy constructor

  //
  //Dtors
  //
  ~Rational();

  // Operator Overloading;

  //
  // Operators
  //

  // Assignment / mutable operators
  Rational& operator=(const Rational & other);
  Rational& operator++();
  Rational& operator--();
  Rational& operator+=(const Rational &rhs);
  Rational& operator-=(const Rational &rhs);
  Rational& operator*=(const Rational &rhs);
  Rational& operator/=(const Rational &rhs);

  // Relational Operators
  bool operator==(const Rational& lhs, const Rational& rhs);
  bool operator!=(const Rational& lhs, const Rational& rhs);
  bool operator< (const Rational& lhs, const Rational& rhs);
  bool operator> (const Rational& lhs, const Rational& rhs);
  bool operator<=(const Rational& lhs, const Rational& rhs);
  bool operator>=(const Rational& lhs, const Rational& rhs);

  //Algebraic operators and functions
  Rational operator+(const Rational& lhs, const Rational & rhs);
  Rational operator-(const Rational& lhs, const Rational & rhs);
  Rational operator*(const Rational& lhs, const Rational & rhs);
  Rational operator/(const Rational& lhs, const Rational & rhs);

  bool isUndefined();

  bool isZero();

  bool isOne();

  std::string to_string() const;

};

#endif
