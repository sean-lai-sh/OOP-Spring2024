/*
Author: Sean Lai Sheng Hong
file: Protectors.cpp
Purpose: Implementation for the Protectors class and its children
*/
#include "Protectors.h"
#include "Noble.h"
#include<iostream>
#include<string>

using namespace std;

namespace WarriorCraft{
        // Warrior Implementation
    // Constructor for Warrior
    Protectors::Protectors(const string& name, double strength): 
                name(name), strength(strength), lord(nullptr){}
    // Get the strength of the warrior
    double Protectors::getStrength() const{
        return strength;
    }
    // Get the name of the warrior
    const string& Protectors::getName() const{
        return name;
    }
    // Get the lord of the warrior
    Lord* Protectors::getLord() const{
        return lord;
    }

    // check name of the warrior
    bool Protectors::checkName(const string& name) const{
        return this->name == name;
    }
    // Reduce the strength of the warrior
    void Protectors::reduceStrength(double ratio){
        strength -= strength*ratio;
    }
    // Set the hired status of the warrior
    bool Protectors::isHired() const{
        return lord != nullptr;
    }
    // Set the hired status of the warrior
    void Protectors::setHired(Lord* master){
        this->lord = master;
    }
    // Runaway from the noble
    bool Protectors::runaway(){
        if (lord != nullptr){
            cout << name << " flees in terror, abandoning his lord, " 
            << lord->getName() << endl;
            lord->removeProtector(*this);
            lord = nullptr;
            return true;
        }
        return false;
    }

    // Overload the << operator for Protectors
    ostream& operator<<(ostream& os, const Protectors& rhs){
        os << rhs.name << " has strength " << rhs.strength;
        return os;
    }

    // Warriors Implementation
    void Warriors::battleCry() const{
        cout <<  getName() << " says: Take that in the name of my lord, " 
        << getLord()->getName() << endl;
    }

    // Archer Implementation
    // Archer battleCry
    void Archer::battleCry() const{
        cout << "TWANG! ";
        Warriors::battleCry();
    }

    // Swordsman Implementation
    // Swordsman battleCry
    void Swordsman::battleCry() const{
        cout << "CLANG! ";
        Warriors::battleCry();
    }

    // Wizard Implementation
    // Wizard battleCry
    void Wizard::battleCry() const{
        cout << "POOF!" << endl;
    }
}

