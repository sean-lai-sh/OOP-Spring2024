/*
  Sean Lai Sheng Hong
  03/09/2024
  bigUnsigned_begin.cpp
  Purpose: Operator overloading and copy control
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Put your class and all function definitions here.
// BigUnsigned class that represents a large unsigned integer using 
// a vector of digits
class BigUnsigned{
     // functions that are friends of BigUnsigned
     friend ostream& operator<<(ostream& lhs, const BigUnsigned& rhs);
     friend bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs);
     friend bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs);
     public:
          // Integer Constructor 
          BigUnsigned(int init_val = 0) : numArr(0){
               // have to add digits in body instead of initializer list
               int temp = init_val;
               addingDigits(temp);
               normalize(false);
          }

          // function to add digits to the array in correct order
          void addingDigits(int i){
               while( i > 0){
                    numArr.push_back(i%10);
                    i /= 10;
               }
          }
          // String Constructor for BigUnsigned
          BigUnsigned(const string& digits) : numArr(0){
               
               int ptr = 0;
               // iterate until you find first non-zero digit/ nonchar
               while(ptr < digits.length() && 
                    (digits[ptr] <= '0' || digits[ptr] > '9')){
                    ++ptr;
               }
               // loop and add each digit to the array
               while(ptr < digits.length() && 
                    (digits[ptr] >= '0' && digits[ptr] <= '9')){
                    // Utilizing char arithmetic to convert to actual int value
                    numArr.push_back(digits[ptr] - '0');
                    //cout << digits[ptr] << endl;
                    ++ptr;
               }
               // cout << *this;
               // flip array to correct order since we added from the back
               this->normalize(true);
          }
          /* 
          assignment operator overloading for BigUnsigned
          Explicit copy control not needed since 
          we are not using dynamic memory
          */
          BigUnsigned& operator=(const BigUnsigned& rhs){
               // Clear up current array
               numArr.clear();
               // add_digits (same as copying since now numArr is empty)
               *this += rhs;
               return *this;
          }
          // abstract adding logic to reduce clutter
          int plusEqHelper(int sum, int index){
               int tSum = sum;
               if(tSum < 10 && index < numArr.size()){
                    numArr[index] = tSum;
                    tSum = 0;
               }else if (tSum >= 10 && index < numArr.size()){
                    numArr[index] = tSum%10;
                    tSum /= 10;
               }else if(tSum >= 10 && index >= numArr.size()){
                    numArr.push_back(tSum%10);
                    tSum /= 10;
               }else{
                    numArr.push_back(tSum);
                    tSum = 0;
               }
               return tSum;
          }
          // += operator overloading for BigUnsigned as a member function
          BigUnsigned& operator+=(const BigUnsigned& rhs){
               // Iterate through the entire forloop, 
               // adding to respective index
               // Add numbers so long index < this size() & index < rhs size()
               int index = 0;
               int sum = 0;
               while(index < numArr.size() && index < rhs.numArr.size()){
                    sum += numArr[index] + rhs.numArr[index];
                    sum = plusEqHelper(sum, index);
                    ++index;
               }
               // Add till we iterate through this size()
               while(index < numArr.size() && sum != 0){
                    sum += numArr[index];
                    sum = plusEqHelper(sum, index);
                    ++index;
               }
               // Add till we iterate through rhs size()
               while(index < rhs.numArr.size()){
                    sum += rhs.numArr[index];
                    sum = plusEqHelper(sum, index);
                    ++index;
               }
               // Add the remaining sum since we have iterated through both
               // generally could be an if statement but we are using while
               // to catch any weird behavior that may occur
               while(sum != 0){
                    sum = plusEqHelper(sum, index);
                    ++index;
               }
               return *this;
          }
          

          //pre decrement
          BigUnsigned& operator++(){
               *this += 1;
               return *this;
          }
          //post decrement
          BigUnsigned operator++(int){
               BigUnsigned temp = *this;
               *this += 1;
               return temp;
          }

          explicit operator bool() const{
               return numArr[0] != 0 || numArr.size() > 1;
          }
     
     private:
          // Normalize vectors and flip if necessary
          // made private to prevent user from calling it
          void normalize(bool flip){
               if(numArr.size() == 0){
                    numArr.push_back(0);
               }else if(flip){
                    // Flip array via swapping
                    for(size_t i = 0; i < numArr.size()/2; ++i){
                         int temp = numArr[i];
                         numArr[i] = numArr[numArr.size() - i - 1];
                         numArr[numArr.size() - i - 1] = temp;
                    }
               }
          }
          // vector to store the digits
          vector<int> numArr;

};
// non-member function prototypes
// + operator overloading for BigUnsigned
BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs);
// operator> overloading for BigUnsigned
bool operator>(const BigUnsigned& lhs, const BigUnsigned& rhs);
// operator>= overloading for BigUnsigned
bool operator>=(const BigUnsigned& lhs, const BigUnsigned& rhs);
// operator<= overloading for BigUnsigned
bool operator<=(const BigUnsigned& lhs, const BigUnsigned& rhs);
// operator== overloading for BigUnsigned
bool operator!=(const BigUnsigned& lhs, const BigUnsigned& rhs);

