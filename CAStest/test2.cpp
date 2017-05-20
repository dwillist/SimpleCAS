#include <vector>
#include <iostream>
#include <boost/assign/list_of.hpp>

using namespace std;

int sum_func(vector<int> v){
  int to_return = 0;
  for(int i = 0; i < v.size(); ++i){
    to_return +=v[i];
  }
  return to_return;
}


int main(){
}
