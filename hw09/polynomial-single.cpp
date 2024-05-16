/*
  testPolynomial.cpp
  Test code for the Polynomial class
 */

#include <iostream>
#include <vector>
using namespace std;

class Polynomial{
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs){
        // DEBUGGING IGNORE
        // cout << "OPERATOR IS CALLED";
        // cout << "lhs: " << lhs.maxPower << endl;
        // cout << "rhs: " << rhs.maxPower << endl;

        if(lhs.maxPower != rhs.maxPower){
            return false;
        }

        Node* lhsCurrent = lhs.head;
        Node* rhsCurrent = rhs.head;
        while(lhsCurrent != nullptr){
            if(lhsCurrent->data != rhsCurrent->data){
                return false;
            }
            lhsCurrent = lhsCurrent->next;
            rhsCurrent = rhsCurrent->next;
        }
        return true;
    }
    friend bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
        return !(lhs == rhs);
    }
    friend ostream& operator<<(ostream& os, const Polynomial& poly);
    friend Polynomial operator+(const Polynomial& lhs, Polynomial& rhs){
        Polynomial temp(lhs);
        temp += rhs;
        return temp;
    }
    struct Node{
        int data = 0;
        Node* next = nullptr;
    };
public:
    Polynomial(vector<int> coefficentVec = {}){
        // if we have no coefficent its 0!
        if(coefficentVec.size()  == 0){
            head = new Node();
            maxPower = 0;
        }else{
            head = new Node();
            Node* current = head;
            for(int i = 0; i < coefficentVec.size(); i++){
                current->data = coefficentVec[i];
                if(i != coefficentVec.size() - 1){
                    current->next = new Node();
                    current = current->next;
                }
            }
            maxPower = coefficentVec.size() - 1;
            cleanup();
        }
    }


    bool printerHelper(Node* current, int power, ostream& os)const {
        if(current == nullptr){
            return false;
        }
        if(current->data == 0 && current->next == nullptr){
            os << "0";
            return true;
        }
        if(current->data == 0){
            return printerHelper(current->next, power - 1,os);
        }
        if(power == 0){
            os << current->data;
        }else{
            if(current->data != 1 && current->data != -1){
                os << current->data;
            }else if(current->data == -1){
                os << "-";
            }
            os << "x";
            if(power != 1){
                os << "^" << power;
            }
        }
        if(current->next != nullptr){
            os << " + ";
        }
        return printerHelper(current->next, power - 1, os );
    }


    Polynomial& operator+=(const Polynomial& rhs){
        Node* tailPtr = nullptr;
        // Create temps to iterate through the linked list
        Node* lhsCurrent = this->head;
        Node* rhsCurrent = rhs.head;
        // cout << "Before addition\n" << *this << "\n" << rhs << "\n";
        // Iterate through either difference in max power
        int powDifferential = this->maxPower - rhs.maxPower;
        if (powDifferential < 0){
            tailPtr = this->head;
            this->maxPower = rhs.maxPower;
            Node* endIsh = this->head;
            Node* whereHead = this->head;
            for(int i = 0; i < -powDifferential; ++i){
                // Create a new node to add to the front
                if(this->head == nullptr){
                    this->head = addToBack(this->head, rhsCurrent->data);
                }else if(this->head != nullptr && i == 0){
                    this->head = new Node{rhsCurrent->data, this->head};
                    whereHead = this->head;
                    endIsh = this->head;
                }else{
                    endIsh->next = new Node{rhsCurrent->data, endIsh->next};
                    endIsh = endIsh->next;
                }
                rhsCurrent = rhsCurrent->next;
            }
            this->head = whereHead;
            
        }else if(powDifferential > 0){
            // Below works for powDifferential > 0
            for(int i = 0; i < powDifferential; ++i){
                // move till we are at the same power
                lhsCurrent = lhsCurrent->next;
                tailPtr = lhsCurrent;
            }
        }
        // Add the rest of the linked list
        while(lhsCurrent != nullptr || rhsCurrent != nullptr){
            // Add to the back of tailPtr and increment to the next
            int coef = lhsCurrent->data + rhsCurrent->data;
            // // prevent adding 0 as a leading coefficent
            // if(this->head == nullptr && coef != 0){
            //     this->head = addToBack(tailPtr, coef);
            //     tailPtr = this->head;
            //     this->maxPower++;
            // }else if(this->head != nullptr){
            //     // add to the back
            //     lhsCurrent->data = coef;
            // }
            lhsCurrent->data = coef;
            lhsCurrent = lhsCurrent->next;
            rhsCurrent = rhsCurrent->next;
        }
        cleanup();
        return *this;
    }

    
    // Copy constructor
    Polynomial(const Polynomial& rhs){
        Node* newPoly = nullptr;
        Node* current = rhs.head;

        while(current != nullptr){
            // If we have no head, create one
            if(newPoly == nullptr){
                newPoly = addToBack(newPoly, current->data);
            // If we have a head, add to the back
            }else{
                addToBack(newPoly, current->data);
            }
            current = current->next;
        }
        this->head = newPoly;
        this->maxPower = rhs.maxPower;
    }

    int evaluate(int x) const{
        int sum = 0;
        Node* current = head;
        int power = maxPower;
        while(current != nullptr){
            sum += current->data * myPow(x, power);
            power--;
            current = current->next;
        }
        return sum;
    }

    Polynomial& operator=(const Polynomial& rhs){
        if(this == &rhs){
            return *this;
        }
        cleanup();
        Node* newPoly = nullptr;
        Node* current = rhs.head;

        while(current != nullptr){
            // If we have no head, create one
            if(newPoly == nullptr){
                newPoly = addToBack(newPoly, current->data);
            // If we have a head, add to the back
            }else{
                addToBack(newPoly, current->data);
            }
            current = current->next;
        }
        this->head = newPoly;
        this->maxPower = rhs.maxPower;
        return *this;
    }