int main() {

     // Test code for BigUnsigned provided by the John Sterling
     BigUnsigned zero;
     BigUnsigned one(1);

     cout << "zero: " << zero << endl;
     cout << "one: " << one << endl;

     BigUnsigned val = 1;
     cout << "val: " << val << endl;
     cout << "++val: " << ++val << endl;
     cout << "val: " << val << endl;
     cout << "val++: " << val++ << endl;
     cout << "val: " << val << endl;
     
     cout << "(one + zero): " << (one + zero) << endl;
     cout << "(one + one): " <<  (one + one) << endl;

     cout << boolalpha;
     cout << "one < one: " << (one < one) << endl;
     cout << "zero < one: " << (zero < one) << endl;

    BigUnsigned a = 123;
    BigUnsigned b = 1234;
    BigUnsigned c = 124;
    BigUnsigned d = 12345;

    cout << "a: " << a << ", b: " << b 
         << ", c: " << c << ", d: " << d << endl;
    cout << "a + d: " << (a + d) << endl;
    cout << "d + d: " << (d + d) << endl;
    cout << "a < d: " << (a < d) << endl;
    cout << "d < a: " << (d < a) << endl;
    cout << "zero == zero: " << (zero == zero) << endl
         << "zero == one: " << (zero == one) << endl
         << "a == a: " << (a == a) << endl
         << "a == d: " << (a == d) << endl
         << "d == a: " << (d == a) << endl;

     cout << "(zero == 0): " << (zero == 0) << endl
         << "(one == 0): " << (one == 0) << endl
         << "(1 == one): " << (1 == one) << endl;

//     // +=
     cout << "b: " << b << ", c: " << c << endl;
     cout << "(c += b): " << (c += b) << endl;
     cout << "b: " << b << ", c: " << c << endl;


     BigUnsigned x = a;
     cout << "x: " << x << ", a: " << a << endl
         << "x == a: " << (x == a) << endl
         << "a == x: " << (a == x) << endl
         << "a < x: " << (a < x) << endl
         << "a > x: " << (a > x) << endl;
    
    cout << "x > a: " << (x > a) << endl
         << "x >= a: " << (x >= a) << endl
         << "x <= a: " << (x <= a) << endl
         << "x != a: " << (x != a) << endl;
         
    
    BigUnsigned big("987654321");
    BigUnsigned big2("  ");
    BigUnsigned big3("felix");
    BigUnsigned big4("00987654321");

    cout << "big: " << big << endl
         << "big2: " << big2 << endl
         << "big3: " << big3 << endl
         << "big4: " << big4 << endl;

    BigUnsigned big5(98765);
    BigUnsigned big6(2457);
    cout << "big5: " << big5  << ", big6: " <<  big6 << endl
         << "(big5 + big6): " << (big5 + big6) << endl
         << "(big6 + big5): " << (big6 + big5) << endl;


    cout << zero << " is " << (zero ? "true" : "false") << endl;
    cout << one << " is " << (one ? "true" : "false") << endl;
    cout << big4 << " is " << (big4 ? "true" : "false") << endl;
}
// Output operator for BigUnsigned
ostream& operator<<(ostream& lhs, const BigUnsigned& rhs) {
     for(size_t i = rhs.numArr.size(); i > 0; --i){
          lhs << rhs.numArr[i-1];
     }
     return lhs;
}
// == operator overloading for BigUnsigned comparing by indicies
bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs){
     bool isEQ = true;
     if(!(lhs.numArr.size() == rhs.numArr.size())){
          isEQ = false;
     }else{
          for(size_t i = 0; i < lhs.numArr.size(); ++i){
               if(!(lhs.numArr[i] == rhs.numArr[i])){
                    isEQ = false;
                    break;
               }
          }
     }
     return isEQ;
}
// < operator overloading for BigUnsigned comparing by indicies
bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs) {
     bool isEQ = true;
     if(lhs.numArr.size() > rhs.numArr.size()){
          isEQ = false;
     }else{
          for(size_t i = lhs.numArr.size(); i > 0 ; --i){
               if((lhs.numArr[i - 1]  >= rhs.numArr[i - 1])){
                    isEQ = false;
                    break;
               }
          }
     }
     return isEQ;
}
// + operator overloading for BigUnsigned
BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs){
     BigUnsigned temp = lhs;
     temp += rhs;
     return temp;
}
// > operator overloading for BigUnsigned
bool operator>(const BigUnsigned& lhs, const BigUnsigned& rhs)  {
     return !(lhs < rhs || lhs == rhs );
}
// >= operator overloading for BigUnsigned
bool operator>=(const BigUnsigned& lhs, const BigUnsigned& rhs)  {
     return !(lhs < rhs);
}
// <= operator overloading for BigUnsigned
bool operator<=(const BigUnsigned& lhs, const BigUnsigned& rhs)  {
     return lhs < rhs || lhs == rhs;
}
// != operator overloading for BigUnsigned
bool operator!=(const BigUnsigned& lhs, const BigUnsigned& rhs)  {
     return !(lhs == rhs);
}


