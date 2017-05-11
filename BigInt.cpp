#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

//
// Private Functions
//

void increaseSize(int bits_to_add){
  bool sign_bit = binary_rep[size()-1];
  int i = size();
  binary_rep.resize(size()+bits_to_add);
  for(;i < size(); ++i){
    binary_rep[i] = sign_bit;
  }
}

void decreaseSize(int bits_to_remove){
  int new_size = size() = bits_to_remove;
  if( new_size < 0){
    throw "BigInt rep resized to negative value, invalid size";
  }
  binary_rep.resize(new_size);
}

//
bool full(){
  bool sign_bit = binary_rep[size()-1];
  for(int i = 0 i < size()-1; ++i){
    if(binary_rep[i] == sign_bit){
      return false;
    }
  }
  return true;
}

bool halfEmpty(){
  bool sign_bit = binary_rep[size()-1];
  for(int i = size()-1; i >= (size()/2) -1; i--){
    if(binary_rep[i] != sign_bit){
      return false;
    }
  }
  return true;
}


void negate(){
  //need to consider 100 -> 011+1 -> 100
  // below if statement captures this edge case
  if(full()){
    increaseSize(1);
  }
  binary_rep.flip();
  *this++;
}

//
// Ctors
//

BigInt(long long l){
  std::bitset<64> = temp(l); // long long casted to unsigned long here.
  binary_rep.resize(STARTSIZE);
  for(int i = 0; i < STARTSIZE; ++i){
    binary_rep[i] = temp.test(i);
  }
}

BigInt(const BigInt & B){ // copy constructor
  if(*this != B){
    binary_rep = B.binary_rep;
  }
}

//
// Getters
//

bool getKthDigit(int k){
  return binary_rep[k];
}

std::string toString(bool big_endian){
  std::string to_return;
  for(auto i : binary_rep){
    if(i){
      to_return.push_back('1');
    }
    else{
      to_return.push_back('0');
    }
  }
  if(big_endian){
    std::reverse(to_return.begin(),to_return.end())
  }
  return to_return;
}


long long size(){
  return (long long) binary_rep.size();
}

bool negative(){
  return binary_rep[size()-1];
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
  bool carry = false;
  int max_size = max(lhs.size(),rhs.size());
  BigInt to_return = BigInt(0);
  to_return.increaseSize(max_size - STARTSIZE);
  int index = 0;
  for(;index < max_size; ++index){
    if(index < lhs.size() && index < rhs.size()){
      to_return.binary_rep[index] = (lhs.getKthDigit(index) != rhs.getKthDigit(index) || carry);
      carry = (lhs.getKthDigit(index) + rhs.getKthDigit(index) + carry > 1);
    }
  }
  // two cases of overflow
  // both positive
  if(lhs.positive() && rhs.positive() && to_return.negative()){
    to_return.binary_rep.push_back(0);
  }
  // both negative
  else if(lhs.negative() && rhs.negative() && to_return.positive()){
    to_return.binary_rep.push_back(1);
  }
  return to_return
}

BigInt operator-(const BigInt& lhs, const BigInt & rhs){
  BigInt to_negate = rhs;
  to_negate.negate();
  return lhs + to_negate;
}

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
  swap(binary_rep,other.binary_rep);
}
