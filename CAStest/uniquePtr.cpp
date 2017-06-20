#include <iostream>
#include <vector>

class A{
private:
  int i;
public:
  A(int i_inst):
    i(i_inst){}
  A(A const & other) : i(other.i){}
  A(A && other) : i(std::move(other.i)){}
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

}

int main(){
  std::unique_ptr<A> bptr(new B(5));
  
  function(bptr);
}
