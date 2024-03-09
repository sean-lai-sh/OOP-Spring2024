// Task 1
// Who are you? What is this program called?
// Author: Sean Lai
// File Name: rec04.cpp
// Purpose: Learning about pointers and references
// I have stopped using cerr in your started code because CLion makes
// a mess with it.

#include <iostream>   // needed for task 2
#include <vector>     // needed for task 27
using namespace std;  // needed for task 2

// Task 16 Complex definition
struct Complex {
   double real;
   double img;
};

// Task 17 PlainOldClass definition
class PlainOldClass {
public:
   PlainOldClass() : x(-72) {}
   int getX() const { return x; }
   void setX( int val )  { x = val; }
private:
   int x;
};


// Task 18 PlainOldClass2 definition
class PlainOldClassV2 {  
public:
   PlainOldClassV2() : x(-72) {}
   int getX() const { return x; }
   void setX( int x )  { this->x = x; } // HMMMM???
private:
   int x;
};

// Task 28 Colour definition
class Colour {  
public:       
    Colour(const string& name, unsigned r, unsigned g, unsigned b)       
        : name(name), r(r), g(g), b(b) {}       
    void display() const { 
        cout << name << " (RBG: " << r << "," << g<< "," << b << ")"; 
    }   
private:       
    string name;      // what we call this colour       
    unsigned r, g, b; // red/green/blue values for displaying  
};  

// Task 29 SpeakerSystem definition

// Task 29 Amplifier definition
class SpeakerSystem {
   public:
   void vibrateSpeakerCones(unsigned signal) const {

      cout << "Playing: " << signal << "Hz sound..." << endl;
      cout << "Buzz, buzzy, buzzer, bzap!!!\n";
   }
};

class Amplifier {
public:
  void attachSpeakers(const SpeakerSystem& spkrs)
   {
      if(attachedSpeakers) {
         cout << "already have speakers attached!\n";
      } else {
         attachedSpeakers = &spkrs;
      }
   }
  
   void detachSpeakers() { // should there be an "error" message if not attached?
        if(attachedSpeakers){
            attachedSpeakers = nullptr;
        }else{
            cout << "No speakers attached\n";
        }
   } 
  
   void playMusic( ) const {
      if (attachedSpeakers) {
         attachedSpeakers -> vibrateSpeakerCones(440); 
      } else {
         cout << "No speakers attached\n";
      } 
   }
private:
   const SpeakerSystem* attachedSpeakers = nullptr;
};

// Task 30 Person Definition
class Person {  
public:       
    Person(const string& name) : name(name) {}
    void movesInWith(Person& newRoomate) {
        if (&newRoomate == this) {
            cerr << "You can't move in with yourself" << endl;
            return;
        }else if (roomie != nullptr) {
            cerr << "You already have a roomie" << endl;
            return;
        }else if (newRoomate.roomie != nullptr) {
            cerr << "Roomate already has a roomie" << endl;
            return;
        }
        roomie = &newRoomate;        // now I have a new roomie            
        newRoomate.roomie = this;    // and now they do too       
    }       
    const string& getName() const { return name; }
    // Don't need to use getName() below, just there for you to use in debugging.
    const string& getRoomiesName() const { return roomie->getName(); }  
private:
    Person* roomie = nullptr;       
    string name;  
};           

