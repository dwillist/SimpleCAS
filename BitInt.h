#ifndef _BIG_INT_H_
#define _BIG_INT_H_

#include <vector>

class BigInt{
private:
  // note that value[0] is th 1's place of our number
  std::vector<int> value;
  bool neg;
public:
  //
  // Ctors
  //
  BigInt(const string & s);
  BigInt(const int i);
  BigInt(const long l);
  BigInt(const BigInt & B); // copy constructor

  //
  //Dtor
  //
  virtual ~BigInt();

  //
  // Getters
  //

  /**
    @params: position of digit we want to recieve, 0 -> 1's place 1 -> 10's,...
    @return: digit in kth position
  */
  int getKthDigit(int k);

  /**
    @params: None
    @return: string representation of our big integer
  */
  string to_string();

  //
  // Operators
  //

  // Assignment / mutable operators
  BigInt& operator=(const BigInt & other);
  BigInt& operator++();
  BigInt& operator--();
  BigInt& operator+=(const BigInt &rhs);
  BigInt& operator-=(const BigInt &rhs);
  BigInt& operator*=(const BigInt &rhs);
  BigInt& operator/=(const BigInt &rhs);

  // Relational Operators
  bool operator==(const BigInt& lhs, const BigInt& rhs);
  bool operator!=(const BigInt& lhs, const BigInt& rhs);
  bool operator< (const BigInt& lhs, const BigInt& rhs);
  bool operator> (const BigInt& lhs, const BigInt& rhs);
  bool operator<=(const BigInt& lhs, const BigInt& rhs);
  bool operator>=(const BigInt& lhs, const BigInt& rhs);

  //Algebraic operators and functions
  BigInt operator+(const BigInt& lhs, const BigInt & rhs);
  BigInt operator-(const BigInt& lhs, const BigInt & rhs);
  BigInt operator*(const BigInt& lhs, const BigInt & rhs);
  BigInt operator/(const BigInt& lhs, const BigInt & rhs);

  BigInt rem(const BigInt & divisor);
  BigInt rem(int divisor);
  BigInt rem(long long divisor);

  BigInt gcd(const BigInt & other);
  BigInt gcd(int other);
  BigInt gcd(long long other);

  BigInt nth_root(const BigInt & radicand);
  BigInt nth_root(int radicand);
  BigInt nth_root(long long radicand);

  BigInt sqrt();


};


#endif
