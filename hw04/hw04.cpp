/*
     Name: Sean Lai Sheng Hong
     File Name:  hw04.cpp
     Purpose: Simulate fights between Noble using Warrior armies
    
*/

#include <iostream>
#include <vector>
#include <string>
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
               if (armyStrength == 0 && otherNoble.armyStrength == 0){
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
                    cout << name << " is dead and cannot fire " << warrior.getName() << endl;
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
                         ", you don't work for me any more! -- " << name << endl;
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


int main() {
	
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
	
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
	
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    art.hire(nimoy);
	
    cout << "==========\n\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n\n";
	
    art.fire(cheetah);
    cout << art << endl;

    lance.fire(nimoy);
    cout << lance << endl;
    cout << "==========\n\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";
	
}

ostream& operator<<(ostream& os, const Warrior& rhs){
     os << rhs.name << ": " << rhs.strength;
     return os;
}

ostream& operator<<(ostream& os, const Noble& rhs){
     os << rhs.name << " has an army of " << rhs.army.size();
     for (size_t i = 0; i < rhs.army.size(); i++){
          os << "\n     " << *rhs.army[i];
     }
     return os;
}