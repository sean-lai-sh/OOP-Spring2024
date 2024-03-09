/*
  Sean Lai
  February 9, 2024
  rec03_start.cpp
 */

// Provided
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;




// Task 1
// Define an Account struct
struct account{
    string name;
    int accountNumber;
};


// Task 2
// Define an Account class (use a different name than in Task 1)
class accountClass{
  friend ostream& operator<<(ostream& os, const accountClass& accountToken);
  public:
    accountClass(const string& name, int accountNumber): name(name), accountNumber(accountNumber){}
    //get name
    string getName() const{
        return name;
    }
    //get account number
    int getAccountNumber() const{
        return accountNumber;
    }
  private:
    string name;
    int accountNumber;
};

// Task 3
// Define an Account (use a different name than in Task 1&2) and
// Transaction classes
class Transaction{
  friend ostream& operator<<(ostream& os, const Transaction& transactionToken);
  public:
    Transaction(const string& type, int amount): type(type), amount(amount){}
  private:
    string type;
    int amount;
};
class accountTransaction{
  friend ostream& operator<<(ostream& os, const accountTransaction& accountToken);
  public:
    accountTransaction(const string& name, int accountNumber): name(name), accountNumber(accountNumber), balance(0){}
    
    void deposit(int amount){
        balance += amount;
        transactionHistory.push_back(Transaction("deposit", amount));
    }

    void withdraw(int amount){
        if(amount > balance){
            cerr << "Account# " << accountNumber << " has only " << balance << ". Insufficient funds for withdrawal of " << amount << "\n";
            return;
        }
        balance -= amount;
        transactionHistory.push_back(Transaction("withdrawal", amount));
    }

    int getAccountNumber() const{
        return accountNumber;
    }
  private:
    string name;
    int accountNumber;
    int balance;
    vector<Transaction> transactionHistory;
    
};


// Task 4
// Define an Account with a nested public Transaction class
// (use different names than in the previous Tasks)

class accountTransaction2{
  friend ostream& operator<<(ostream& os, const accountTransaction2& accountToken);
  friend ostream& operator<<(ostream& os, const accountTransaction2::Transaction& transactionToken);
  public:
    accountTransaction2(const string& name, int accountNumber): name(name), accountNumber(accountNumber), balance(0){}
    
    class Transaction{
      friend ostream& operator<<(ostream& os, const Transaction& transactionToken);
      public:
        Transaction(const string& type, int amount): type(type), amount(amount){}
      private:
        string type;
        int amount;
    };

    void deposit(int amount){
        balance += amount;
        transactionHistory.push_back(Transaction("deposit", amount));
    }

    void withdraw(int amount){
        if(amount > balance){
            cerr << "Account# " << accountNumber << " has only " << balance << ". Insufficient funds for withdrawal of " << amount << "\n";
            return;
        }
        balance -= amount;
        transactionHistory.push_back(Transaction("withdrawal", amount));
    }

    int getAccountNumber() const{
        return accountNumber;
    }
  private:
    string name;
    int accountNumber;
    int balance;
    vector<Transaction> transactionHistory;
    
};


// Task 5
// Define an Account with a nested private Transaction class
// (use different names than in the previous Tasks)
class accTrans3{
  class Transaction{
      friend ostream& operator<<(ostream& os, const Transaction& transactionToken);
      public:
        Transaction(const string& type, int amount): type(type), amount(amount){}
      private:
        string type;
        int amount;
    };
  friend ostream& operator<<(ostream& os, const accTrans3& accountToken);
  friend ostream& operator<<(ostream& os, const accTrans3::Transaction& transactionToken);
  public:
    accTrans3(const string& name, int accountNumber): name(name), accountNumber(accountNumber), balance(0){}

    void deposit(int amount){
        balance += amount;
        transactionHistory.push_back(Transaction("deposit", amount));
    }

    void withdraw(int amount){
        if(amount > balance){
            cerr << "Account# " << accountNumber << " has only " << balance << ". Insufficient funds for withdrawal of " << amount << "\n";
            return;
        }
        balance -= amount;
        transactionHistory.push_back(Transaction("withdrawal", amount));
    }

    int getAccountNumber() const{
        return accountNumber;
    }
  private:
    
    string name;
    int accountNumber;
    int balance;
    vector<Transaction> transactionHistory;
    
};
// open a file
void openFile(ifstream& fileReader, const string& fileName);

// add account to vector from filestream
void addAccountStruct(vector<account>& accounts, ifstream& fileReader);

void printAccStruct(const vector<account>& accounts);

void addAccountClass(vector<accountClass>& accounts, ifstream& fileReader);

void addAccountEmplace(vector<accountClass>& accounts, ifstream& fileReader);

size_t findAccount(const vector<accountTransaction>& accounts, int accountNumber);

size_t findAccount2(const vector<accountTransaction2>& accounts, int accountNumber);

size_t findAccount3(const vector<accTrans3>& accounts, int accountNumber);

void task5Runtime(ifstream& fileReader);

