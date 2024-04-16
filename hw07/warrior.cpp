/*
Author: Sean Lai Sheng Hong
Filename: warrior.cpp
Purpose: Implementations for the Warrior class in namespace WarriorCraft
*/
#include "noble.h"
#include "warrior.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace WarriorCraft{
    // Warrior Implementation
    // Constructor for Warrior
    Warrior::Warrior(const string& name, double strength): 
                name(name), strength(strength), master(nullptr){}
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
}