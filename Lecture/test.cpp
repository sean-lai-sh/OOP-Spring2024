#include <iostream>
#include<string>
using namespace std;

char cypherChar(const int& shiftValue, const char& token){
    int shiftingBy = (token - shiftValue - 65)%26;
    if(shiftingBy < 0){
        char original = 91 + shiftingBy;
        return original;
    }else if(shiftingBy > 0){
        char original = 64 + shiftingBy;
        return original;
    }else{
        return token;
    }
}

int main(){
    std::cout <<"Testing general executable folder";
    std::string s = "AAesting  123";

    cout << s[0] << endl;
    s[0] += 1;
    cout << s[0] << endl;
    s[0] -= 66;
    cout << (int) s[0] << endl;
    
    cout << cypherChar(1, s[1]);


}