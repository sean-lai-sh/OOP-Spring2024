/*
Author: Sean Lai Sheng Hong
File: polynomial.cpp
Purpose: Implement the Polynomial class, practicing ll, cc, sc, and oo
*/
#include "Polynomial.h"
#include<iostream>
#include<vector>
using namespace std;





Polynomial::Node* Polynomial::addToBack(Polynomial::Node* current, int data){
    if(current == nullptr){
        return new Polynomial::Node{data, nullptr};
    }
    current->next = addToBack(current->next, data);
    return current;
}

int Polynomial::evaluate(int x) const{
    // Horner's Method
    int sum = 0;
    Node* current = head;
    while(current != nullptr){
        sum = sum * x + current->data;
        current = current->next;
    }
    return sum;
}

Polynomial::Polynomial(const Polynomial& rhs){
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

Polynomial& Polynomial::operator+=(const Polynomial& rhs){
    // Create temps to iterate through the linked list
    Node* lhsCurrent = this->head;
    Node* rhsCurrent = rhs.head;
    // cout << "Before addition\n" << *this << "\n" << rhs << "\n";
    // Iterate through either difference in max power
    int powDifferential = this->maxPower - rhs.maxPower;
    if (powDifferential < 0){
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
                // add front before the start of shorter list
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
        }
    }
    // Add the rest of the linked list
    while(lhsCurrent != nullptr || rhsCurrent != nullptr){
        // Add to the back of tailPtr and increment to the next
        int coef = lhsCurrent->data + rhsCurrent->data;
        lhsCurrent->data = coef;
        lhsCurrent = lhsCurrent->next;
        rhsCurrent = rhsCurrent->next;
    }
    cleanup();
    return *this;
}

Polynomial::Polynomial(vector<int> coefficentVec){
    // if we have no coefficent its 0!
    if(coefficentVec.size()  == 0){
        head = new Node();
        maxPower = 0;
    }else{
        head = new Node();
        Node* current = head;
        for(size_t i = 0; i < coefficentVec.size(); i++){
            current->data = coefficentVec[i];
            if(i + 1 != coefficentVec.size()){
                current->next = new Node();
                current = current->next;
            }
        }
        maxPower = coefficentVec.size() - 1;
        // remove anything that'll mess up the polynomial
        cleanup();
    }
}

Polynomial& Polynomial::operator=(const Polynomial& rhs){
    if(this == &rhs){
        return *this;
    }
    cleanup();
    Polynomial::Node* newPoly = nullptr;
    Polynomial::Node* current = rhs.head;

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
    // update the head and maxPower
    this->head = newPoly;
    this->maxPower = rhs.maxPower;
    return *this;
}

void Polynomial::cleanup() {
    Node* current = this->head;
    Node* prev = nullptr;

    // Remove leading zeros
    while (current != nullptr && current->data == 0) {
        Node* toDelete = current;
        current = current->next;
        delete toDelete;
        this->maxPower--; 
        // Update maxPower if leading zeros are being removed.
    }

    // Update head pointer after removing leading zeros
    this->head = current;

    // If all elements were zero, ensure the polynomial is properly reset
    if (this->head == nullptr) {
        this->head = new Node{0, nullptr}; 
        // Create a single zero node if all were zeros.
        this->maxPower = 0;       // Reset maxPower if all were leading zeros.
        return;
    }

    // Traverse the rest of the list without removing zeros
    while (current != nullptr) {
        prev = current;
        current = current->next;
    }
}


bool Polynomial::printerHelper(Node* current, 
                                int power, std::ostream& os) const {
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
        os << "+";
    }
    return printerHelper(current->next, power - 1, os );
}

bool operator==(const Polynomial& lhs, const Polynomial& rhs){
    // DEBUGGING IGNORE
    // cout << "OPERATOR IS CALLED";
    // cout << "lhs: " << lhs.maxPower << endl;
    // cout << "rhs: " << rhs.maxPower << endl;
    if(lhs.maxPower != rhs.maxPower){
        return false;
    }
    Polynomial::Node* lhsCurrent = lhs.head;
    Polynomial::Node* rhsCurrent = rhs.head;
    // Check if the data is the same
    while(lhsCurrent != nullptr){
        if(lhsCurrent->data != rhsCurrent->data){
            return false;
        }
        lhsCurrent = lhsCurrent->next;
        rhsCurrent = rhsCurrent->next;
    }
    return true;
}

bool operator!=(const Polynomial& lhs, const Polynomial& rhs){
    return !(lhs == rhs);
}

Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs){
    Polynomial temp(lhs);
    temp += rhs;
    return temp;
}

ostream& operator<<(ostream& os, const Polynomial& poly){
    poly.printerHelper(poly.head, poly.maxPower, os);
    return os;
}