int main() {
    ifstream fileReader;
    // Task 1: account as struct
    //      1a
    cout << "Task1a:\n";
    openFile(fileReader, "accounts.txt");
    vector<account> accounts;
    string name;
    int accountNumber;
    // repeat each time a name, acc Number is found
    while(fileReader >> name >> accountNumber){
      account temp; 
      temp.name = name;
      temp.accountNumber = accountNumber;
      accounts.push_back(temp);
    }
    printAccStruct(accounts);
    accounts.clear();
    fileReader.close();
    //      1b
    cout << "Task1b:\n";
    cout << "Filling vector of struct objects, using {} initialization:\n";
    openFile(fileReader, "accounts.txt");
    addAccountStruct(accounts, fileReader);
    printAccStruct(accounts);
    accounts.clear();
    fileReader.close();
    //==================================
    // Task 2: account as class
    openFile(fileReader, "accounts.txt");
    vector<accountClass> accountStorage;
    //      2a
    cout << "==============\n";
    cout << "\nTask2a:";
    cout << "\nFilling vector of class objects, using local class object:\n";
    string nameStore;
    int accNoStore;
    // repeat each time a name, acc Number is found
    while(fileReader >> nameStore >> accNoStore){
        accountClass temp(nameStore, accNoStore);
        accountStorage.push_back(temp);
    }
    fileReader.close();
    // using getters
    for (const accountClass& acc: accountStorage){
        cout << acc.getName() << "\t" << acc.getAccountNumber() << endl;
    }
    cout << "\nTask2b:\n";
    cout << "output using output operator with getters\n";
    
    // using output operator
    for(const accountClass& acc: accountStorage){
        cout << acc;
    }
    cout << "\nTask2c:\n";
    cout << "output using output operator as friend without getters\n";
    // using output operator as friend
    for(const accountClass& acc: accountStorage){
        cout << acc;
    }
    
    cout << "\nTask2d:\n";
    cout << "Filling vector of class objects, using temporary class object:\n";
    accountStorage.clear();
    openFile(fileReader, "accounts.txt");
    addAccountClass(accountStorage, fileReader);
    for(const accountClass& acc: accountStorage){
        cout << acc;
    }
    fileReader.close();
    cout << "\nTask2e:\n";
    cout << "Filling vector of class objects, using emplace_back:\n";
    accountStorage.clear();
    openFile(fileReader, "accounts.txt");
    addAccountEmplace(accountStorage, fileReader);
    for(const accountClass& acc: accountStorage){
        cout << acc;
    }
    fileReader.close();
    cout << "==============\n";
    cout << "\nTask 3:\nAccounts and Transaction:\n";
    openFile(fileReader, "transactions.txt");
    vector<accountTransaction> accountStorage2;
    string commandTokens;
    while(fileReader >> commandTokens){
        if(commandTokens == "Account"){
            string name;
            int accountNumber;
            fileReader >> name >> accountNumber;
            accountStorage2.emplace_back(name, accountNumber);
        }else if(commandTokens == "Deposit"){
            int accountNumber;
            int amount;
            fileReader >> accountNumber >> amount;
            size_t index = findAccount(accountStorage2, accountNumber);
            if(index == accountStorage2.size()){
                cerr << "Account not found\n";
            }else{
                accountStorage2[index].deposit(amount);
            }
        }else if(commandTokens == "Withdraw"){
            int accountNumber;
            int amount;
            fileReader >> accountNumber >> amount;
            size_t index = findAccount(accountStorage2, accountNumber);
            if(index == accountStorage2.size()){
                cerr << "Account not found\n";
            }else{
                accountStorage2[index].withdraw(amount);
            }
        }
    }
    for(const accountTransaction& acc: accountStorage2){
        cout << acc;
    }
    fileReader.close();
    accountStorage2.clear();
    cout << "==============\n";
    cout << "\nTask 4:\nTransaction nested in public section of Account:\n";
    openFile(fileReader, "transactions.txt");
    vector<accountTransaction2> accountStore3;
    string commandStrings;
    while(fileReader >> commandStrings){
        if(commandStrings == "Account"){
            string name;
            int accountNumber;
            fileReader >> name >> accountNumber;
            accountStore3.emplace_back(name, accountNumber);
        }else if(commandStrings == "Deposit"){
            int accountNumber;
            int amount;
            fileReader >> accountNumber >> amount;
            size_t index = findAccount2(accountStore3, accountNumber);
            if(index == accountStore3.size()){
                cerr << "Account not found\n";
            }else{
                accountStore3[index].deposit(amount);
            }
        }else if(commandStrings == "Withdraw"){
            int accountNumber;
            int amount;
            fileReader >> accountNumber >> amount;
            size_t index = findAccount2(accountStore3, accountNumber);
            if(index == accountStore3.size()){
                cerr << "Account not found\n";
            }else{
                accountStore3[index].withdraw(amount);
            }
        }
    }
    for(const accountTransaction2& acc: accountStore3){
        cout << acc;
    }
    fileReader.close();
    accountStore3.clear();
    cout << "==============\n";
    cout << "\nTask 5:\nTransaction nested in private section of Account:\n";
    task5Runtime(fileReader);
    
}

