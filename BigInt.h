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
    @params: total_size is a positive int denoting new size of binary_rep
    @return: None
      - if total size is larger than current size extend our binary_rep according to
        its sign( 1's for negative 0's for positive)
      -if less then this just chops of most significant bits untill we reach total_size
  */
  void setSize(int total_size);

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

  BigInt();
  BigInt(std::vector<bool> & bin_rep);
  //TODO: implement below constructor for arbitrary based strings
  //BigInt(const std::string & s,base = 10);
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
  int getKthDigit(std::size_t k) const;

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
  std::string toString(bool big_endian = true) const;

  /**
    @params: None
    @return: size of binary representation of our number
  */
  long long size() const;

  /**
    @params: None
    @return: weather the current BigInt < 0
  */
  bool negative() const;

  //
  //Setters
  //

  /**
    params: int position of digit to be changed
      bool value (false -> 0, true -> 1) of new value of kth digit
    return: None
  */
  void setKthDigit(std::size_t k,bool new_value);


  /**
    params: None
    return: None
      -sets all bits of number to zero without resizing
  */
  void zero() const;

  /**
    params: None
    return: a long long integer
  */
  long long toLlong() const;

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
  BigInt operator%(const BigInt& lhs, const BigInt & rhs);
  BigInt operator-(const BigInt lhs); // Unary minus

  // binary operators that can be used on integers

  BigInt operator&(const BigInt &lhs, const BigInt &rhs); // Bitwise and
  BigInt operator~(const BigInt &lhs, const BigInt &rhs); // Bitwise complement
  BigInt operator^(const BigInt &lhs, const BigInt &rhs); // Bitwise exclusive or
  BigInt operator|(const BigInt &lhs, const BigInt &rhs); // Bitwise or
  BigInt operator<<(const BigInt &lhs, unsigned int shift); // Left shift
  BigInt operator>>(const BigInt &lhs, unsigned int shift); // Right shift


  void swap(BigInt & other);

  _raw_add(BigInt & other const);

  _raw_subtract(BigInt & other const);


};

//
// Non-class related functions
//

namespace BigIntFuntions{
  /**
    @params: two BigInts a dividend and divisor
    @return: a pair of Bigints of the form pair<quotent,rem>
      - Note: this follows the convention both the quotent and remainder having
        the same sign.
  */
  std::pair<BigInt,BigInt> divmod(const BigInt& dividend, const BigInt& divisor);

  //BigInt extended_gcd(BigInt lhs,BigInt rhs);

  //BigInt gcd(const BigInt & lhs,const BigInt & rhs);

  //BigInt nth_root(const BigInt & radicand, unsigned int index);

  //BigInt sqrt(const BigInt & to_root);
}


#endif
