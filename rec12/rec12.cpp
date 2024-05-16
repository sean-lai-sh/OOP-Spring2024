/*
Author Sean Lai Sheng Hong
file: rec12.cpp


*/
#include <cstdlib>
#include <iostream>
using namespace std;

template <typename T>
class List {
    struct Node;
    friend ostream& operator<<(ostream& os, const List<T>& rhs){
        Node* curr = rhs.head->next;
        while(curr != rhs.tail){
            os << curr->data << ' ';
            curr = curr->next;
        }
        return os;
    
    }
public:
    
    class iterator{
    public:
        iterator(Node* node): curr(node){}
        T& operator*(){
            return curr->data;
        }
        iterator& operator++(){
            curr = curr->next;
            return *this;
        }
        bool operator!=(const iterator& rhs){
            return curr != rhs.curr;
        }
        Node*getPtr(){
            return curr;
        }
    private:
        Node* curr;
    };

    class const_iterator{
    public:
        const_iterator(Node* node): curr(node){}
        const T& operator*(){
            return curr->data;
        }
        const_iterator& operator++(){
            curr = curr->next;
            return *this;
        }
        bool operator!=(const const_iterator& rhs){
            return curr != rhs.curr;
        }
        Node* getPtr(){
            return curr;
        }
    private:
        Node* curr;
    };

    List()
    {   
        this->head = new Node{};
        this->tail = new Node{T(), nullptr, head};
        head->next = tail;
        length = 0;
    }


    void push_back(const T& data){
        Node* new_node = new Node{data, tail, tail->prev};
        tail->prev->next = new_node;
        tail->prev = new_node;
        length += 1;
    }

    void pop_back(){
        if (length == 0){
            return;
        }
        // Get last node
        Node* last_node = tail->prev;
        // Get its previous node
        Node* prev_node = last_node->prev;
        // Set the previous node's next to tail
        prev_node->next = tail;
        // Set tail's previous to the previous node
        tail->prev = prev_node;
        // Delete the last node
        delete last_node;
        length -= 1;
    }

    void push_front(const T& data){
        Node* new_node = new Node{data, head->next, head};
        head->next->prev = new_node;
        head->next = new_node;
        length += 1;
    }

    void pop_front(){
        if (length == 0){
            return;
        }
        // Get first node
        Node* first_node = head->next;
        // Get its next node
        Node* next_node = first_node->next;
        // Set the next node's previous to head
        next_node->prev = head;
        // Set head's next to the next node
        head->next = next_node;
        // Delete the first node
        delete first_node;
        length -= 1;
    }

    int front() const{
        return head->next->data;
    }

    int& front(){
        return head->next->data;
    }

    int back() const{
        return tail->prev->data;
    }

    int& back(){
        return tail->prev->data;
    }

    size_t size() const{
        return length;
    }

    void clear(){
        while (length != 0){
            pop_back();
        }
    }

    const T& operator[](size_t index) const{
        Node* curr = head->next;
        for (size_t i = 0; i < index; ++i){
            curr = curr->next;
        }
        return curr->data;
    }

    T& operator[](size_t index){
        Node* curr = head->next;
        for (size_t i = 0; i < index; ++i){
            curr = curr->next;
        }
        return curr->data;
    }

    iterator begin(){
        return iterator(head->next);
    }

    iterator end(){
        return iterator(tail);
    }

    const_iterator begin() const{
        return const_iterator(head->next);
    }

    const_iterator end() const{
        return const_iterator(tail);
    }


    ~List(){
        clear();
        delete head;
        delete tail;
    }

    List(const List& rhs){
        head = new Node{};
        tail = new Node{0, nullptr, head};
        head->next = tail;
        length = 0;
        Node* curr = rhs.head->next;
        while(curr != rhs.tail){
            push_back(curr->data);
            curr = curr->next;
        }
    }

    List& operator=(const List& rhs){
        if(this != &rhs){
            clear();
            Node* curr = rhs.head->next;
            while(curr != rhs.tail){
                push_back(curr->data);
                curr = curr->next;
            }
        }
        return *this;
    }

    iterator insert(iterator iter, const T& data){
        Node* new_node = new Node{data, iter.getPtr(), iter.getPtr()->prev};
        iter.getPtr()->prev->next = new_node;
        iter.getPtr()->prev = new_node;
        length += 1;
        return iterator(new_node);
    }

    iterator erase(iterator iter){
        if(length == 0){
            cerr << "List is empty" << endl;
            return iterator(tail);
        }
        Node* curr = iter.getPtr();
        Node* to_return = curr->next;
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        delete curr;
        length -= 1;
        return iterator(to_return);
    }

    
private:
    
    struct Node{
        T data = T();
        Node* next = nullptr;
        Node* prev = nullptr;
    };
    Node* head;
    Node* tail;
    size_t length;

    
};

