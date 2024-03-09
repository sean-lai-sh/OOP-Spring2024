// Date: 01/31/2024
// Author: Sean Lai
// File Name: hw01.cpp
// File Purpose: Caesar Cypher Decryption from a text file
#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

char cypherChar(const int& shiftValue, const char& token);

void decryptLine(const int& shiftValue, string& line);

int main(){
    ifstream fileReader("encrypted.txt");
    if(!fileReader){ // check if file is found
        cerr << "File not found\n";
        exit(1); // end code prematurely since no file
    }
    int cypherValue;
    vector<string> fileLines; // vector to store file lines
    string line; // Create a temp variable to store the getline output
    if(fileReader >> cypherValue){ // find shifting value
        getline(fileReader, line); // skip \n after number
        // Iterate through each line and decrypt before adding to Vector
        while(getline(fileReader, line)){ 
            decryptLine(cypherValue, line); 
            // decrypt line before inserting into vector
            fileLines.push_back(line);
        }
        
    }else{
        // Iterate through each line and adding to Vector
        while(getline(fileReader, line)){ 
            fileLines.push_back(line);
        }
    }
    fileReader.close(); //Close file stream
    // print backwards the entire file through the vector
    for(size_t i = fileLines.size(); i > 0; --i){
        cout << fileLines[i-1] << "\n";
    }
}

// Decrypts a char by shifting each character by shiftValue
// shiftvalue is the key to reverse the caesar cypher shifting
// token references the char to decrypt and is from A-Z.
char cypherChar(const int& shiftValue, const char& token){
    int shiftingBy = (token - shiftValue - 65) % 26;
    // Perform Modulo Operation to prevent
    if(shiftingBy < 0){ // Negative after shifting implies start from Z
        char original = 91 + shiftingBy;
        return original;
    }else{ // Positive implies start from A
        char original = 65 + shiftingBy;
        return original;
    }
}

// Decrypts a line by shifting each character by shiftValue
// shiftvalue is the key to reverse the caesar cypher shifting
// line references the string to decrypt
void decryptLine(const int& shiftValue, string& line){
    // Iterate through string
    // and decrypt a token if its an uppercase letter.
    for(char& token : line){
        if(token >= 'A' && token <= 'Z'){
            token = cypherChar(shiftValue, token);
        }
    }
}