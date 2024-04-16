/*
  Author: Sean Lai Sheng Hong
  rec10_start.cpp
  Practicing Inheritance with Polymporphism
*/

#include <iostream>
#include <vector>
using namespace std;


// Base Instrument class
class Instrument {
    // output operator to show the instrument
friend ostream& operator<<(ostream& os, const Instrument& rhs);
public:
    // pure virtual make sound method
    virtual void makeSound() const = 0;
    // pure virtual display function to enable polymorphism
    virtual ostream& display(ostream& os) const = 0;

    virtual void play() = 0;
    // destructor for Instrument
    virtual ~Instrument() {}
};

class Percussion : public Instrument {
public:
    // default constructor
    using Instrument::Instrument;
    // Percussion makeSound
    void makeSound() const override;
    // Percussion info
};

class Drum : public Percussion {
public:
    using Percussion::Percussion;
    ostream& display(ostream& os) const override {
        return os << "Drum";
    }
    void play() override {
        cout << "Boom";
    }
};
class Cymbal : public Percussion {
public:
    using Percussion::Percussion;
    ostream& display(ostream& os) const override {
        return os << "Cymbal";
    }
    void play() override {
        cout << "Crash";
    }
    
}; 

class Strings: public Instrument {
public:
    // 
    Strings(int pitch);
    // Strings makeSound
    void makeSound() const override;
    // Strings display
    ostream& display(ostream& os) const override {
        os << pitch;
        return os;
    }
private:
    int pitch;
};

class Cello : public Strings {
public:
    using Strings::Strings;
    ostream& display(ostream& os) const override {
        os << "Cello: ";
        return Strings::display(os);
    }
    void play() override {
        cout << "Squawk";
    }

};
class Violin : public Strings {
public:
    using Strings::Strings;
    ostream& display(ostream& os) const override {
        os << "Violin: ";
        return Strings::display(os);
    }
    void play() override {
        cout << "Screech";
    }
};

class Brass : public Instrument {
public:
    Brass(int mouthpiece);
    // Brass makeSound
    void makeSound() const override;

    ostream& display(ostream& os) const override {
        os << mouthpiece;
        return os;
    }
    void play() override {
        cout << "Toot";
    }
private:
    int mouthpiece;
};

class Trombone : public Brass {
public:
    using Brass::Brass;
    ostream& display(ostream& os) const override {
        os << "Trombone: ";
        return Brass::display(os);
    }
    void play() override {
        cout << "Blat";
    }
};
class Trumpet : public Brass {
public:
    using Brass::Brass;
    ostream& display(ostream& os) const override {
         os << "Trumpet: ";
         return Brass::display(os);
    }
    void play() override {
        cout << "Toot";
    }
};

// 
// Musician class as provided to the students. Requires an Instrument class.
// 

class Musician {
public:
    Musician(const string& name) : instr(nullptr), name(name) {}

    // acceptInstr takes in an instrument for the Musician to later play.
    //  "loses" any instrument that it used to have.
    void acceptInstr(Instrument* instPtr) { instr = instPtr; }

    // giveBackInstr: gives the instrument that the Musicial was holding "back"
    Instrument* giveBackInstr() { 
        Instrument* result(instr); 
        instr = nullptr;
        return result;
    }

    // testPlay: testing out my instrument
    void testPlay() const {
        if (instr) instr->makeSound(); 
        else cerr << name << " has no instr\n";
    }

    // play: play the instrument

    //   Not making it const so that Instrument::play method does not
    //   need to be const. Allows the instrument to be modifed in the
    //   process of being played.
    void play() {
        if (instr) instr->play();
        // Don't do anything if we don't have an instrument.
    }
private:
    Instrument* instr;
    string name;
};


class MILL{
friend ostream& operator<<(ostream& os, const MILL& rhs);
public:
    // Default Constructor
    MILL();
    // add instrument to the MILL, returning true if successful
    bool receiveInstr(Instrument& instr);
    // play all the instruments
    void dailyTestPlay() const;
    // loan out an instrument if available
    Instrument* loanOut();
private:
    vector<Instrument*> instruments;
};


class Orch{

public:

    void addPlayer(Musician& player){
        players.push_back(&player);
    }
    void play() const {
        for(Musician* player : players){
            player->play();
        }
        cout << endl;
    }
private:
    vector<Musician*> players;
};


