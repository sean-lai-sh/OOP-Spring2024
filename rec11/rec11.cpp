/*
  rec11.cpp
  Sean Lai
  Learning Basics of Linked Lists
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

//
//  From linked list library in the course's sample code
//
struct Node {
    int data = 0;
    Node* next = nullptr;
};


//
//  Solution to recitation goes here:
//     

// reverse. Creates a new list with all new nodes. Does not modify
// anything in the original list. About seven lines, ignoring close
// braces.
Node* reverse(const Node* hp);

// reverseInPlace. Modifies the original list. No new nodes are
// created. Doesn't change the data values in the nodes, just their
// next fields, so it rearranges the nodes themselves within the
// list.

// Note the "pass by reference" for the head pointer! The parameter,
// hp will be holding a different address when you are done.

// This solution is likely a couple of lines longer than reverse.
void reverseInPlace(Node*& hp);

// Does the sequence of data VALUES in pattern appear anywhere contiguously
// in that order in target?
// Return the position where a match is found, otherwise null.
//Node* isSublist(Node* pattern, Node* target);
const Node* isSublist(const Node* pattern, const Node* target);

// test the nodes in listB looking for the first one to match a node
// from listA. Note that we are matching the addresses of the nodes,
// not the data they hold.
//Node* sharedListBruteForce(Node* listA, Node* listB);
const Node* sharedListBruteForce(const Node* listA, const Node* listB);

// Use an "unordered set", i.e. a hashtable, to identify the first
// element in listB that is also in listA.
//Node* sharedListUsingSet(Node* listA, Node* listB);
const Node* sharedListUsingSet(const Node* listA, const Node* listB);

const Node* sharedListUsingIDK(const Node* listA, const Node* listB);

//get length
int getLength(const Node* head);

///////////////////////////////////////////////////////////////////////////////
//
// Provided test code
//
void listAddHead(Node*& headPtr, int entry);
void listPrint(const Node* headPtr);
void listClear(Node*& headPtr);
Node* listBuild(const vector<int>& vals);
void match(const Node* target, const Node* pattern);

int main() {
    cout << "Part one: \n\n";

    Node* original = listBuild({6,3,2,5});
    cout << "original: ";
    listPrint(original);
    Node* reversed = reverse(original);
    cout << "Calling reverse:\n";
    cout << "original: ";
    listPrint(original);
    cout << "Reversed: ";
    listPrint(reversed);

    cout << "Calling reverseInPlace on the original:\n";
    cout << "original before: ";
    listPrint(original);
    reverseInPlace(original);
    cout << "original after: ";
    listPrint(original);

    cout << "=====================\n\n"
         << "Part two: \n\n";

    // Target: 1 2 3 2 3 2 4 5 6
    Node* target = listBuild({1, 2, 3, 2, 3, 2, 4, 5, 6});
    cout << "Target: ";
    listPrint(target);
    cout << endl;

    // Attempt Match: 1
    // Node* m1 = nullptr;
    Node* m1 = listBuild({1});    
    match(target, m1);
    listClear(m1);

    // Attempt Match: 3 9
    // Node* m2 = nullptr;
    Node* m2 = listBuild({3, 9});    
    match(target, m2);
    listClear(m2);

    // Attempt Match: 2 3
    // Node* m3 = nullptr;
    Node* m3 = listBuild({2, 3});    
    match(target, m3);
    listClear(m3);

    // Attempt Match: 2 4 5 6
    Node* m4 = listBuild({2, 4, 5, 6});    
    match(target, m4);
    listClear(m4);

    // Attempt Match: 2 3 2 4
    Node* m5 = listBuild({2, 3, 2, 4});    
    match(target, m5);
    listClear(m5);

    // Attempt Match: 5 6 7
    Node* m6 = listBuild({5, 6, 7});    
    match(target, m6);
    listClear(m6);

    // Attempt Match: 
    m1 = listBuild({6});    
    match(target, m1);
    listClear(m1);

    // Attempt Match: 
    m1 = nullptr;
    match(target, m1);

    cout << "Task Three\n";
    cout << "Target: ";
    listPrint(target);

    cout << "Matching target against self:\n";
    cout << "Brute force: ";
    listPrint(sharedListBruteForce(target, target));
    cout << "Using Set:   ";
    listPrint(sharedListUsingSet(target, target));

    cout << "Matching target against dup of self:\n";
    //Node* dupOfTarget = listDup(target);
    Node* dupOfTarget = listBuild({1, 2, 3, 2, 3, 2, 4, 5, 6});
    cout << "Brute force: ";
    listPrint(sharedListBruteForce(target, dupOfTarget));
    cout << "Using Set:   ";
    listPrint(sharedListUsingSet(target, dupOfTarget));
    listClear(dupOfTarget);

    cout << "Matching target against part of self from fourth node:\n";
    cout << "Brute force: ";
    listPrint(sharedListBruteForce(target, target->next->next->next));
    cout << "Using Set:   ";
    listPrint(sharedListUsingSet(target, target->next->next->next));
    
    cout << "testing against another list whose fourth node"
         << " matches target's fifth node\n";
    Node* another = target->next->next->next->next;
    listAddHead(another, 7);
    listAddHead(another, 6);
    listAddHead(another, 5);
    cout << "other list:\n";
    listPrint(another);

    cout << "Brute force: ";
    const Node* startOfShared = sharedListBruteForce(target, another);
    listPrint(startOfShared);

    cout << "Using Set:   ";
    startOfShared = sharedListUsingSet(target, another);
    listPrint(startOfShared);

    // Clean up
    listClear(target);
    for (Node* p = another; p != startOfShared; ) {
	Node* pNext = p->next;
        delete p;
	p = pNext;
    }

} // main


/// My Code:

Node* reverse(const Node* hp){
    Node* newHead = nullptr;
    const Node* p = hp;
    // Add the nodes in reverse order
    while (p != nullptr){
        listAddHead(newHead, p->data);
        // ListAddHead is adding a node to the head of the list
        // So we're pushing everything into a pseudo stack, where we flip
        // the order of the nodes  
        p = p->next;
    }
    return newHead;
}

void reverseInPlace(Node*& hp){
    Node* newHead = nullptr;
    // dummy node to hold the new head
    Node* p = hp; // Pointer to where we are in the list
    Node* next = nullptr; // Stores what original next is to be used later
    // Add the nodes in reverse order
    while (p != nullptr){
        next = p->next; // Store the original next
        p->next = newHead; // Set the next of the current node to the new head
        newHead = p; // Set the new head to the current node
        p = next; // Move to the next node
    }
    hp = newHead;
}



const Node* isSublist(const Node* pattern, const Node* target){
    if (pattern == nullptr) return target;
    const Node* matchList = nullptr;
    const Node* curPtr = target;
    const Node* posInPattern = pattern;
    const Node* backUp = nullptr;
    while(curPtr != nullptr){
        while(posInPattern != nullptr && curPtr != nullptr && curPtr->data == posInPattern->data){
            if(posInPattern == pattern){
                backUp = curPtr;
                matchList = curPtr;
            }
            posInPattern = posInPattern->next;
            curPtr = curPtr->next;
        }
        if(posInPattern == nullptr) return matchList;
        posInPattern = pattern;
        if(backUp != nullptr) {
            curPtr = backUp->next;
            backUp = nullptr;
        }
        else{
            curPtr = curPtr->next;
        }
    }
    if(posInPattern != nullptr) return nullptr;
    return matchList;
}

const Node* sharedListBruteForce(const Node* listA, const Node* listB){
    const Node* curPtrA = listA;
    const Node* curPtrB = listB;
    while(curPtrA != nullptr){
        while(curPtrB != nullptr){
            if(curPtrA == curPtrB){
                return curPtrA;
            }
            curPtrB = curPtrB->next;
        }
        curPtrB = listB;
        curPtrA = curPtrA->next;
    }
    return nullptr;
}

const Node* sharedListUsingSet(const Node* listA, const Node* listB){
    unordered_set<const Node*> set;
    const Node* curPtrA = listA;
    const Node* curPtrB = listB;
    while(curPtrA != nullptr){
        set.insert(curPtrA);
        curPtrA = curPtrA->next;
    }
    while(curPtrB != nullptr){
        if(set.find(curPtrB) != set.end()){
            return curPtrB;
        }
        curPtrB = curPtrB->next;
    }
    return nullptr;
}

//get length
int getLength(const Node* head){
    int length = 0;
    const Node* curPtr = head;
    while(curPtr != nullptr){
        length++;
        curPtr = curPtr->next;
    }
    return length;
}

const Node* sharedListUsingIDK(const Node* listA, const Node* listB){
    // get length
    int lengthA = getLength(listA);
    int lengthB = getLength(listB);

    // get the difference in length
    int diff = lengthA - lengthB;

    // get the longer list
    const Node* curPtrA = listA;
    const Node* curPtrB = listB;
    if(diff > 0){
        for(int i = 0; i < diff; i++){
            curPtrA = curPtrA->next;
        }
    }
    else{
        for(int i = 0; i < -diff; i++){
            curPtrB = curPtrB->next;
        }
    }
    // check for shared node
    while(curPtrA != nullptr && curPtrB != nullptr){
        if(curPtrA == curPtrB){
            return curPtrA;
        }
        curPtrA = curPtrA->next;
        curPtrB = curPtrB->next;
    }
    return nullptr;
}
//
// Functions provided for the test code
//

// match the target with the pattern. Calls isSublist to do the work.
void match(const Node* target, const Node* pattern)
{
    cout << "Attempt pattern: ";
    listPrint(pattern);
    const Node* result = isSublist(pattern, target);
    if (result)
        listPrint(result);
    else
        cout << "Failed to match\n";
    cout << endl;
} // match

void listAddHead(Node*& headPtr, int entry)
{
    headPtr = new Node{entry, headPtr};
} // listAddHead

// listPrint prints out the data values in the list.
// All the values are printed on a single line with blanks separating them.
void listPrint(const Node* headPtr)
{
    const Node* p = headPtr;
    while (p != nullptr) {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
} // listPrint

// Need to add this to the provided functions
void listClear(Node*& headPtr)
{
    while (headPtr) {
        Node* next = headPtr->next;
        delete headPtr;
        headPtr = next;
    }
} // listClear

Node* listBuild(const vector<int>& vals)
{
    Node* result = nullptr;
    for (size_t index = vals.size(); index > 0; --index) {
        listAddHead(result, vals[index-1]);
    }
    return result;
} // listBuild
