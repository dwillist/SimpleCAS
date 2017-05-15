#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <bitset>

#include "BigInt.h"

//
// Private Functions
//

void BigInt::increaseSize(std::size_t bits_to_add){
  bool sign_bit = binary_rep[size()-1];
  int i = size();
  binary_rep.resize(size()+bits_to_add);
  for(;i < size(); ++i){
    binary_rep[i] = sign_bit;
  }
}


void BigInt::setSize(std::size_t total_size){
  if(total_size > size()){
    increaseSize(total_size-size());
  }
  else if(total_size < size()){
    binary_rep.resize(total_size);
  }
}

void BigInt::decreaseSize(std::size_t bits_to_remove){
  int new_size = size() = bits_to_remove;
  if( new_size < 0){
    throw "BigInt rep resized to negative value, invalid size";
  }
  binary_rep.resize(new_size);
}

bool BigInt::full(){
  bool sign_bit = binary_rep[size()-1];
  for(int i = 0 i < size()-1; ++i){
    if(binary_rep[i] == sign_bit){
      return false;
    }
  }
  return true;
}

bool BigInt::halfEmpty(){
  bool sign_bit = binary_rep[size()-1];
  for(int i = size()-1; i >= (size()/2) -1; i--){
    if(binary_rep[i] != sign_bit){
      return false;
    }
  }
  return true;
}


