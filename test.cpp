#include <string>
#include <vector>
#include <algorithm>

#include "BigInt.h"

int main(){
  BigInt a = BigInt(5);
  BigInt b = BigInt(10);
  long long to_print = (a + b).toLong();
  printf("value : %lld\n",to_print);
}
