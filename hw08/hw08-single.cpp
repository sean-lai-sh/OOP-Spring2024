/*
  CS2124 hw08-test.cpp
  -jbs
 */

#include <string>
#include <vector>
#include <iostream>
#include <cassert>
using namespace std;

class Protectors;

class Noble{
    friend ostream& operator<<(ostream& os, const Noble& rhs);
    public:
        Noble(const string& name, double strength);
        // Battle another Noble
        void battle(Noble& otherNoble);
        // BattleCall Display
        virtual void battleCall() const = 0;
        // Enabling polynon-member display
        virtual void display(ostream& os) const = 0;
        virtual void adjustStrength(double otherStrength) = 0;
        const string& getName() const;
    protected:
        void setStrength(double newStrength);
        double getStrength() const;
    private:
      string name;
      double strength;
};

class PersonWithStrengthToFight : public Noble{
    public:
        PersonWithStrengthToFight(const string& name, double strength) 
              : Noble(name,strength) {}
        void battleCall() const override;
        void display(ostream& os) const override;
        void adjustStrength(double otherStrength) override;
};

class Lord : public Noble{
    public:
        Lord(const string& name);
        bool hires(Protectors& servant);
        bool fires(Protectors& servant);
        void battleCall() const override;
        void display(ostream& os) const override;
        void adjustStrength(double otherStrength) override;
        // remove a warrior from the army
        bool removeProtector(Protectors& protector);
    private:
        vector<Protectors*> army;
};

class Protectors{
    friend ostream& operator<<(ostream& os, const Protectors& rhs);
    public:
        Protectors(const string& name, double strength);
        // Get the strength of the warrior
        double getStrength() const;
        // Get the name of the warrior
        const string& getName() const;
        // Check name of the warrior
        bool checkName(const std::string& name) const;
        // Reduce the strength of the warrior
        void reduceStrength(double ratio);
        // Set the who Hired the warrior
        void setHired(Lord* lord);
        // Check if the warrior is hired
        bool isHired() const;
        // Runaway from the noble
        bool runaway();
        // Enable poly non-member display, print the protector details
        virtual void battleCry() const = 0;
        
    protected:
        Lord* getLord() const;
    private:
        string name;
        double strength;
        Lord* lord;
};

class Warriors : public Protectors{
    public:
        using Protectors::Protectors;
        void battleCry() const override;
};
class Archer : public Warriors{
    public:
        using Warriors::Warriors;
        void battleCry() const override;
};

class Swordsman : public Warriors{
    public:
        using Warriors::Warriors;
        void battleCry() const override;
};

class Wizard : public Protectors{
    public:
        using Protectors::Protectors;
        void battleCry() const override;
};
//
// Test Code
//
int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250); 	
    Lord janet("Janet");	
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);	
    janet.hires(stout);	
    janet.hires(samantha);     // fails because samantha works for sam.
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);	
    cout << "\n==========\nNobles: \n"
	 << sam << endl
	 << randy << endl
	 << janet << endl
	 << barclay << endl
	 << joe << endl
	 << "\n==========\n";
    joe.battle(randy);	            // joe has no army and dies.
    joe.battle(sam);	            // joe is dead
    janet.battle(barclay);          // barclay wins
    Archer pethora("Pethora", 50);	
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);          // janet is dead, so can't hire
    sam.hires(thora);              // sam brings in reinforcements
    sam.hires(pethora);
    sam.hires(merlin);
    janet.battle(barclay);	   // Silly janet
    sam.battle(barclay);           // Go Sam!
    samantha.runaway();            // Samantha has had enough
    sam.fires(thora);              // These layoffs! Sam fires thora.
    joe.battle(barclay);           // They're both dead already

    cout << "\n==========\nNobles: \n"
	 << sam << endl
	 << randy << endl
	 << janet << endl
	 << barclay << endl
	 << joe << endl
	 << "==========\n";
} // main

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
      otherNoble.battleCall();
      cout << "He's dead " << otherNoble.name << endl;
    }
    // if the other is dead
    else if (otherNoble.getStrength() == -1){
      this->battleCall();
      cout << "He's dead " << name << endl;
      // debugging only
    }
    else if (this->getStrength() > otherNoble.getStrength()){
      this->battleCall();
      otherNoble.battleCall();
      cout << name << " defeats " << otherNoble.getName() << endl;
      this->adjustStrength(otherNoble.getStrength());
      otherNoble.adjustStrength(-1);

    }
    else if (this->getStrength() < otherNoble.getStrength()){
      this->battleCall();
      otherNoble.battleCall();
      cout << otherNoble.getName() << " defeats " << name << endl;
      otherNoble.adjustStrength(this->getStrength());
      this->adjustStrength(-1);
    }
    else{

      cout << "Mutual Annihilation: " 
            << name << " and " << otherNoble.name 
            << " die at each other's hands" << endl;
      this->adjustStrength(-1);
      otherNoble.adjustStrength(-1);
    }
}
const string& Noble::getName() const{
    return name;
}
void Noble::setStrength(double newStrength = -1){
    strength = newStrength;
}
double Noble::getStrength() const{
    return strength;
}

// Overload the << operator for Noble
ostream& operator<<(ostream& os, const Noble& rhs){
    rhs.display(os);
    return os;
}

// PersonWithStrengthToFight Implementation
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
void Archer::battleCry() const{
    cout << "TWANG! ";
    Warriors::battleCry();
}

// Swordsman Implementation
void Swordsman::battleCry() const{
    cout << "CLANG! ";
    Warriors::battleCry();
}

// Wizard Implementation
void Wizard::battleCry() const{
    cout << "POOF!" << endl;
}

