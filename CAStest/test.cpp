#include "testnamespace.h"
#include <cstdlib>
#include <cstdio>
#include <vector>

int testfunc(std::vector<int> d = std::vector<int>()){
  return (int)d.size();
}

int main(){
  printf("printed from namespace %d\n",testnamespace::f(5));
  std::vector<int> v = {4,5,6,1};
  std::vector<int> w = {4,6,5,1};
  if(v < w){
    printf("v less than w\n");
  }
  else{
    printf("w less than or equal to v\n");
  }

  printf("size of default sized vector is %d\n",testfunc());
}
