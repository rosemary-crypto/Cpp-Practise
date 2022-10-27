#include<iostream>
#include<memory>
#include<vector>

using namespace std;

class A
{
public:
    A(int val)
    {
        _val = val;
    }

    int GetVal() { return _val; }
    void ChangeVal(int c){_val = c;}
    void Trying(){
      unique_ptr<int> checking = make_unique<int>(3);
      std::cout<<"CHECK 1 : "<<*checking <<endl;
      *checking = 7;
      std::cout<<"CHECK 2 : "<<*checking <<endl;  
      Changing(checking);
      std::cout<<"CHECK 3 : "<<*checking <<endl;  
    }
    void Changing(unique_ptr<int>& here){
      *here = 100;
    }
private:
    int _val;
};

void MyFunc(unique_ptr<A> & arg)
{
    cout << arg->GetVal() << endl;
}
void MyFunc2(unique_ptr<A> arg)
{
    cout << arg->GetVal() << endl;
}
void MyFuncChange(unique_ptr<A> & arg, int c)
{
    arg->ChangeVal(c);
}

int main(int argc, char* argv[])
{
    unique_ptr<A> ptr = unique_ptr<A>(new A(1234));
    MyFunc(ptr);
    MyFuncChange(ptr,100);
    MyFunc(ptr);
    ptr->Trying();
    unique_ptr<A> ptr2 = unique_ptr<A>(new A(1234));
    MyFunc2(move(ptr2));
}