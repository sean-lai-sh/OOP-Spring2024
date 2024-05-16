/*
AUthor: Sean Lai Sheng Hong
file: Noble.cpp
Purpose: Implementation for the Noble class and its children

*/
#include "Noble.h"
#include "Protectors.h"
#include <iostream>
#include <string>


using namespace std;

namespace WarriorCraft{
    // Noble Implementation
    Noble::Noble(const string& name, double strength): 
            name(name), strength(strength){}

    void Noble::battle(Noble& otherNoble){
        cout << name << " battles " << otherNoble.getName() << endl;
        // check for both dead and print the message
        if (getStrength() == -1 && otherNoble.getStrength() == -1){
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
        return;
        }
        // if one is dead
        if (getStrength() == -1){
        // loser battle call
        otherNoble.battleCall();
        cout << "He's dead " << otherNoble.name << endl;
        }
        // if the other is dead
        else if (otherNoble.getStrength() == -1){
        // winner battle call
        this->battleCall();
        cout << "He's dead " << name << endl;
        
        }
        else if (this->getStrength() > otherNoble.getStrength()){
            // call the battle cry
            this->battleCall();
            otherNoble.battleCall();
            // print the result of the battle
            cout << name << " defeats " << otherNoble.getName() << endl;
            // adjust the strength of the nobles
            this->adjustStrength(otherNoble.getStrength());
            otherNoble.adjustStrength(-1);
        }
        else if (this->getStrength() < otherNoble.getStrength()){
            // call the battle cry
            this->battleCall();
            otherNoble.battleCall();
            // print the result of the battle
            cout << otherNoble.getName() << " defeats " << name << endl;
            // adjust the strength of the nobles
            otherNoble.adjustStrength(this->getStrength());
            this->adjustStrength(-1);
        }
        else{
            // if both have the same strength
            cout << "Mutual Annihilation: " 
                    << name << " and " << otherNoble.name 
                    << " die at each other's hands" << endl;
            this->adjustStrength(-1);
            otherNoble.adjustStrength(-1);
        }
    }
    // Get the name of the noble
    const string& Noble::getName() const{
        return name;
    }
    // Set the strength of the noble
    void Noble::setStrength(double newStrength = -1){
        strength = newStrength;
    }
    // Get the strength of the noble
    double Noble::getStrength() const{
        return strength;
    }

    // Overload the << operator for Noble
    ostream& operator<<(ostream& os, const Noble& rhs){
        rhs.display(os);
        return os;
    }
    //Lord Implementation
    bool Lord::hires(Protectors& servant){
        // check if the noble is dead
        if (this->getStrength() == -1){
            cout << getName() << " failed to hire " 
            << servant.getName() << endl;
            return false;
        }
        // Check if the servant is already hired
        if (servant.isHired()){
            cout << getName() << " failed to hire " 
            << servant.getName() << endl;
            return false;
        }
        // add the servant to the army and increase the strength of the noble
        army.push_back(&servant);
        double newStrength = getStrength() + servant.getStrength();
        setStrength(newStrength);
        servant.setHired(this);
        //cout << name << " hires " << servant.name << endl;  
        return true;
    }
    bool Lord::fires(Protectors& servant){
        // check if the noble is dead
        if (this->getStrength() == -1){
                cout << getName() << 
                " is dead and cannot fire "
                    << servant.getName() << endl;
                return false;
        }
        // Check if the servant is in the army and remove it
        if(removeProtector(servant)){
            cout << servant.getName() << 
            ", you don't work for me anymore ! -- " 
            << getName() << endl;
            return true;
        }
        cout << getName() << " failed to fire " << servant.getName() << endl;
        return false;
    }

    // Lord constructor
    Lord::Lord(const string& name): Noble(name,0), army(){}


    bool Lord::removeProtector(Protectors& protector){
        for (size_t i = 0; i < army.size(); i++){
            // compare the address of the protector
            if (army[i] == &protector){
                // reduce the strength of the noble's army
                double newStrength = getStrength() - protector.getStrength();
                // set the new strength of the noble
                setStrength(newStrength);
                // set the protector's hired status to false
                protector.setHired(nullptr);
                // remove the protector from the army
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
    void Lord::battleCall() const{
        for (Protectors* protector : army){
            protector->battleCry();
        }
    }
    void Lord::display(ostream& os) const{
        os << getName() << " has an army of " << army.size();
        for (Protectors* protector : army){
            os << endl <<  "\t"<< *protector;
        }
    }

    void Lord::adjustStrength(double otherStrength){
        if(otherStrength == -1){
        setStrength();
        for (Protectors* protector : army){
            protector->reduceStrength(1);
        }
        }else{
        // get ratio of the strength
        double ratio = otherStrength/getStrength();
        // reduce the strength of the noble
        setStrength(getStrength() - getStrength()*ratio);
        for (Protectors* protector : army){
            protector->reduceStrength(ratio);
        }
        }
    }
    // PersonWithStrengthToFight Implementation
    PersonWithStrengthToFight::PersonWithStrengthToFight(
        const string& name, double strength): Noble(name, strength){}
    void PersonWithStrengthToFight::battleCall() const{
        cout << "Ugh!" << endl;
    }
    void PersonWithStrengthToFight::display(ostream& os) const{
        if(getStrength() == -1){
        os <<  getName() << " has strength: " << 0;
        }
        else{
        os <<  getName() << " has strength: " << getStrength();
        }
    }
    void PersonWithStrengthToFight::adjustStrength(double otherStrength){
        if(otherStrength == -1){
        setStrength();
        return;
        }
        // get ratio of the strength
        double ratio = otherStrength/getStrength();
        // reduce the strength of the noble
        setStrength(getStrength() - getStrength()*ratio);
    }
}