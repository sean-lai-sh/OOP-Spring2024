#include<iostream>
#include<vector>
#include<string>
using namespace std;

void Base10to3(int n){
    if(n < 0){
        throw out_of_range("test");
    }
    if(n > 3){
        Base10to3(n/3);
    }
    cout << n%3;
}

int main(){
    // Test cases for Base10to3
    Base10to3(10);
    cout << endl;
    Base10to3(3);
    cout << endl;
    Base10to3(15);
    cout << endl;
    Base10to3(0);
    cout << endl;
    try{
        Base10to3(-1);
    }catch(exception& ex){
        cout << "function works";
    }

}
