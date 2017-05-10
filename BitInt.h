#ifndef _BIG_INT_H_
#define _BIG_INT_H_

#include <bitset>
#include <string>

class BigInt{
private:
  const int STARTSIZE = 64;
  const int ADJUSTFACTOR = 2;
  // a little-endian 1's complement representation of our big integer.
  std::<bitset> binary_rep;
  // TODO: implement below initialization method
  //void _initialize(const std::string & s,base = 10);
  void increaseSize();
  bool full();
public:
  //
  // Ctors
  //

  //TODO: implement below constructor for arbitrary based strings
  //BigInt(const std::string & s,base = 10);
  BigInt(int i);
  BigInt(long long l);
  BigInt(const BigInt & B); // copy constructor

  //
  //Dtor
  //
  // default Dtor works fine for us;

  //
  // Getters
  //

  /**
    @params: position of digit we want to recieve, 0 -> 1's place 1 -> 10's,...
    @return: digit in kth position
  */
  int getKthDigit(int k);

  /**
    TODO: implement below method
    @params: None
    @return: string representation of our big integer
  */
  //std::string toBaseNString(int n = 10);

  /**
    @params: None
    @return: size of binary representation of our number
  */
  long long size();

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

  void swap(BigInt & other);

  _raw_add(BigInt & other const);

  _raw_subtract(BigInt & other const);


};


#endif
