#ifndef _BIG_INT_H_
#define _BIG_INT_H_

#include <vector>

class BigInt{
private:
  std::vector<int> value;
public:
  //
  // Ctors
  //
  BigInt(const string & s);
  BigInt(const int i);
  BigInt(const long l);
  BigInt(const BigInt & B);

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
    @return:
  */
  string to_string();

  //
  //
  //
};


#endif
