// rec13_start.cpp

#include <iostream>
#include <fstream>
#include <vector>      // task 1
#include <list>        // task 2
#include <algorithm>   // task 3
#include <string>      // task 21
#include <set>         // task 22
#include <map>         // task 23
using namespace std;

void printListIter(const list<int> &l);

void task11Auto(std::list<int> &testList);

void printListRF(const list<int>& l);

list<int>::iterator mySearch(list<int>& l, int value);

list<int>::iterator mySearch2(list<int>& l, int value);

bool mySearchFunc(int i);

class searchPred {
public:
    searchPred(int value) : value(value) {}
    bool operator()(int i) const { return i == value; }
private:
    int value;
};



// list<int>::iterator ourFind(list<int>::iterator& start
//                             , list<int>::iterator& end
//                             , int value) {
//     cout << "Sean's find\n";
//     for(list<int>::iterator i = start; i != end; ++i) {
//         if(*i == value) {
//             return i;
//         }
//     }
//     return end;
// }

template <typename T, typename U>
T ourFind(T start, T end, const U& value) {
    cout << "Sean's templated find\n";
    for(T i = start; i != end; ++i) {
        if(*i == value) {
            return i;
        }
    }
    return end;
}


int main() {
    // 1. Create a vector with some values and display using ranged for
    cout << "Task 1:\n";
    vector<int> test{1,2,3,4,5,6,7,8,9,10};

    for(int i : test) {
        cout << i << ' ';
    }
    cout << "\n=======\n";

    // 2. Initalize a list as a copy of values from the vector
    cout << "Task 2:\n";
    list<int> testList(test.begin(), test.end());
    for(int i : testList) {
        cout << i << ' ';
    }
    cout << "\n=======\n";

    // 3. Sort the original vector.  Display both the vector and the list
    cout << "Task 3:\n";
    sort(test.begin(), test.end());
    cout << "\n=======\n";

    // 4. print every other element of the vector.
    cout << "Task 4:\n";
    for(size_t i = 0; i < test.size(); i += 2) {
        cout << test[i] << ' ';
    }
    cout << "\n=======\n";

    // 5. Attempt to print every other element of the list using the
    //    same technique.
    cout << "Task 5:\n";
    // for(size_t i = 0; i < testList.size(); i += 2) {
    //     cout << testList[i] << ' ';
    // }
    cout << "\n=======\n";

    //
    // Iterators
    //

    // 6. Repeat task 4 using iterators.  Do not use auto;
    cout << "Task 6:\n";
    for(vector<int>::iterator i = test.begin(); i != test.end(); i += 2) {
        cout << *i << ' ';
    }
    cout << "\n=======\n";

    // 7. Repeat the previous task using the list.  Again, do not use auto.
    //    Note that you cannot use the same simple mechanism to bump
    //    the iterator as in task 6.
    cout << "Task 7:\n";
    for(list<int>::iterator i = testList.begin(); i != testList.end(); i++) {
        cout << *i << ' ';
        i++;
    }
    cout << "\n=======\n";

    // 8. Sorting a list
    cout << "Task 8:\n";
    //sort(testList.begin(), testList.end());
    cout << "\n=======\n";

    // 9. Calling the function to print the list
    cout << "Task 9:\n";
    printListIter(testList);

    cout << "=======\n";

    // 10. Calling the function that prints the list, using ranged-for
    cout << "Task 10:\n";
    printListRF(testList);

    cout << "=======\n";

    //
    // Auto
    //

    // 11. Calling the function that, using auto, prints alterate
    // items in the list
    cout << "Task 11:\n";
    task11Auto(testList);

    cout << "=======\n";

    
    // 12.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 12:\n";
    list<int>::iterator it = mySearch(testList, 5);
    if (it != testList.end()) {
        cout << "Found\n" << *it << '\n';
    } else {
        cout << "Not found\n";
    }
    cout << "=======\n";

    // 13.  Write a function find that takes a list and value to search for.
    //      What should we return if not found
    cout << "Task 13:\n";
    list<int>::iterator it2 = mySearch2(testList, 5);
    if (it2 != testList.end()) {
        cout << "Found\n" << *it2 << '\n';
    } else {
        cout << "Not found\n";
    }
    cout << "=======\n";

    //
    // Generic Algorithms
    //

    // 14. Generic algorithms: find
    cout << "Task 14:\n";
    find(testList.begin(), testList.end(), 5);
    cout << "=======\n";

    // 15. Generic algorithms: find_if
    cout << "Task 15:\n";
    find_if(testList.begin(), testList.end(), mySearchFunc);
    cout << "=======\n";

    // 16. Functor
    cout << "Task 16:\n";
    find_if(testList.begin(), testList.end(), searchPred(5));
    cout << "=======\n";
    
    // 17. Lambda
    cout << "Task 17:\n";
    find_if(testList.begin(), testList.end(), [](int i) { return i == 5; });
    cout << "=======\n";

    // 18. Generic algorithms: copy to an array
    cout << "Task 18:\n";
    int* heapArr = new int[testList.size()];
    copy(testList.begin(), testList.end(), heapArr);
    for(size_t i = 0; i < testList.size(); i++) {
        cout << heapArr[i] << ' ';
    }
    int* testing = find(heapArr, heapArr + testList.size(), 5);
    cout << *testing;
    delete [] heapArr;
    cout << "\n";
    testing = nullptr;
    cout << "=======\n";

    //
    // Templated Functions
    //

    // 19. Implement find as a function for lists
    cout << "Task 19:\n";
    list<int>::iterator myTests =  ourFind(testList.begin(), 
                                            testList.end(), 
                                            5);
    if (myTests != testList.end()) {
        cout << "Found\n" << *myTests << '\n';
    } else {
        cout << "Not found\n";
    }

    cout << "=======\n";
    
    // 20. Implement find as a templated function
    cout << "Task 20:\n";
    list<int>::iterator myTests2 =  ourFind(testList.begin(), 
                                            testList.end(), 
                                            5);
    if (myTests2 != testList.end()) {
        cout << "Found\n" << *myTests << '\n';
    } else {
        cout << "Not found\n";
    }
    cout << "=======\n";

    //
    // Associative collections
    //

    // 21. Using a vector of strings, print a line showing the number
    //     of distinct words and the words themselves.
    cout << "Task 21:\n";
    ifstream in("pooh-nopunc.txt");
    vector<string> words;
    string word;
    while(in >> word) {
        if(find(words.begin(), words.end(), word) == words.end()) {
            words.push_back(word);
        }
    }
    cout << words.size() << " distinct words\n";
    // Commented to save grader sanity
    // for(const string& w : words) {
    //     cout << w ;
    // }
    in.close();
    cout << "\n=======\n";

    // 22. Repeating previous step, but using the set
    cout << "Task 22:\n";
    ifstream in2("pooh-nopunc.txt");
    set<string> words2;
    string word2;
    while(in2 >> word2) {
        set<string>::iterator it = words2.find(word2);
        if(it == words2.end()) {
            words2.insert(word2);
        }
        /// Insert will do the above error checking
    }
    cout << words2.size() << " distinct words\n";
    // close file
    in2.close();
    cout << "=======\n";

    // 23. Word co-occurence using map
    cout << "Task 23:\n";
    ifstream in3("pooh-nopunc.txt");
    map<string, vector<int>> wordCount;
    // read the file and store the position of each word
    string word3;
    int pos = 0;
    while(in3 >> word3) {
        wordCount[word3].push_back(pos);
        pos++;
    }
    for( auto p : wordCount) {
        cout << p.first << " ";
        for(int i : p.second) {
            cout << i << " ";
        }
        cout << endl;
    }
    in3.close();
    cout << wordCount.size();
    cout << "=======\n";
}

void task11Auto(std::list<int> &testList)
{
    for (auto i = testList.begin(); i != testList.end(); i++)
    {
        cout << *i << ' ';
        i++;
    }
}

void printListIter(const list<int>& l) {
    for(list<int>::const_iterator i = l.begin(); i != l.end(); i++) {
        cout << *i << ' ';
    }
}

void printListRF(const list<int>& l) {
    for(int i : l) {
        cout << i << ' ';
    }
}

list<int>::iterator mySearch(list<int>& l, int value) {
    for(list<int>::iterator i = l.begin(); i != l.end(); i++) {
        if(*i == value) {
            return i;
        }
    }
    return l.end();
}

list<int>::iterator mySearch2(list<int>& l, int value) {
    for(auto i = l.begin(); i != l.end(); i++) {
        if(*i == value) {
            return i;
        }
    }
    return l.end();
}

bool mySearchFunc(int i) {
    return i == 5;
}

template <typename T>
void printList(const T& l) {
    for(auto i : l) {
        cout << i << ' ';
    }
}