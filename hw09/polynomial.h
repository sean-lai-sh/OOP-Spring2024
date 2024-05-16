#include<iostream>
#include<vector>

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
class Polynomial{
    struct Node{
        int data = 0;
        Node* next = nullptr;
    };
    friend bool operator==(const Polynomial& lhs, const Polynomial& rhs);
    friend bool operator!=(const Polynomial& lhs, const Polynomial& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
    friend Polynomial operator+(const Polynomial& lhs, const Polynomial& rhs);
    
public:
    Polynomial(std::vector<int> coefficentVec = {});
    bool printerHelper(Node* current, int power, std::ostream& os) const ;

    Polynomial& operator+=(const Polynomial& rhs);
    
    // Copy constructor
    Polynomial(const Polynomial& rhs);

    int evaluate(int x) const;

    Polynomial& operator=(const Polynomial& rhs);
private:
    Node* addToBack(Node* current, int data);
    void cleanup();
    Polynomial::Node* head;
    int maxPower;
};
#endif
