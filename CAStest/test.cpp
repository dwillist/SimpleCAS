#include "testnamespace.h"
#include <cstdlib>
#include <cstdio>

int main(){
  int i = 5;
  printf("printed from namespace %d\n",testnamespace::f(i));
}
