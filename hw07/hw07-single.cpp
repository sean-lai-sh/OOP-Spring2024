/*
Author: Sean Lai Sheng Hong
File: hw07.cpp
Purpose: Simulate fights between Noble using Warrior armies
            Practicing cyclic association.
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

// Your Noble and Warrior classes should go here.
// Promise of Class Noble.
class Noble;
// Warrior: Battles for a Noble
class Warrior{
    friend ostream& operator<<(ostream& os, const Warrior& rhs);
    public:
        // Constructor
        Warrior(const string& name, const double& strength);
        // Get the strength of the warrior
        double getStrength() const;
        // Get the name of the warrior
        const string& getName() const;
        // Check name of the warrior
        bool checkName(const string& name) const;
        // Reduce the strength of the warrior
        void reduceStrength(double ratio);
        // Set the hired status of the warrior
        void setHired(Noble* master);
        // Check if the warrior is hired
        bool isHired() const;
        // Runaway from the noble
        bool runaway();
    private:
    // Data members
        string name;
        double strength;
        bool hired;
        Noble* master;
};

// Noble: Manages Warriors and Battles other Nobles
class Noble{
    friend ostream& operator<<(ostream& os, const Noble& rhs);
    public:
        // Constructor
        Noble(const string& name);
        // Battle another Noble
        void battle(Noble& otherNoble);
        // Check Name of the Noble
        bool checkName(const string& name) const;
        // Get the name of the Noble
        const string& getName() const;
        // Hire a warrior
        bool hire(Warrior& warrior);
        // Fire a warrior
        bool fire(Warrior& warrior);
        // Remove a specific warrior from the army (helper function)
        bool removeWarrior(Warrior& warrior);
    private:
        string name;
        double armyStrength;
        vector<Warrior*> army;
};

int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 4);
    Warrior sky("Leia", 6);
    Warrior wizard("Merlin", 9);
    Warrior jaffa("Teal'c", 9);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(jaffa);
    art.hire(cheetah);
    art.hire(wizard);
    art.hire(sky);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(nimoy);

    cout << "================ Initial Status ===============" << endl;
    cout << art << endl
	 << lance << endl
	 << jim << endl
	 << linus << endl
	 << billie << endl;
    cout << "===============================================\n\n";

    art.fire(cheetah);
    wizard.runaway();
    cout << endl << art << endl;

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "\n================ Final Status ===============" << endl;
    cout << art << endl
	 << lance << endl
	 << jim << endl
	 << linus << endl
	 << billie << endl;

    // Tarzan and Merlin should be unemployed
    cout << "Tarzan's Hire Status: " << boolalpha 
	 << cheetah.isHired() << endl;
    cout << "Merlin's Hire Status: " << boolalpha 
	 << wizard.isHired() << endl;
    cout << "===============================================\n\n";
}

// Warrior Implementation
// Constructor for Warrior
Warrior::Warrior(const string& name, const double& strength): 
            name(name), strength(strength), hired(false), master(nullptr){}
// Get the strength of the warrior
double Warrior::getStrength() const{
    return strength;
}
// Get the name of the warrior
const string& Warrior::getName() const{
    return name;
}
// check name of the warrior
bool Warrior::checkName(const string& name) const{
    return this->name == name;
}
// Reduce the strength of the warrior
void Warrior::reduceStrength(double ratio){
    strength -= strength*ratio;
}
// Set the hired status of the warrior
bool Warrior::isHired() const{
    return master != nullptr;
}
// Set the hired status of the warrior
void Warrior::setHired(Noble* master){
    this->master = master;
}
// Runaway from the noble
bool Warrior::runaway(){
    if (master != nullptr){
        cout << name << " flees in terror, abandoning his lord, " 
        << master->getName() << endl;
        master->removeWarrior(*this);
        master = nullptr;
        return true;
    }
    return false;
}

// Overload the << operator for Warrior
ostream& operator<<(ostream& os, const Warrior& rhs){
     os << rhs.name << ": " << rhs.strength;
     return os;
}
// Noble Implementation
// Constructor for Noble
Noble::Noble(const string& name): name(name), armyStrength(0){}

// Get the name of the Noble
const string& Noble::getName() const{
    return name;
}
// Battle another Noble
void Noble::battle(Noble& otherNoble){
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
bool Noble::checkName(const string& name) const{
    return this->name == name;
}

// Hire a warrior
bool Noble::hire(Warrior& warrior){
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
    warrior.setHired(this);
    //cout << name << " hires " << warrior.name << endl;  
    return true;
}

// Fire a warrior from a Noble
bool Noble::fire(Warrior& warrior){
    // check if the noble is dead
    if (armyStrength == -1){
            cout << name << 
            " is dead and cannot fire "
                << warrior.getName() << endl;
            return false;
    }
    // Check if the warrior is in the army and remove it
    if(removeWarrior(warrior)){
        cout << "You don't work for me anymore " 
        << warrior.getName() << "! -- " << name << endl;
        return true;
    }
    cout << name << " failed to fire " << warrior.getName() << endl;
    return false;
}

bool Noble::removeWarrior(Warrior& warrior){
    for (size_t i = 0; i < army.size(); i++){
        // compare the address of the warrior
        if (army[i] == &warrior){
            // reduce the strength of the noble's army
            armyStrength -= warrior.getStrength();
            // set the warrior's hired status to false
            warrior.setHired(nullptr);
            // remove the warrior from the army
            for (size_t j = i; j < army.size()-1; j++){
                army[j] = army[j+1];
            }
            // remove the last element
            army.pop_back();
            return true;
        }
    }
    return false;
}
// Overload the << operator for Noble
ostream& operator<<(ostream& os, const Noble& rhs){
     os << rhs.name << " has an army of " << rhs.army.size();
     for (size_t i = 0; i < rhs.army.size(); i++){
          os << "\n     " << *rhs.army[i];
     }
     return os;
}
