
#include<iostream>
#include<string>
using namespace std;
class Base{
public:
    ~Base(){
        cout<< "5";
    }
};
class Der : public Base{
public:
    ~Der(){
        cout<< "4";
    }
};
class GDer : public Der{
public:
    ~GDer(){
        cout<< "3";
    }
};

int main(){
    Base* A = new  GDer();
    Base* B = new Der();
    delete A;
    delete B;
}

