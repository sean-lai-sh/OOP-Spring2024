// Author : Sean Lai
// File Name : hw03.cpp
// File Purpose : Implement a program that reads a file and simulates a battle between warriors
// Date : 02/14/2024
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Warrior class to store warrior information
class Warrior{
    
    class Weapon{        
        friend ostream& operator<<(ostream& os, const Warrior::Weapon& rhs);
        friend int currentWeaponStrength();
        public:
            // Constructor. Tabbed for readability
            Weapon(const string& weaponName, const int& weaponStrength): 
            name(weaponName), strength(weaponStrength){}

            int getStrength() const{
                return strength;
            }
            void reduceStrength(const int& deltaStrength){
                strength -= deltaStrength;
                if (strength < 0){ 
                    // ensure that all strength of a dead warrior is 0
                    strength = 0;
                }
            }
        private:
            string name;
            int strength;    
    };
    // Overload the << operator to print the warrior
    friend ostream& operator<<(ostream& os, const Warrior& rhs);
    friend ostream& operator<<(ostream& os, const Warrior::Weapon& rhs);
// friend int compareStrength(const Warrior& otherWarrior); NOT NEEDED
    public:
        
        // Constructor. Tabbed for readability
        Warrior(const string& warriorName, 
                const string& weaponName, 
                const int& warriorStrength): 
        name(warriorName), weaponName(weaponName, warriorStrength){}

        // Compare the strength of two warriors (used for battle)
        // int compareStrength(const Warrior& otherWarrior) const {
        //     // check if otherWarrior is not null
        //     if(!otherWarrior){
        //         cerr<< "Warrior does not exist\n";
        //         return weaponName.getStrength();
        //     }
        //     return weaponName.getStrength() - otherWarrior.weaponName.getStrength();
        // }
        // Get strength of the warrior
        int currentWeaponStrength() const{
            return weaponName.getStrength();
        }

        // Battle two warriors and print the result
        void battle(warrior2& warrior2){
    
            // Get the name of the two warriors to allow >> operator without errors
            string firstWarriorName = firstWarrior.name();
            string secondWarriorName = secondWarrior.name();
            // Print the battle
            cout << firstWarriorName << " battles " << secondWarriorName << endl;
            // Check if both warriors are dead
            int result = firstWarrior.compareStrength(secondWarrior);
            if(firstWarrior.currentWeaponStrength() == 0 && secondWarrior.currentWeaponStrength() == 0){
                cout << "Oh, NO! They're both dead! Yuck!" << endl;
            }else if(firstWarrior.currentWeaponStrength() == 0){
                // Check if warrior1 is dead
                cout << "He's dead, " << secondWarriorName << endl;
            }else if(secondWarrior.currentWeaponStrength() == 0){
                // Check if warrior2 is dead
                cout << "He's dead, " << firstWarriorName << endl;
            }
                firstWarrior.fight(secondWarrior); // Conduct the battle
            // Check if both warriors have the same strength
            if(result == 0){
            // output the result and tabbed for readability
                cout << "Mutual Annihilation: " 
                << firstWarriorName << " and " << secondWarriorName 
                << " die at each other's hands" << endl;
            }else if(result > 0){
                // Check if warrior1 has more strength than warrior2
                cout << firstWarriorName << " defeats " << secondWarriorName << endl;
            }else{
                // if  warrior2 has more strength than warrior1
                cout << secondWarriorName << " defeats " << firstWarriorName << endl;
            }
        }

        //fight against another warrior and deduct their strength
        bool fight(Warrior& otherWarrior){
            if(otherWarrior){
                cerr<< "Warrior does not exist\n";
                return false;
            }
            int toDeduct = otherWarrior.weaponName.getStrength();
            otherWarrior.changeWeaponStrength(weaponName.getStrength());  
            changeWeaponStrength(toDeduct);
            return true;
        }
        
        // Get the name of the warrior (Constant function to prevent modification of name)
        string getName() const{
            return name;
        }
    private:
    // private member variables
        string name;
        Weapon weaponName;
        // change the strength of the weapon
        void changeWeaponStrength(const int& deltaStrength){
            weaponName.reduceStrength(deltaStrength);
        }
        
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
// // Battle two warriors and print the result
// void battleWarriors(vector<Warrior>& output, const string& warrior1, const string& warrior2);

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
            // old: battleWarriors(fileLines, warrior1, warrior2);
            warrio1.battle(warrior2);
        }
    }
    fileReader.close(); //Close file stream
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
    string weaponName;
    int weaponStrength;
    fileReader >> warriorName >> weaponName >> weaponStrength;
    if (warriorExists(output, warriorName) != output.size()){
        cerr << "Warrior already exists\n";
    }else{
        Warrior newWarrior{warriorName, weaponName, weaponStrength};
        output.push_back(newWarrior);
    }
}




// Display all warriors and their weapon
void displayWarriors(const vector<Warrior>& allWarriors){
    cout << "There are: " << allWarriors.size() << " warriors" << endl;
    for(const Warrior&  aWarrior: allWarriors){
        cout<< aWarrior << endl;
    }
}

// Does warrior exist in the vector (linear search since vector is unsorted)
size_t warriorExists(const vector<Warrior>& storage, const string& warriorName){
    for(size_t i = 0; i < storage.size(); ++i){
        if(storage[i].getName() == warriorName){
            return i;
        }
    }
    return storage.size();
}



// Overload the << operator to print the warrior
ostream& operator<<(ostream& os, const Warrior& rhs){
    os << "Warrior: " << rhs.name << ", " << rhs.weaponName;
    return os;
}

// Overload the << operator to print the weapon
ostream& operator<<(ostream& os, const Warrior::Weapon& rhs){
    os << "weapon: " << rhs.name << ", " << rhs.strength;
    return os;

}

