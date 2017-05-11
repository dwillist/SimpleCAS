#ifndef _BIG_INT_H_
#define _BIG_INT_H_

#include <bitset>
#include <string>

class BigInt{
private:
  const int STARTSIZE = 64;

  // a little-endian 1's complement representation of our big integer.
  // we use a vector of bools and let the compiler
  std::vector<bool> binary_rep;
  // TODO: implement below initialization method
  //void _initialize(const std::string & s,base = 10);

  /**
    @params: bits_to_add is number of bits to add starting after the most
             significant bit
    @return: None
      - this increases the size of our representation to final_size by appending
      0's (for positive) or 1's (for negative) on to the end of our binary_rep
  */
  void increaseSize(int bits_to_add);

  /**
    @params: bits_to_remove is number of bits to remove starting from most
             significant bit
    @return: None
      - this decreases the size of our representation by removing excess 0's (for positive)
      or 1's (for negative) on to the end of our binary_rep
  */
  void decreaseSize(int bits_to_remove);

  /**
    @params: integer indicating final number of bits in our final binary representation
    @return: boolean value indicating weather or not current binary representation is
             the largest (positive or negative) possible with current number of bits
  */
  bool full();

  /**
    @params: None
    @return: boolean value indicating if half of our current binary representation
             is just preceeding 0's(for positive) or 1's(for negative)
  */
  bool halfEmpty();

  /**
    @params: None
    @return: None
        - flips all bits and adds 1 to negate current binary representation.
  */
  void negate();


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
    @params: boolean indicating if we want our final output to be big endian
    @return: binary string representing the value of this BigInt in little-endian or
             big_endian form
  */
  std::string toString(bool big_endian = true);

  /**
    @params: None
    @return: size of binary representation of our number
  */
  long long size();

  /**
    @params: None
    @return: weather the current BigInt < 0
  */
  bool negative();

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