void openFile(ifstream& fileReader, const string& fileName){
    fileReader.open(fileName);
    if(!fileReader){
        cerr << "File not found\n";
        exit(1);
    }
}
/// TASK 1
void addAccountStruct(vector<account>& accounts, ifstream& fileReader){
    string name;
    int accountNumber;
    // repeat each time a name, acc Number is found
    while(fileReader >> name >> accountNumber){
        accounts.push_back(account{name, accountNumber});
    }
}

void printAccStruct(const vector<account>& accounts){
    for(const account& acc: accounts){
        cout << acc.name << "\t" << acc.accountNumber << endl;
    }
}

/// TASK 2

void addAccountClass(vector<accountClass>& accounts, ifstream& fileReader){
    string name;
    int accountNumber;
    // repeat each time a name, acc Number is found
    while(fileReader >> name >> accountNumber){
        accounts.push_back(accountClass(name, accountNumber));
    }
}
void addAccountEmplace(vector<accountClass>& accounts, ifstream& fileReader){
    string name;
    int accountNumber;
    // repeat each time a name, acc Number is found
    while(fileReader >> name >> accountNumber){
        accounts.emplace_back(name, accountNumber);
    }
}
ostream& operator<<(ostream& os, const accountClass& accountToken){
    os << accountToken.name << "\t" << accountToken.accountNumber << endl;
    return os;
}
/// TASK 3
ostream& operator<<(ostream& os, const Transaction& transactionToken){
    os << "\t" << transactionToken.type << " " << transactionToken.amount << endl;
    return os;
}

ostream& operator<<(ostream& os, const accountTransaction& accountToken){
  os << accountToken.name << "\t" << accountToken.accountNumber << endl;
  for(const Transaction& transaction : accountToken.transactionHistory){
    os << transaction;
  }
  return os;
}

size_t findAccount(const vector<accountTransaction>& accounts, int accountNumber){
    for(size_t i = 0; i < accounts.size(); ++i){
        if(accounts[i].getAccountNumber() == accountNumber){
            return i;
        }
    }
    return accounts.size();
}

//TASK 4
ostream& operator<<(ostream& os, const accountTransaction2& accountToken){
  os << accountToken.name << "\t" << accountToken.accountNumber << endl;
  for(const accountTransaction2::Transaction& transaction : accountToken.transactionHistory){
    os << transaction;
  }
  return os;
}
ostream& operator<<(ostream& os, const accountTransaction2::Transaction& transactionToken){
    os << "\t" << transactionToken.type << " " << transactionToken.amount << endl;
    return os;
}
size_t findAccount2(const vector<accountTransaction2>& accounts, int accountNumber){
    for(size_t i = 0; i < accounts.size(); ++i){
        if(accounts[i].getAccountNumber() == accountNumber){
            return i;
        }
    }
    return accounts.size();
}

// TASK 5
ostream& operator<<(ostream& os, const accTrans3& accountToken){
  os << accountToken.name << "\t" << accountToken.accountNumber << endl;
  for(const accTrans3::Transaction& transaction : accountToken.transactionHistory){
    os << transaction;
  }
  return os;
}
ostream& operator<<(ostream& os, const accTrans3::Transaction& transactionToken){
    os << "\t" << transactionToken.type << " " << transactionToken.amount << endl;
    return os;
}
size_t findAccount3(const vector<accTrans3>& accounts, int accountNumber){
    for(size_t i = 0; i < accounts.size(); ++i){
        if(accounts[i].getAccountNumber() == accountNumber){
            return i;
        }
    }
    return accounts.size();
}
void task5Runtime(ifstream& fileReader){
  openFile(fileReader, "transactions.txt");
    vector<accTrans3> accountStore3;
    string commandStrings;
    while(fileReader >> commandStrings){
        if(commandStrings == "Account"){
            string name;
            int accountNumber;
            fileReader >> name >> accountNumber;
            accountStore3.emplace_back(name, accountNumber);
        }else if(commandStrings == "Deposit"){
            int accountNumber;
            int amount;
            fileReader >> accountNumber >> amount;
            size_t index = findAccount3(accountStore3, accountNumber);
            if(index == accountStore3.size()){
                cerr << "Account not found\n";
            }else{
                accountStore3[index].deposit(amount);
            }
        }else if(commandStrings == "Withdraw"){
            int accountNumber;
            int amount;
            fileReader >> accountNumber >> amount;
            size_t index = findAccount3(accountStore3, accountNumber);
            if(index == accountStore3.size()){
                cerr << "Account not found\n";
            }else{
                accountStore3[index].withdraw(amount);
            }
        }
    }
    for(const accTrans3& acc: accountStore3){
        cout << acc;
    }
    fileReader.close();
    accountStore3.clear();
}