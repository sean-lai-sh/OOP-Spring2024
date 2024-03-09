#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <utility>
using namespace std;

struct carbohydrate{
    vector<string> names;
    int carbon;
    /// Since carbon is always 0-infinity, we can use size_t
    int hydrogen;
};

void openFile(ifstream& fileReader);

void processFile(ifstream& fileReader, vector<carbohydrate>& output);

void displayFormula(const vector<carbohydrate>& output);

void sortVector(vector<carbohydrate>& fileLines);

size_t findFormula(const vector<carbohydrate>& names, int carbon, int hydrogen);

void printFormula(const carbohydrate& formulas);

void addName(vector<carbohydrate>& names, int carbon, int hydrogen, const string& name);

int main(){
    ifstream fileReader;
    openFile(fileReader);
    vector<carbohydrate> fileLines;
    processFile(fileReader, fileLines);
    cout << "Unsorted: " << endl;
    displayFormula(fileLines);
    sortVector(fileLines);
    cout << "Sorted: " << endl;
    displayFormula(fileLines);
}

void openFile(ifstream& fileReader){
    string fileName;
    // Repeat until provided valid file name
    do{
        cout << "Filename: ";
        cin >> fileName;
        fileReader.open(fileName);
    }while (!fileReader);
    cout << "file is open" << endl;
}

void addName(vector<carbohydrate>& names, int carbon, int hydrogen, const string& name){
    size_t index = findFormula(names, carbon, hydrogen);
    if(index == names.size()){
        carbohydrate newCarb;
        newCarb.carbon = carbon;
        newCarb.hydrogen = hydrogen;
        newCarb.names.push_back(name);
        names.push_back(newCarb);
    }else{
        names[index].names.push_back(name);
    }
}

size_t findFormula(const vector<carbohydrate>& names, int carbon, int hydrogen){
    // Linear search for the formula
    for(size_t i = 0; i < names.size(); ++i){
        if(names[i].carbon == carbon && names[i].hydrogen == hydrogen){
            return i;
        }
    }
    return names.size();
}

void processFile(ifstream& fileReader, vector<carbohydrate>& output){
    string name;
    int carbon;
    int hydrogen;
    char carbonToken; // collect the C char
    char hydrogenToken; // collect the H char
    //repeat each time a name, carbon, and hydrogen is found
    // adding it to the output vector
    while(fileReader >> name >> carbonToken >> carbon >> hydrogenToken >> hydrogen){
        // cout << name << " " << carbon << " " << hydrogen << endl;
        addName(output, carbon, hydrogen, name);
    }
}

void printFormula(const carbohydrate& formulas){
    // print # of Carbon and Hydrogen
    cout << "C" << formulas.carbon << "H" << formulas.hydrogen << " ";
    // Print all formula banes
    for(size_t i = 0; i < formulas.names.size(); ++i){
        cout << " " << formulas.names[i] << " ";
    }
    cout << endl;
}

void displayFormula(const vector<carbohydrate>& output){
    // Print all the formulas using function
    for(const carbohydrate& formula : output){
        printFormula(formula);
    }
}
void sortVector(vector<carbohydrate>& fileLines){
    //bubble sort
    for(size_t i = 0; i < fileLines.size(); ++i){
        for(size_t j = i+1; j < fileLines.size(); ++j){
            //Check carbon is the same
            if(fileLines[i].carbon > fileLines[j].carbon){
                swap(fileLines[i], fileLines[j]);
            //check hydrogen is the same
            }else if (fileLines[i].carbon == fileLines[j].carbon){
                if(fileLines[i].hydrogen > fileLines[j].hydrogen){
                    swap(fileLines[i], fileLines[j]);
                }
                    
            }
        }
    }
}