int main() {
    cout << "Task 1\n";

    // Task 2
    cout << "Task 2\n";
    // Add code here
    int x;  
    x = 10;  
    cout << "x = " << x << endl;
    /// Prints x = 10
    // Task 3 
    cout << "Task 3\n";
    // Using the debugger, set a breakpoint in main and run to
    // it. Observe the value of x.
    // [No new code]
    // Initializes to undefined value for x initially 
    // (But VSc sets it as 0 for me)
    // thn sets it to 10
    // Task 4
    cout << "Task 4\n";
    // Using the debugger, step forward observing the value of x
    // [No new code]
    // x = 10 occurs after the line x = 10
    // Task 5
    cout << "Task 5\n";
    // Watch window. Xcode equivalent? Gdb equivalent?
    // Activity: see x's value
    // [No new code]
    // X = 10
    // Task 6
    cout << "Task 6\n";
    // Watch window to see the address of x
    // [No new code]

    // Task 7
    cout << "Task 7\n";
    // Watch window to see the value stored at the address of x
    // [No new code]
    
    // Task 8
    cout << "Task 8\n";
    // Add code. here
    int* p;  
    p = &x;  
    cout << "p = " << p << endl;
    
    // Task 9
    cout << "Task 9\n";
    // Using the value you observe in &x, write a line of code to
    // directly assign that value to p. E.g. p = 0x0012fed4;
    // What happens? Should have a compiler error.
    // p = 0x0012fed4; // using the value from my Watch window
    // x = p; // Error: cannot convert int* to int
    // p has undefined int value
    // Task 10
    cout << "Task 10\n";
    // Run earlier print statement for "p = ". Observe the watch
    // window.
    // Then add code here:
    cout << "p = " << p << endl;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p contains " << *p << endl;
    // Task 11
    cout << "Task 11\n";
    // Add code here
    *p = -2763;  
    cout << "p points to where " << *p << " is stored\n";  
    cout << "*p now contains " << *p << endl;  
    cout << "x now contains " << x << endl;
    
    // Task 12
    cout << "Task 12\n";
    // Add code
    int y(13);      
    cout << "y contains " << y << endl;      
    p = &y;      
    cout << "p now points to where " << *p << " is stored\n";      
    cout << "*p now contains " << *p << endl;      
    *p = 980;      
    cout << "p points to where " << *p << " is stored\n";      
    cout << "*p now contains " << *p << endl;      
    cout << "y now contains " << y << endl;
    
    // Task 13
    cout << "Task 13\n";
    // Add code here
    int* q;    // THis compiles pointing to same address as p  
    q = p;      
    cout << "q points to where " << *q << " is stored\n";      
    cout << "*q contains " << *q << endl;
    
    // Task 14
    cout << "Task 14\n";
    // Add code here
    double d(33.44);      
    double* pD(&d);      
    *pD = *p;      
    *pD = 73.2343;      
    *p  = *pD;  // my initial answer was wrong, this is valid
    *q  = *p;      
    // pD  = p; // Compile Error
    // p   = pD; // Compile Error
    
    // Task 15
    cout << "Task 15!!!\n"; // Yes, this is a VERY IMPORTANT task!
    // Const and pointers.
    // Add code here
    int joe = 24;  
    const int sal = 19;    
    int*  pI;  
    pI = &joe;  
    *pI = 234;  
    // pI = &sal; // Cannot go from int* to const int* 
    *pI = 7623;   // Presents unintended behavior but it compiles

    const int* pcI;
    pcI = &joe;  
    // *pcI = 234;  
    pcI = &sal;  
    // *pcI = 7623;    

    // int* const cpI;
    int* const cpI(&joe);
    // int* const cpI(&sal); // Already assigned
    // cpI = &joe;  //Already assigned
    *cpI = 234;  
    //  cpI = &sal;  
    *cpI = 7623;    

    // const int* const cpcI; // cannot assign to nothing
    const int* const cpcI(&joe);
    //const int* const cpcI(&sal);
    // cpcI = &joe;  // *cpcI = 234;  
    //  cpcI = &sal;  // cannot dereference
    // *cpcI = 7623; // cannot change value
    
    // Task 16
    cout << "Task 16\n";
    // Pointers to user-defined types.  Add the type for struct Complex above.
    // Add code here
    Complex c = {11.23,45.67};      
    Complex* pC(&c);
    cout << "real: " << pC->real << "\nimaginary: " << pC->img << endl;
    // Task 17
    cout << "Task 17\n";
    // Add code here
    // What is this code doing?
    PlainOldClass poc;
    PlainOldClass* ppoc( &poc ); // This is a pointer to a PlainOldClass
    cout << ppoc->getX() << endl; // This is the same as poc.getX()
    ppoc->setX( 2837 ); // This is the same as poc.setX( 2837 )
    cout << ppoc->getX() << endl; // This is the same as poc.getX()

    // Task 18
    cout << "Task 18\n";
    // Test the changes to PlainOldClassV2
    PlainOldClassV2 tac;
    PlainOldClassV2* ptac( &tac ); // This is a pointer to a PlainOldClassV2
    cout << ptac->getX() << endl; // This is the same as tac.getX()
    ptac->setX( 2837 ); // This is the same as tac.setX( 2837 )
    cout << ptac->getX() << endl; // This is the same as tac.getX()
    
    // Task 19
    cout << "Task 19\n";
    // creating and modifying an item on the heap. Use the debugger to
    // observe.
    // Add code here
    int* pDyn = new int(3); // p points to an int initialized to 3 on the heap      
    *pDyn = 17;

    // Task 20
    cout << "Task 20\n";
    // What happens to pDyn in the following? With most compilers it
    // is unchanged.  Visual Studio actually changes it. (I should
    // check if that is just in debug mode.)
    // Add code here
    cout << pDyn << endl;  
    delete pDyn;  // prevent memory leak
    cout << pDyn << endl;

    // DO NOT DO THIS.  This is very bad.
    // int* pDyn2 = pDyn; // p points to an int initialized to 17 on the heap
    // cout << "The 17 might STILL be stored at address " << pDyn2<< " even though we deleted pDyn\n";  
    // cout << "But can we dereference pDyn?  We can try.  This might crash... " << *pDyn2 << ".  Still here?\n";
    // Task 21
    cout << "Task 21\n";
    // Add code here
    pDyn = nullptr; // good practice to spot unintentional referencing
    double* pDouble = nullptr; // typical initialization of a pointer
    
    // Task 22
    cout << "Task 22\n";
    // Add code here
    // cout << "Can we dereference pDouble?  " << *pDouble << endl; // No, this will crash
    // cout << "Can we dereference pDyn?  " << *pDyn << endl; // No, this will crash
    
    // Task 23
    cout << "Task 23\n";
    // Question. Can <code>this</code> be nullptr?
    // NO

    // Task 24
    cout << "Task 24\n";
    // Add code here
    double* pTest = new double(12);      
    delete pTest;      
    pTest = nullptr;      
    delete pTest; // safe
    
    

    // Task 25
    cout << "Task 25\n";
    // Add code here
    short* pShrt = new short(5);      
    delete pShrt;      
    // delete pShrt; // double delete crashes the program    
    

    // Task 26
    cout << "Task 26\n";
    // Add code here
    long jumper = 12238743;      
    // delete jumper;
    long* ptrTolong = &jumper; 
    // delete works on heap allocated mem only       
    // delete ptrTolong;  // What happens here?  Deletes as intended
    

    // Task 27
    cout << "Task 27\n";
    // Add code here
    Complex cmplx;      
    //delete cmplx;      // What happens here? needs mem addres
    vector<Complex*> complV; // can hold pointers to Complex objects
    Complex* tmpPCmplx;      // space for a Complex pointer
    for (size_t ndx = 0; ndx < 3; ++ndx) {
    tmpPCmplx = new Complex; // create a new Complex object on the heap
    tmpPCmplx->real = ndx;   // set real and img to be the
    tmpPCmplx->img  = ndx;   // value of the current ndx
    complV.push_back(tmpPCmplx); // store the ADDRESS of the object in a vector or pointer to Complex
    }      
    // display the objects using the pointers stored in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {         
        cout << complV[ ndx ]->real << endl;         
        cout << complV[ ndx ]->img  << endl;      
    }      
    // release the heap space pointed at by the pointers in the vector      
    for (size_t ndx = 0; ndx < 3; ++ndx) {         
        delete complV[ndx];
        complV[ndx] = nullptr;
    }      
    // clear the vector      
    complV.clear();

    // Task 28 Use the Colour class
    cout << "Task 28\n";
    // Add Colour class above main
    // Add code here
    vector<Colour*> colours;         
    string inputName;       
    unsigned inputR, inputG, inputB;

    // fill vector with Colours from the file       
    // this could be from an actual file but here we are using the keyboard instead of a file
    // (so we don't have to create an actual file)
    // Do you remember the keystroke combination to indicate "end of file" at the keyboard?
    // somehow the while's test has to fail - from keyboard input
    while (cin >> inputName >> inputR >> inputG >> inputB) {
        colours.push_back(new Colour(inputName, inputR, inputG, inputB));       
    }         

    // display all the Colours in the vector:       
    for (size_t ndx = 0; ndx < colours.size(); ++ndx) {            
        colours[ndx]->display();  
        delete colours[ndx];
        colours[ndx] = nullptr;          
        cout << endl;       
    }
    colours.clear();
    // Task 29 Use SpeakerSystem and Amplifier classes
    cout << "Task 29\n";
    // Add SpeakerSystem and Amplifier classes above main
    // Add code here
    SpeakerSystem spkrs;
    Amplifier amp;
    amp.attachSpeakers(spkrs);
    amp.playMusic();
    amp.detachSpeakers();
    amp.playMusic();


    // Task 30 Use the Person class
    cout << "Task 30\n";
    // Add Person class above main
    // Add code here
    Person joeBob("Joe Bob"), billyJane("Billy Jane");         

    // now model these two becoming roommates       
    joeBob.movesInWith(billyJane);         

    // did this work out?       
    cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
    cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;

    Person test("Test");
    test.movesInWith(billyJane); // SHOULD GIVE ERROR     
}
