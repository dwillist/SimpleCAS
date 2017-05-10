#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

//
// Private Functions
//

void BigInt::increaseSize(){
  std::binset<size() * ADJUSTFACTOR> new_binary_rep(binary_rep);
  // need to copy leading 1's for 1's complement
  if binary_rep.test(size()){
    new_binary_rep.flip(size());
    new_binary_rep.flip(new_binary_rep.size()); // set 1's complement bit
  }
  binary_rep = new_binary_rep;
}

bool BigInt::full(){
  for(int i = 0; i < size()-1){
    if(!binary_rep.test(i)){
      return false;
    }
  }
  return true;
}

//
// Ctors
//

BigInt(long long l){
  binary_rep = bitset<STARTSIZE>(l);
}
BigInt(const BigInt & B){ // copy constructor
  if(*this != B){
    binary_rep = B.binary_rep;
  }
}

//
// Getters
//

int getKthDigit(int k){
  return value[k];
}

std::string toString(){
  return binary_rep.to_string();
}

  //
  // Operators
  //

// Assignment uses copy swap idiom
BigInt& operator=(const BigInt & other) throw(){
  other.swap(*this);
  return *this;
}

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
BigInt operator+(const BigInt& lhs, const BigInt & rhs){
    
}
BigInt operator-(const BigInt& lhs, const BigInt & rhs);
BigInt operator*(const BigInt& lhs, const BigInt & rhs);
BigInt operator/(const BigInt& lhs, const BigInt & rhs);

BigInt rem(const BigInt & divisor);
BigInt rem(const BigInt divisor);
BigInt rem(int divisor);
BigInt rem(long long divisor);

BigInt gcd(const BigInt & other);
BigInt gcd(const BigInt other);
BigInt gcd(int other);
BigInt gcd(long long other);

BigInt nth_root(const BigInt & radicand);
BigInt nth_root(const BigInt radicand);
BigInt nth_root(int radicand);
BigInt nth_root(long long radicand);

BigInt sqrt();

void swap(BigInt & other){
  using std::swap;
  swap(values,other.values);
  swap(neg,other.neg);
}
