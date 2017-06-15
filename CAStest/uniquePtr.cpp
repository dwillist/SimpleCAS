#include <iostream>
#include <vector>

class A{
private:
  int i;
public:
  A(int i_inst):
    i(i_inst){}
  virtual int value(){
    return i;
  }
};

class B : public A{
public:
  B(int i_inst) : A(i_inst){}
  virtual int value(){
    return 1000;
  }
};

void function(std::unique_ptr<A> const & ptr){
  std::cout << ptr->value() << std::endl;
}

int main(){
  std::unique_ptr<A> bptr(new B(5));
  function(bptr);
}
