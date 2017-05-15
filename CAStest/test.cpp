#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>

void printV(std::vector<bool> & B){
  for(int i = 0; i < B.size(); ++i){
    if(B[i]){
      printf("1");
    }
    else{
      printf("0");
    }
  }
  printf("\n");
}

int main(){
  /*
  std::vector<bool> B = {0,1,1,0};
  printf("pre flip\n");
  printV(B);
  B.flip();
  printf("post flip\n");
  printV(B);
  */
  bool a = true;
  bool b = true;
  bool c = (a ^ b);
  printf("%s", c ? "true" : "false");
}