// Task 1
void printListInfo(const List<int>& myList) {
        cout << "size: " << myList.size()
             << ", front: " << myList.front()
             << ", back(): " << myList.back()
             << ", list: " << myList << endl;
}

// // The following should not compile. Check that it does not.
// void changeFrontAndBackConst(const List& theList) {
//     theList.front() = 17;
//     theList.back() = 42;
// }

void changeFrontAndBack(List<int>& theList) {
    theList.front() = 17;
    theList.back() = 42;
}

// // Task 4
void printListSlow(const List<int>& myList) {
    for (size_t i = 0; i < myList.size(); ++i) {
        cout << myList[i] << ' ';
    }
    cout << endl;
}

// // Task 8
void doNothing(List<int> aList) {
    cout << "In doNothing\n";
    printListInfo(aList);
    cout << "Leaving doNothing\n";
}    

int main() {

    // Task 1
    cout << "\n------Task One------\n";
    List<int> myList;
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList.push_back(" << i*i << ");\n";
        myList.push_back(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    
    cout << "Modify the first and last items, and display the results\n";
    changeFrontAndBack(myList);
    printListInfo(myList);
    cout << "===================\n";

    cout << "Remove the items with pop_back\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_back();
    }
    cout << "===================\n";

    // Task 2
    cout << "\n------Task Two------\n";
    cout << "Fill empty list with push_front: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        cout << "myList2.push_front(" << i*i << ");\n";
        myList.push_front(i*i);
        printListInfo(myList);
    }
    cout << "===================\n";
    cout << "Remove the items with pop_front\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.pop_front();
    }
    printListInfo(myList);
    cout << "===================\n";

    // Task 3
    cout << "\n------Task Three------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i*i);
    }
    printListInfo(myList);
    cout << "Now clear\n";
    myList.clear();
    cout << "Size: " << myList.size() << ", list: " << myList << endl;
    cout << "===================\n";

    // Task 4
    cout << "\n------Task Four------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    cout << "Display elements with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Add one to each element with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) myList[i] += 1;
    cout << "And print it out again with op[]\n";
    for (size_t i = 0; i < myList.size(); ++i) cout << myList[i] << ' ';
    cout << endl;
    cout << "Now calling a function, printListSlow, to do the same thing\n";
    printListSlow(myList);
    cout << "Finally, for this task, using the index operator to modify\n"
         << "the data in the third item in the list\n"
         << "and then using printListSlow to display it again\n";
    myList[2] = 42;
    printListSlow(myList);
    

    // Task 5
    cout << "\n------Task Five------\n";
    cout << "Fill empty list with push_back: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i)  myList.push_back(i*i);
    printListInfo(myList);
    cout << "Now display the elements in a ranged for\n";
    for (int x : myList) cout << x << ' ';
    cout << endl;
    cout << "And again using the iterator type directly:\n";
    // Note you can choose to nest the iterator class or not, your choice.
    //for (iterator iter = myList.begin(); iter != myList.end(); ++iter) {
    for (List<int>::iterator iter = myList.begin(); iter != myList.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    cout << "WOW!!! (I thought it was cool.)\n";
    
    // // Task 6
    cout << "\n------Task Six------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Filling an empty list with insert at begin(): "
         << "i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.begin(), i*i);
    printListInfo(myList);
    // ***Need test for insert other than begin/end***
    for (int i = 0; i < 10; ++i) myList.insert(++myList.begin(), i*i);
    printListInfo(myList);
    cout << "===================\n";

    // // Task 7
    cout << "\n------Task Seven------\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    cout << "Erasing the elements in the list, starting from the beginning\n";
    while (myList.size()) {
        printListInfo(myList);
        myList.erase(myList.begin());
    }
    // ***Need test for erase other than begin/end***
    cout << "===================\n";

    // // Task 8
    cout << "\n------Task Eight------\n";
    cout << "Copy control\n";
    cout << "Filling an empty list with insert at end: i*i for i from 0 to 9\n";
    myList.clear();
    for (int i = 0; i < 10; ++i) myList.insert(myList.end(), i*i);
    printListInfo(myList);
    cout << "Calling doNothing(myList)\n";
    doNothing(myList);
    cout << "Back from doNothing(myList)\n";
    printListInfo(myList);

    cout << "Filling listTwo with insert at begin: i*i for i from 0 to 9\n";
    List<int> listTwo;
    for (int i = 0; i < 10; ++i) listTwo.insert(listTwo.begin(), i*i);
    printListInfo(listTwo);
    cout << "listTwo = myList\n";
    listTwo = myList;
    cout << "myList: ";
    printListInfo(myList);
    cout << "listTwo: ";
    printListInfo(listTwo);
    cout << "===================\n";
}