int main() {

    //
    // PART ONE
    //
    cout << "P A R T  O N E\n";

    cout << "Define some instruments ---------------------------------------\n";
    Drum drum;
    Cello cello(673);
    Cymbal cymbal;
    Trombone tbone(4);
    Trumpet trpt(12) ;
    Violin violin(567) ;
  
    cout << "Define the MILL -----------------------------------------------\n";
    MILL mill;
    cout << "The MILL before adding instruments:\n" << mill << "\n\n";

    cout << "Put the instruments into the MILL -----------------------------\n";
    mill.receiveInstr(trpt);
    mill.receiveInstr(violin);
    mill.receiveInstr(tbone);
    mill.receiveInstr(drum);
    mill.receiveInstr(cello);
    mill.receiveInstr(cymbal);
    cout << "\nThe MILL after adding some instruments:\n" << mill << "\n\n";
  
    cout << "Daily test ----------------------------------------------------\n"
	 << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    cout << "Define some Musicians------------------------------------------\n";
    Musician harpo("Harpo");
    Musician groucho("Groucho");
  	
    cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
    groucho.testPlay();	 // Groucho doesn't have an instrument yet.

    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();
    cout << endl;
  
    groucho.testPlay();	
    mill.receiveInstr(*groucho.giveBackInstr());
    harpo.acceptInstr(mill.loanOut());
    groucho.acceptInstr(mill.loanOut());
    groucho.testPlay();
    harpo.testPlay();

    cout << "\ndailyTestPlay()" << endl;
    mill.dailyTestPlay();

    cout << "\nThe MILL after giving out some instruments:\n";
    cout << mill << "\n\n";

    cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";
    mill.receiveInstr(*groucho.giveBackInstr());

    cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
    mill.receiveInstr(*harpo.giveBackInstr());
    cout << endl;

    cout << "dailyTestPlay()" << endl;
    mill.dailyTestPlay();
  
    cout << "\nThe MILL at the end of Part One:\n";
    cout << mill << endl;

    //
    // PART TWO
    //
    
    cout << "\nP A R T  T W O\n";
    
    Musician bob("Bob");
    Musician sue("Sue");
    Musician mary("Mary");
    Musician ralph("Ralph");
    Musician jody("Judy");
    Musician morgan("Morgan");

    Orch orch;

    // THE SCENARIO

    //Bob joins the orchestra without an instrument.
    orch.addPlayer(bob);

    //The orchestra performs
    cout << "orch performs\n";
    orch.play();
    
    //Sue gets an instrument from the MIL2 and joins the orchestra.
    sue.acceptInstr(mill.loanOut());
    orch.addPlayer(sue);

    //Ralph gets an instrument from the MIL2.
    ralph.acceptInstr(mill.loanOut());

    //Mary gets an instrument from the MIL2 and joins the orchestra.
    mary.acceptInstr(mill.loanOut());
    orch.addPlayer(mary);

    //Ralph returns his instrument to the MIL2.
    mill.receiveInstr(*ralph.giveBackInstr());

    //Jody gets an instrument from the MIL2 and joins the orchestra.
    jody.acceptInstr(mill.loanOut());
    orch.addPlayer(jody);

    // morgan gets an instrument from the MIL2
    morgan.acceptInstr(mill.loanOut());
    
    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Ralph joins the orchestra.
    orch.addPlayer(ralph);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();
	
    // bob gets an instrument from the MIL2
    bob.acceptInstr(mill.loanOut());

    // ralph gets an instrument from the MIL2
    ralph.acceptInstr(mill.loanOut());

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    //Morgan joins the orchestra.
    orch.addPlayer(morgan);

    //The orchestra performs.
    cout << "orch performs\n";
    orch.play();

    cout << endl << mill << endl;
}

// Instrument Implementation
void Instrument::makeSound() const{
    cout << "To make a sound...";
}

ostream& operator<<(ostream& os, const Instrument& rhs){
    return rhs.display(os);
}
// Percussion Implementation
void Percussion::makeSound() const {
    Instrument::makeSound();
    cout << "Hit me!" << endl;
}

// Strings Implementation
Strings::Strings(int pitch): Instrument(), pitch(pitch) {}

void Strings::makeSound() const {
    Instrument::makeSound();
    cout <<  "bow a string with pitch " << pitch << endl;
}

// Brass Implementation
Brass::Brass(int mouthpiece): Instrument(), mouthpiece(mouthpiece) {}

void Brass::makeSound() const {
    Instrument::makeSound();
    cout << " blow on a mouthpiece of size " << mouthpiece << endl;
}


// MILL Implementation
MILL::MILL(){
    instruments = {};
}

ostream& operator<<(ostream& os, const MILL& rhs){
    os << "The MILL has the following instruments:";
    if(rhs.instruments.size() == 0){
        os << " None";
    }else{
        bool anyInstruments = false;
        for (Instrument* instr : rhs.instruments){
            if(instr != nullptr){
                os << endl << *instr;
                anyInstruments = true;
            }
        }
        if(!anyInstruments){
            os << " None";
        }
    }
    return os;
}

Instrument* MILL::loanOut(){
    if(instruments.size() == 0){
        return nullptr;
    }else{
        Instrument* loaning;
        for(size_t i = 0; i < instruments.size(); ++i){
            if(instruments[i] != nullptr){
                loaning = instruments[i];
                instruments[i] = nullptr;
                break;
            }
        }
        return loaning;
    }
}

bool MILL::receiveInstr(Instrument& instr){
    if(instruments.size() == 0){
        instruments.push_back(&instr);
        instr.makeSound();
        return true;
    }else{
        // Check if there is an empty slot
        for(size_t i = 0; i < instruments.size(); ++i){
            if(instruments[i] == nullptr){
                instruments[i] = &instr;
                instr.makeSound();
                return true;
            }
        }
        // If there is no empty slot, add to the end
        instruments.push_back(&instr);
        instr.makeSound();
        return true;
    }
}

void MILL::dailyTestPlay() const {
    for (const Instrument* instr : instruments){
        if(instr != nullptr){
            instr->makeSound();
        }
    }
}