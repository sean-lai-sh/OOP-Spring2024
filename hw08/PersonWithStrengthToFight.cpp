#include "Noble.h"
#include "PersonWithStrengthToFight.h"
#include<iostream>
#include<string>

using namespace std;

namespace WarriorCraft{
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