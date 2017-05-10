#include <cstdlib>
#include <cstdio>
#include <vector>

class testClass{
public:
  int value;
  testClass(int v){
    value = v;
  }
};

int function(testClass c){
  printf("called by value\n");
  return c.value;
}
int function(testClass & c){
  printf("called by reference\n");
  return c.value;
}

int main(){
  int input = 5;
  testClass t(7);
  int ret_val1 = function(input);
  int ret_val2 = function(t);
  printf("%d %d\n",ret_val1,ret_val2);
}
