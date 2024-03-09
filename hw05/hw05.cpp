/*
Author: Sean Lai Sheng Hong
File: hw05.cpp
Purpose: Simulate fights between Noble using Warrior armies using heap memory
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// Your Noble and Warrior classes should go here.

// Warrior: Battles for a Noble
class Warrior{
     friend ostream& operator<<(ostream& os, const Warrior& rhs);
     public:
          // Constructor
          Warrior(const string& name, const double& strength): 
          name(name), strength(strength), hired(false){}
          // Get the strength of the warrior
          double getStrength() const{
               return strength;
          }
          // Get the name of the warrior
          const string& getName() const{
               return name;
          }
          // Check name of the warrior
          bool checkName(const string& name) const{
               return this->name == name;
          }
          // Reduce the strength of the warrior
          void reduceStrength(double ratio){
               strength -= strength*ratio;
          }
          // Set the hired status of the warrior
          void setHired(bool status){
               hired = status;
          }
          // Check if the warrior is hired
          bool isHired() const{
               return hired;
          }
     private:
     // Data members
          string name;
          double strength;
          bool hired;
};

// Noble: Manages Warriors and Battles other Nobles
class Noble{
     friend ostream& operator<<(ostream& os, const Noble& rhs);
     public:
            // Constructor
            Noble(const string& name): name(name), armyStrength(0){}
            // Battle another Noble
            void battle(Noble& otherNoble){
                // print who is battling who
                cout << name << " battles " << otherNoble.name << endl;
                // if both are dead
                if (armyStrength == -1 && otherNoble.armyStrength == -1){
                        cout << "Oh, NO! They're both dead! Yuck!" << endl;
                }
                // if one is dead
                else if (armyStrength == -1){
                        cout << "He's dead, " << otherNoble.name << endl;
                }
                // if the other is dead
                else if (otherNoble.armyStrength == -1){
                        cout << "He's dead, " << name << endl;
                        // debugging only
                }
                // if one is stronger than the other
                else if (armyStrength > otherNoble.armyStrength){
                        cout << name << " defeats " << otherNoble.name << endl;
                        double ratio = otherNoble.armyStrength/armyStrength;
                        // reduce the strength of the noble's army
                        for (size_t i = 0; i < army.size(); i++){
                            army[i]->reduceStrength(ratio);
                        }
                        // set the other noble's army strength to 0
                        for (size_t i = 0; i < otherNoble.army.size(); i++){
                            otherNoble.army[i]->reduceStrength(1);
                        }
                        armyStrength *= ratio;
                        otherNoble.armyStrength = -1;
                }
                // if the other is stronger than the one
                else if (armyStrength < otherNoble.armyStrength){
                        cout << otherNoble.name << " defeats " << name << endl;
                        double ratio = armyStrength/otherNoble.armyStrength;
                        // reduce the strength of the winner's  army
                        for (size_t i = 0; i < otherNoble.army.size(); i++){
                            otherNoble.army[i]->reduceStrength(ratio);
                        }
                        // set the noble's army strength to 0
                        for (size_t i = 0; i < army.size(); i++){
                            army[i]->reduceStrength(1);
                        }

                        otherNoble.armyStrength *= ratio;
                        armyStrength = -1;
                }
                // if both are equally strong
                else{
                        cout << "Mutual Annihilation: " 
                        << name << " and " << otherNoble.name 
                        << " die at each other's hands" << endl;
                        armyStrength = -1;
                        otherNoble.armyStrength = -1;
                        // set both armies to 0
                        for (size_t i = 0; i < army.size(); i++){
                            army[i]->reduceStrength(1);
                        }
                        for (size_t i = 0; i < otherNoble.army.size(); i++){
                            otherNoble.army[i]->reduceStrength(1);
                        }
                }
            }
            // Check Name of the Noble
            bool checkName(const string& name) const{
                return this->name == name;
            }
            // Hire a warrior
            bool hire(Warrior& warrior){
               // check if the noble is dead
                if (armyStrength == -1){
                    return false;
                }
                // Check if the warrior is already hired
                if (warrior.isHired()){
                    cout << name << " failed to hire " 
                    << warrior.getName() << endl;
                    return false;
                }
                army.push_back(&warrior);
                armyStrength += warrior.getStrength();
                warrior.setHired(true);
                //cout << name << " hires " << warrior.name << endl;  
                return true;
            }
            // Fire a warrior
            bool fire(Warrior& warrior){
                // check if the noble is dead
                if (armyStrength == -1){
                        cout << name << 
                        " is dead and cannot fire "
                         << warrior.getName() << endl;
                        return false;
                }
                // Check if the warrior is in the army
                for (size_t i = 0; i < army.size(); i++){
                        if (army[i] == &warrior){
                            armyStrength -= warrior.getStrength();
                            warrior.setHired(false);
                            for (size_t j = i; j < army.size()-1; j++){
                                army[j] = army[j+1];
                            }
                            army.pop_back();
                            cout << warrior.getName() << 
                            ", you don't work for me any more! -- " 
                            << name << endl;
                            return true;
                        }
                }
                cout << name << " failed to fire " << warrior.getName() << endl;
                return false;
            }
     private:
          string name;
          double armyStrength;
          vector<Warrior*> army;
};

// Check if the warrior exists in the vector
size_t warriorExists(const vector<Warrior*>& storage, const string& warriorName);
// Check if the noble exists in the vector
size_t nobleExists(const vector<Noble*>& storage, const string& nobleName);
// Battle two nobles utilizing the fileReader
void nobleBattles(ifstream& fileReader, 
                const vector<Noble*>& nobles);
// Prints the status of all warriors and nobles
void warriorNobleStatus(
    const vector<Noble *>& nobles, 
    const vector<Warrior *>& warriors);

// Let a noble hire a warrior with error checking
void processHire(ifstream& fileReader, 
                const vector<Noble *>& nobles, 
                const vector<Warrior *>& warriors);
// create warrior to Vector + error checking
void createWarrior(ifstream& fileReader, vector<Warrior *>& warriors);
// fire warrior from a Noble + error checking
void fireWarrior(ifstream& fileReader, 
                const vector<Noble *>& nobles, 
                const vector<Warrior *>& warriors);
// create noble to Vector + error checking
void createNoble(ifstream& fileReader, vector<Noble *>& nobles);

int main()
{
    vector<Warrior*> warriors;
    vector<Noble*> nobles;
    ifstream fileReader("nobleWarriors.txt"); 
    if(!fileReader){
        // check if file exists
        cerr << "File not found\n";
        exit(1);
    }
    string command;
    while(fileReader >> command){
        if(command == "Noble"){
            // Create a new noble
            createNoble(fileReader, nobles);
        }else if(command == "Warrior"){
            // Create a new warrior
            createWarrior(fileReader, warriors);
        }else if(command == "Hire"){
            // Hire a warrior
            processHire(fileReader, nobles, warriors);
        }else if(command == "Fire"){
            // Fire a warrior
            fireWarrior(fileReader, nobles, warriors);
        }else if(command == "Battle"){
            /// Battle two nobles
            nobleBattles(fileReader, nobles);
        }else if(command == "Status"){
            // Display all warriors and nobles
            warriorNobleStatus(nobles, warriors);
        }else if(command == "Clear"){
            // Clear all the heap memory for nobles
            for(size_t i = 0; i < nobles.size(); i++){
                delete nobles[i];
                nobles[i] = nullptr;
            }
            nobles.clear();
            // Clear all the heap memory for warriors
            for(size_t i = 0; i < warriors.size(); i++){
                delete warriors[i];
                warriors[i] = nullptr;
            }
            warriors.clear();
        }
    }
}

// create a new noble
void createNoble(ifstream& fileReader, vector<Noble *>& nobles)
{
    string nobleName;
    fileReader >> nobleName;
    // check if the noble already exists
    if (nobleExists(nobles, nobleName) != nobles.size())
    {
        cerr << "Noble already exists\n";
    }
    else
    {
        // create a new noble
        Noble *newNoble = new Noble(nobleName);
        nobles.push_back(newNoble);
    }
}
// fire a warrior from a noble
void fireWarrior(ifstream& fileReader,
                const vector<Noble *>& nobles,
                const vector<Warrior *>& warriors)
{
    string nobleName, warriorName;
    fileReader >> nobleName >> warriorName;
    size_t nobleIndex = nobleExists(nobles, nobleName);
    size_t warriorIndex = warriorExists(warriors, warriorName);
    if (nobleIndex != nobles.size() && warriorIndex != warriors.size())
    {
        nobles[nobleIndex]->fire(*warriors[warriorIndex]);
    }
    else if (nobleIndex == nobles.size())
    {
        cerr << "Noble does not exist\n";
    }
    else
    {
        cerr << "Attempt to fire a non-existent warrior\n";
    }
}
// create a new warrior to the vector
void createWarrior(ifstream& fileReader, vector<Warrior *>& warriors)
{
    string warriorName;
    double warriorStrength;
    fileReader >> warriorName >> warriorStrength;
    // check if the warrior already exists
    if (warriorExists(warriors, warriorName) != warriors.size())
    {
        cerr << "Warrior already exists\n";
    }
    else
    {
        Warrior *newWarrior = new Warrior(warriorName, warriorStrength);
        warriors.push_back(newWarrior);
    }
}
// Battle two nobles
void nobleBattles(ifstream& fileReader, const vector<Noble *>& nobles)
{
    // Battle two nobles
    string noble1, noble2;
    fileReader >> noble1 >> noble2;
    size_t nobleIndex1 = nobleExists(nobles, noble1);
    size_t nobleIndex2 = nobleExists(nobles, noble2);
    /// check if the nobles exist
    if (nobleIndex1 != nobles.size() && nobleIndex2 != nobles.size())
    {
        nobles[nobleIndex1]->battle(*nobles[nobleIndex2]);
    }
    else
    {
        // if one or both of the nobles do not exist
        cerr << "Noble(s) does not exist\n";
    }
}
// Overload the << operator for Warrior
ostream& operator<<(ostream& os, const Warrior& rhs){
     os << rhs.name << ": " << rhs.strength;
     return os;
}
// Overload the << operator for Noble
ostream& operator<<(ostream& os, const Noble& rhs){
     os << rhs.name << " has an army of " << rhs.army.size();
     for (size_t i = 0; i < rhs.army.size(); i++){
          os << "\n     " << *rhs.army[i];
     }
     return os;
}
// Check if the warrior exists in the vector
size_t warriorExists(const vector<Warrior*>& storage, const string& warriorName){
     for(size_t i = 0; i < storage.size(); ++i){
        // check if the warrior exists via name since the name is unique
          if(storage[i]->checkName(warriorName)){
               return i;
          }
     }
     return storage.size();
}
// Check if the noble exists in the vector
size_t nobleExists(const vector<Noble*>& storage, const string& nobleName){
     for(size_t i = 0; i < storage.size(); ++i){
        // check if the noble exists via name since the name is unique
          if(storage[i]->checkName(nobleName)){
               return i;
          }
     }
     return storage.size();
}
// Let a noble hire a warrior with error checking
void processHire(ifstream& fileReader, 
                const vector<Noble *>& nobles, 
                const vector<Warrior *>& warriors)
{
    string nobleName, warriorName;
    fileReader >> nobleName >> warriorName;
    size_t nobleIndex = nobleExists(nobles, nobleName);
    size_t warriorIndex = warriorExists(warriors, warriorName);
    // check if the noble and warrior exist
    if (nobleIndex != nobles.size() && warriorIndex != warriors.size())
    {
        nobles[nobleIndex]->hire(*warriors[warriorIndex]);
    }
    else if (nobleIndex == nobles.size())
    {
        // if the noble does not exist
        cerr << "Noble "
             << nobleName
             << " a non-existent noble cannot hire"
             << warriorName << "\n";
    }
    else if (warriorIndex == warriors.size())
    {
        // if the warrior does not exist
        cerr << "Attempted to hire a non-existent warrior: "
             << warriorName << "\n";
    }
}
// Prints the status of all warriors and nobles
void warriorNobleStatus(const vector<Noble *> &nobles, 
                        const vector<Warrior *> &warriors)
{
    // Display the status of all warriors and nobles
    // tabbed for formatting
    cout << "Status\n"
         << "======" << endl;
    cout << "Nobles:" << endl;
    if (nobles.size() != 0)
    {
        // Display all nobles
        for (size_t i = 0; i < nobles.size(); i++)
        {
            cout << *nobles[i] << endl;
        }
    }
    else
    {
        cout << "NONE" << endl;
    }
    cout << "\nUnemployed Warriors:" << endl;

    // Display all unemployed warriors (not hired by any noble)
    bool allEmployed = true;
    for (size_t i = 0; i < warriors.size(); i++)
    {
        if (!warriors[i]->isHired())
        {
            cout << "     " << *warriors[i] << endl;
            allEmployed = false;
        }
    }
    if (allEmployed)
    // if all warriors are employed
    {
        cout << "NONE" << endl;
    }
}