private:
    Node* addToBack(Node* current, int data){
        if(current == nullptr){
            return new Node{data, nullptr};
        }
        current->next = addToBack(current->next, data);
        return current;
    }
    void cleanup(){
        Node* prev = nullptr;
        Node* current = this->head;

        while (current != nullptr) {
            if (current->data == 0) {
                // Remove zero nodes, 
                // except for the very last one if it's the only node.
                if (current == this->head && current->next == nullptr) {
                    break;
                }
                Node* toDelete = current;
                if (prev) {
                    prev->next = current->next;
                } else {
                    this->head = current->next;
                }
                current = current->next;
                delete toDelete;
                maxPower--;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }

    int myPow(int base, int power) const {
        int sum = 1;
        for(int i = 0; i < power; i++){
            sum *= base;
        }
        return sum;
    }
    Polynomial::Node* head;
    int maxPower;
};


void doNothing(Polynomial temp) {}

int main() {
        
    //test constructor
    Polynomial p0;                       // 0
    Polynomial p1({17});                 // 17
    Polynomial p2({1, 2});               // x + 2
    Polynomial p3({-1, 5});              // -x + 5
    Polynomial p4({5, 4, 3, 2, 1});      // 5x^4 + 4x^3 + 3x^2 + 2x + 1
    Polynomial has_a_zero({4, 0, 1, 7}); // 4x^3 + x + 7

    // Polynomial temp(p4);
    // cout << "temp: " << temp << endl;
        
    cout << "displaying polynomials\n"
         << "p0: " << p0 << endl
         << "p1: " << p1 << endl
         << "p2: " << p2 << endl
         << "p3: " << p3 << endl
         << "p4: " << p4 << endl
         << "has_a_zero: " << has_a_zero << endl;

    Polynomial temp;
    temp = p2 + p3;
    cout << "temp: " << temp << endl;
    
    cout << "p2 + p3: " << (p2+p3) << endl
         << "p2 + p4: " << (p2+p4) << endl
         << "p4 + p2: " << (p4+p2) << endl;
    
    //test copy constructor - the statement below uses the copy constructor
    //to initialize poly3 with the same values as poly4
    Polynomial p5(p4);
    cout << "p5: " << p5 << endl;
    p5 += p3;
    cout << "Polynomial p5(p4);\n"
         << "p5 += p3;\n";

    cout << "p4: " << p4 << endl;  
    cout << "p5: " << p5 << endl;  

    
    cout << "Calling doNothing(p5)\n";
    doNothing(p5);
    cout << "p5: " << p5 << endl;

    //tests the assignment operator
    
    Polynomial p6;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;  // Causes bools true and false to be printed that way.
    cout << "(p4 == p6) is " << (p4 == p6) << endl;
    p6 = p4;
    cout << "p6: " << p6 << endl;
    cout << boolalpha;
    cout << "(p4 == p6) is " << (p4 == p6) << endl;   
    //test the evaluaton
    int x = 5;
    cout << "Evaluating p1 at " << x << " yields: " << p1.evaluate(5) << endl;
    cout << "Evaluating p2 at " << x << " yields: " << p2.evaluate(5) << endl;
        
    Polynomial p7({3, 2, 1});           // 3x^2 + 2x + 1
    cout << "p7: " << p7 << endl;
    cout << "Evaluating p7 at " << x << " yields: " << p7.evaluate(5) << endl;

    cout << boolalpha;
    cout << "(p1 == p2) is " << (p1 == p2) << endl;
    cout << "(p1 != p2) is " << (p1 != p2) << endl;

    Polynomial p8({ 1, 1 });
    Polynomial p9({ -1, 1 });
    Polynomial p10({ 0, 0, 2 });
    Polynomial p11({ 0, 0, -2 });
    //p8 + p9 tests if += does the cleanup()
    //p10 tests if constructor does the cleanup()

    cout << "p8: " << p8 << endl
         << "p9: " << p9 << endl
         << "p10: " << p10 << endl;

    cout << "p8 + p9: " << (p8 + p9) << endl;

    cout << "((p8 + p9) == p10) is " << ((p8 + p9) == p10) << endl;

}

ostream& operator<<(ostream& os, const Polynomial& poly){
    poly.printerHelper(poly.head, poly.maxPower, os);
    return os;
}