void BigInt::negate(){
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

BigInt::BigInt(long long l){
  std::bitset<64> = temp(l); // long long casted to unsigned long here.
  binary_rep.resize(STARTSIZE);
  for(int i = 0; i < STARTSIZE; ++i){
    binary_rep[i] = temp.test(i);
  }
}

BigInt::BigInt(const BigInt & B){ // copy constructor
  if(*this != B){
    binary_rep = B.binary_rep;
  }
}

//
// Getters
//

bool BigInt::getKthDigit(std::size_t k){
  return binary_rep[k];
}

std::string BigInt::toString(bool big_endian){
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


long long BigInt::size(){
  return (long long) binary_rep.size();
}

bool BigInt::negative(){
  return binary_rep[size()-1];
}

//
//Setters
//

void BigInt::setKthDigit(std::size_t k,bool new_value){
  binary_rep[k] = new_value;
}


void BigInt::zero(){
  for(auto && bit : binary_rep){
    bin = false;
  }
}


long long BigInt::toLong(){
  std::bitset<64> to_long_bitset = std::bitset<64>(toString());
  return to_long_bitset.to_ullong();
}

//
// Operators
//

// Assignment uses copy swap idiom
BigInt& BigInt::operator=(const BigInt & other) throw(){
  other.swap(*this);
  return *this;
}

// this really should be sped up
BigInt& BigInt::operator++(){
  *this += BigInt(1);
  return *this;
}

BigInt& BigInt::operator--(){
  *this -= BigInt(1);
}

BigInt& BigInt::operator+=(const BigInt &rhs){
  binary_rep = (*this + rhs).binary_rep;
  return *this;
}
BigInt& BigInt::operator-=(const BigInt &rhs){
  binary_rep = (*this - rhs).binary_rep;
  return *this;
}

BigInt& BigInt::operator*=(const BigInt &rhs){
  binary_rep = (*this * rhs).binary_rep;
  return *this;
}
BigInt& BigInt::operator/=(const BigInt &rhs){
  binary_rep = (*this / rhs).binary_rep;
  return *this;
}

// Relational Operators
bool BigInt::operator==(const BigInt& lhs, const BigInt& rhs){
    int lhs_max_index = lhs.size()-1;
    int rhs_max_index = rhs.size()-1;
    while(lhs_max_index == lhs.getKthDigit(lhs.size()-1)){
      lhs_max_index--;
    }
    while(rhs_max_index == rhs.getKthDigit(rhs.size()-1)){
      rhs_max_index--;
    }
}

bool BigInt::operator!=(const BigInt& lhs, const BigInt& rhs);
bool BigInt::operator< (const BigInt& lhs, const BigInt& rhs);
bool BigInt::operator> (const BigInt& lhs, const BigInt& rhs);
bool BigInt::operator<=(const BigInt& lhs, const BigInt& rhs);
bool BigInt::operator>=(const BigInt& lhs, const BigInt& rhs);

//Algebraic operators and functions
BigInt BigInt::operator+(const BigInt& lhs, const BigInt & rhs){
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

BigInt BigInt::operator-(const BigInt& lhs, const BigInt & rhs){
  BigInt to_negate = rhs;
  to_negate.negate();
  return lhs + to_negate;
}

BigInt BigInt::operator*(const BigInt& lhs, const BigInt & rhs){
  BigInt new_lhs = lhs;
  BigInt new_rhs = rhs;
  BigInt to_return = BigInt(0);
  bool negativeResult = false;
  if(new_lhs.negative()){
    new_lhs.negate();
    negativeResult = !negativeResult;
  }
  if(new_rhs.negative()){
    new_rhs.negate();
    negativeResult = !negativeResult;
  }
  for(int i = 0; i < new_rhs.size(); ++i){
    if(new_rhs.getKthDigit(i)){
      to_return += (new_lhs >> i);
    }
  }
  if(negativeResult){
    to_return.negate();
  }
  return to_return;
}


BigInt BigInt::operator/(const BigInt& lhs, const BigInt & rhs){
  return BigIntFuntions::divmod(lhs,rhs).first;
}

BigInt BigInt::operator%(const BigInt& lhs, const BigInt & rhs){
  return BigIntFuntions::divmod(lhs,rhs).second;
}


BigInt BigInt::operator-(const BigInt lhs){
  lhs.negate();
  return lhs;
}

// binary operators that can be used on integers

BigInt BigInt::operator&(const Type &lhs, const Type &rhs){ // Bitwise and
  int max_size = max(lhs.size(),rhs.size())
  BigInt to_return = BigInt(0);
  to_return.setSize(max_size);
  for(int i = 0; i < min(lhs.size(),rhs.size()); ++i){
    if(lhs.getKthDigit(i) && rhs.getKthDigit(i)){
      to_return.setKthDigit(i,true);
    }
  }
  return to_return;
}
// this is NOT the same as negate
BigInt BigInt::operator~(const Type &lhs){ // Bitwise complement
  BigInt to_return = BigInt(0);
  to_return.setSize(lhs.size());
  for( auto && bit : to_return.binary_rep){
    bit = !bit;
  }
  return to_return;
}

BigInt BigInt::operator^(const Type &lhs, const Type &rhs){ // Bitwise exclusive or
  if(lhs.size() < rhs.size()){
    return rhs ^ lhs;
  }
  //lhs.size() >= rhs.size();
  BigInt to_return = BigInt(0);
  to_return.setSize(lhs.size());
  for(int i = 0; i < lhs.size(); i++){
    to_return.binary_rep[i] == lhs.getKthDigit(i) ^ rhs.getKthDigit(i);
    // alternatively could use !=
  }
  return to_return;
}
BigInt BigInt::operator|(const Type &lhs, const Type &rhs){ // Bitwise or
  if(lhs.size() < rhs.size()){
    return rhs | lhs;
  }
  //lhs.size() >= rhs.size();
  BigInt to_return = BigInt(0);
  to_return.setSize(lhs.size());
  for(int i = 0; i < lhs.size(); i++){
    to_return.binary_rep[i] == lhs.getKthDigit(i) | rhs.getKthDigit(i);
    // alternatively could use !=
  }
  return to_return;
}

BigInt BigInt::operator<<(const Type &lhs, unsigned int shift){ // Left shift
  if(shift > lhs.size()){
    shift = lhs.size();
  }
  bool to_add = binary_rep[lhs.size()-1];
  int original_size = lhs.size();
  std::rotate(lhs.begin(),lhs.begin() + shift,lhs.end());
  lhs.setSize(max(lhs.size()-shift,0));
  std::vector<bool> to_insert;
  to_insert.resize(original_size);
  std::fill(to_insert.begin(),to_insert.end(),to_add);
  binary_rep.insert(binary_rep.end(),to_insert.begin(),to_insert.end());

}
BigInt BigInt::operator>>(const Type &lhs, unsigned int shift){ // Right shift
  if(shift > lhs.size()){
    shift = lhs.size());
  }
  BigInt to_return;
  to_return.setSize(lhs.size());
  for(int i = shift-1; i < lhs.size()){
    to_return.setKthDigit(i,lhs.getKthDigit(i-shift));
  }
  return to_return;
}

void BigInt::swap(BigInt & other){
  using std::swap;
  swap(binary_rep,other.binary_rep);
}


//
// BigIntFuntions namespace
//

std::pair<BigInt,BigInt> BigIntFuntions::divmod(
                                        const BigInt& dividend,
                                        const BigInt & divisor){
  bool negative_solution == dividend.negative() ^ divisor.negative()
  if(divisor == BigInt(0)){
    // divide by zero error
    throw std::domain_error("Division by zero");
  }
  BigInt quotent = BigInt(dividend);
  quotent.zero() // makes a zero array as large as quotent
  BigInt rem = BigInt(divisor);
  rem.zero();
  for(int i = 0; i < dividend.size(); ++i){
    rem >> 1;
    rem.setKthDigit(i,dividend.getKthDigit(i));
    if(rem >= divisor){
      rem = rem - divisor;
      quotent.setKthDigit(i,1);
    }
  }
  if(negative_solution){
    quotent.negate();
    rem.negate();
  }
  return(std::make_pair(quotent,rem));
}
