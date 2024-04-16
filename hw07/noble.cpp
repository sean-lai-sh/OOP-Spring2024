/*
Author: Sean Lai Sheng Hong
Filename: noble.h
Purpose: Definitions for the Noble class in namespace WarriorCraft
*/

#include "noble.h"
#include "warrior.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace WarriorCraft{
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

}