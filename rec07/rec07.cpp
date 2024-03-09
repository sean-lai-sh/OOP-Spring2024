/*
  rec07_begin.cpp
  CS2124
  Implement the class Rational, so that the following program works.
 */

#include <iostream>
using namespace std;

int greatestCommonDivisor(int x, int y);

// Put your Rational class here.
class Rational{
    friend ostream& operator<<(ostream& lhs, const Rational& rhs);
    friend istream& operator>>(istream& lhs, Rational& rhs);
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);
    public:
        Rational(int num = 0, int denominator = 1) : numerator(num), denominator(denominator) {
            this->normalize();
        }
        void normalize(){
            if(denominator == 0){
                denominator = 1;
            }

            int gCD = greatestCommonDivisor(numerator, denominator);
            numerator /= gCD;
            denominator /= gCD;

            if(denominator < 0){
                // cout << denominator << numerator;
                denominator *= -1;
                numerator *= -1;
            }
        }
        Rational& operator+=(const Rational& rhs){
            int gCD = greatestCommonDivisor(this->numerator, rhs.numerator);
            numerator = numerator*gCD + rhs.numerator *gCD;
            denominator = denominator * gCD;
            this->normalize();
            return *this;
        }
        // Pre
        Rational& operator++() {
            *this += 1;
            return *this;
        }
        //Post
        Rational operator++(int){
            Rational temp = *this;
            *this += 1;
            return temp;
        }
        explicit operator bool() const{
            return numerator != 0;
        }
    private:
        int numerator;
        int denominator;
};
// Any functions that are not members and not friends should have
// prototypes here and their definitions after main.
Rational operator+(const Rational& lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);
Rational& operator--(Rational& ref);
Rational operator--(Rational& ref, int);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);

int main()
{
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;
    
    // // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;
    
    // // How does this manage to work?
    // // It does NOT require writing another == operator. 
    cout << "1 == one: " << boolalpha << (1 == one) << endl;
    
    // // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // // Even though the above example, (a++ ++), compiled, the
    // // following shouldn't.
    // // But some compiler vendors might let it...  Is your compiler
    // // doing the right thing? Why shouldn't it compile?
    // //cout << "a-- -- = " << (a-- --) << endl;
    // cout << "a = " << a << endl;


    // // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    } 

    // // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    } 

    // cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : " 
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
}

int greatestCommonDivisor(int x, int y)
{
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

// Any functions that are not members and not friends should have
// their definitions here...
ostream& operator<<(ostream& lhs, const Rational& rhs)  {
    cout << rhs.numerator << "/" << rhs.denominator;
    return lhs;
}

istream& operator>>(istream& lhs, Rational& rhs){
    int num, den;
    char delimiter;
    lhs >> num >> delimiter >> den;
    rhs.numerator = num;
    rhs.denominator = den;
    /// cout << rhs.numerator << rhs.denominator;
    rhs.normalize();
    return lhs;

}

// + operator
Rational operator+(const Rational& lhs, const Rational& rhs){
    Rational temp = lhs;
    temp += rhs;
    return temp;
}

bool operator==(const Rational& lhs, const Rational& rhs){
    return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
}

bool operator<(const Rational& lhs, const Rational& rhs){
    return lhs.numerator * rhs.denominator < lhs.denominator * rhs.numerator;
}

bool operator!=(const Rational& lhs, const Rational& rhs){
    return !(rhs==lhs);
}

Rational& operator--(Rational& ref){
    ref += -1;
    return ref;
}

Rational operator--(Rational& ref, int){
    Rational temp = ref;
    temp += -1;
    return temp;
}

bool operator<=(const Rational& lhs, const Rational& rhs){
    return lhs < rhs || lhs == rhs;
}

bool operator>(const Rational& lhs, const Rational& rhs){
    return !(lhs == rhs || lhs < rhs);
}

bool operator>=(const Rational& lhs, const Rational& rhs){
    return !(lhs < rhs);
}
