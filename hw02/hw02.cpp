#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct Warrior{
    string name;
    int strength;
};
// Open the Warriors.txt file
void openFile(ifstream& fileReader);
// add Warrior to vector from filestream
void addWarrior(ifstream& fileReader, vector<Warrior>& output);
// Display a warrior and their strength
void displayWarriorStat(const Warrior& output);
// Display all warriors and their strength
void displayWarriors(const vector<Warrior>& allWarriors);
// Does warrior exist in the vector
size_t warriorExists(const vector<Warrior>& storage, const string& warriorName);
// Battle two warriors and print the result
void battleWarriors(vector<Warrior>& output, const string& warrior1, const string& warrior2);

int main(){
    ifstream fileReader;
    openFile(fileReader); // Open file
    vector<Warrior> fileLines; // store all warriors
    string command; // temp variable to store warrior name
    while(fileReader >> command){
        if(command == "Warrior"){
            // add warrior to vector
            addWarrior(fileReader, fileLines);
        }else if(command == "Status"){
            // display all warrior
            displayWarriors(fileLines);
        }else if(command == "Battle"){
            // battle two warriors
            string warrior1, warrior2;
            // read the two warriors to battle from file
            fileReader >> warrior1 >> warrior2;
            battleWarriors(fileLines, warrior1, warrior2);
        }
    }
}

// A valid isfile is assumed to be present
void openFile(ifstream& fileReader){
    fileReader.open("warriors.txt");
    if(!fileReader){
        cerr << "File not found\n";
        exit(1);
    }
}

// add Vector from filestream
void addWarrior(ifstream& fileReader, vector<Warrior>& output){
    string warriorName;
    int warriorStrength;
    fileReader >> warriorName >> warriorStrength;
    if (warriorExists(output, warriorName) != output.size()){
        cerr << "Warrior already exists\n";
    }else{
        Warrior newWarrior{warriorName, warriorStrength};
        output.push_back(newWarrior);
    }
}



// Display a warrior and their strength
void displayWarriorStat(const Warrior& output){
    cout << "Warrior: " << output.name << ", strength: " << output.strength << endl;
}

// Display all warriors and their strength
void displayWarriors(const vector<Warrior>& allWarriors){
    cout << "There are: " << allWarriors.size() << " warriors" << endl;
    for(const Warrior&  aWarrior: allWarriors){
        displayWarriorStat(aWarrior);
    }
}

// Does warrior exist in the vector (linear search since vector is unsorted)
size_t warriorExists(const vector<Warrior>& storage, const string& warriorName){
    for(size_t i = 0; i < storage.size(); ++i){
        if(storage[i].name == warriorName){
            return i;
        }
    }
    return storage.size();
}

// Battle two warriors and print the result
void battleWarriors(vector<Warrior>& output, const string& warrior1, const string& warrior2){
    size_t warrior1Index = warriorExists(output, warrior1);
    size_t warrior2Index = warriorExists(output, warrior2);

    Warrior& firstWarrior = output[warrior1Index];
    Warrior& secondWarrior = output[warrior2Index];
    // Print the battle
    cout << warrior1 << " battles " << warrior2 << endl;
    // Check if both warriors are dead
    if(firstWarrior.strength == 0 && secondWarrior.strength == 0){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }else if(firstWarrior.strength == 0){
        // Check if warrior1 is dead
        cout << "He's dead, " << warrior2 << endl;
    }else if(secondWarrior.strength == 0){
        // Check if warrior2 is dead
        cout << "He's dead, " << warrior1 << endl;
    }else if(firstWarrior.strength == secondWarrior.strength){
        // Check if both warriors have the same strength
        firstWarrior.strength = 0;
        secondWarrior.strength = 0;
        // output the result and tabbed for readability
        cout << "Mutual Annihilation: " 
        << warrior1 << " and " << warrior2 
        << " die at each other's hands" << endl;
    }else if(firstWarrior.strength > secondWarrior.strength){
        // Check if warrior1 has more strength than warrior2
        firstWarrior.strength -= secondWarrior.strength;
        secondWarrior.strength = 0;
        cout << warrior1 << " defeats " << warrior2 << endl;
    }else{
        // Check if warrior2 has more strength than warrior1
        secondWarrior.strength -= firstWarrior.strength;
        firstWarrior.strength = 0;
        cout << warrior2 << " defeats " << warrior1 << endl;
    }
}


