#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

//Q15
void printIntVector(const vector<int>& value);

void doubleIntVector(vector<int>& toChange);

void doubleIntVector2(vector<int>& toChange);

int main(){
    /// SECTION 1: Output
    std::cout << "Hello World!" << std::endl; // part 1
    cout << "Hello World Simplified!" << endl; // part 2
    int x;
    cout << "Here is the variable x which is currently undefined: " << x << endl; // part 3
    /// SECTION 2: Static Typing
    int y = 17;
    int z = 2000000017;
    double pie = 3.1415926;
    cout << "Y: " << sizeof(y) << endl; 
    cout << "Z: " << sizeof(z) << endl;
    cout << "pie: " << sizeof(pie) << endl;
    // Assigning the string felix to x results in an compile time error
    /// SECTION 3: Conditions
    if ( y >= 10 && y <= 20){
        cout << "Y is between 10 and 20" << endl;
    }
    else{
        cout << "Y is not between 10 and 20" << endl;
    }
    /// SECTION 4: Loops
    // Q7
    for (int i = 10; i <= 20; i++){
        cout << i << " ";
    }
    cout << endl;
    int initialVal = 10;
    while (initialVal <= 20){
        cout << initialVal << " ";
        initialVal++;
    }
    cout << endl;
    int initialVal2 = 10;
    do{
        cout << initialVal2 << " ";
        initialVal2++;
    }while(initialVal2 <= 20);
    cout << endl;
    // Q8
    ifstream ifs;
    string fileName;
    while (!ifs){
        cout << "Filename: ";
        cin >> fileName;
        ifs.open(fileName);
    }

    // Task 9 Read each token from file
    string word;
    while(ifs >> word){
        cout << word << endl;
    }
    ifs.close();
    // task 10
    ifstream integerReader("integers.txt");
    int sum = 0;
    int temp;
    while(integerReader >> temp){
        sum += temp;
    }
    cout << "integer.txt sum is: " << sum << endl;
    integerReader.close();
    // task 11
    ifstream mixedReader("mixed.txt");
    int nextToken;
    int sumToken = 0;
    while(mixedReader >> nextToken){
        sumToken += nextToken;
    }
    cout<<"mixed.txt sum is " << sumToken << endl;
    mixedReader.close();
    //task 12
    vector<int> evensOnly(46, 10);
    for( size_t i = 1; i < evensOnly.size(); ++i){
        evensOnly[i] += 2 * i;
        
    }
    //task 13
    for(size_t i = 0; i < evensOnly.size(); ++i){
        cout << evensOnly[i] << " ";
    }
    cout << endl << "Ranged For approach";
    for(int value : evensOnly){
        cout << value << " ";
    }
    cout << endl << "Backwards";
    for(size_t i = evensOnly.size(); i > 0; --i){
        cout << evensOnly[i-1] << " ";
    }
    cout << endl;

    //task 14
    vector<int> primesBeforeTwenty{2,3,5,7,11,13,17,19};

}

void printIntVector(const vector<int>& value){
    for(size_t i = 0; i < value.size(); ++i){
        cout << value[i] << " ";
    }
    cout << endl;
}

void doubleIntVector(vector<int>& toChange){
    for(size_t i = 0; i < toChange.size(); ++i){
       toChange[i] *= 2;
    }
    printIntVector(toChange); // for testing
}

void doubleIntVector2(vector<int>& toChange){
    for(int& value : toChange){
       value *= 2;
    }
    printIntVector(toChange); // for testing
}