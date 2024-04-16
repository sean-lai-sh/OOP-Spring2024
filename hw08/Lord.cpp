
#include "Lord.h"
#include "Noble.h"
#include "Protectors.h"
#include<iostream>
#include<string>
#include<vector>

using namespace std;

namespace WarriorCraft{
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
            cout << servant.getName() << ", you don't work for me anymore ! -- " << getName() << endl;
            return true;
        }
        cout << getName() << " failed to fire " << servant.getName() << endl;
        return false;
    }

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
}
