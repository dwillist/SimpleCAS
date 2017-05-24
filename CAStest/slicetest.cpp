#include <iostream>

using namespace std;

class A{
public:
  virtual void f() const{
    cout << "class A" << endl;
  }
};

class B : public A{
public:
  virtual void f() const{
    cout << "class B" << endl;
  }
};

void sliceFunction(const A & inst){
  cout << "calling f" << endl;
  inst.f();
}

int main(){
  A * a_inst = new A();
  A * b_inst = new B();
  sliceFunction(*b_inst);
}
