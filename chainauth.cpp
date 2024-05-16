#include<string>
#include<iostream>
#include<list>
#include<vector>
using namespace std;

template<typename T>
class chainAuth{

public:
    chainAuth(const string& masterpw, const list<T>& keys = list<T>())
        : masterpw(masterpw), authKeys(keys) {}

    void add(const T& newKey, const string& masterkey){
        if(masterkey != masterpw){
            throw exception();
        }
        authKeys.push_back(newKey);
    }

    bool auth(const vector<T>& outsideKeys) const {
        if(outsideKeys.size() != authKeys) return false;
        size_t total_size = authKeys.size();
        auto cur = authKeys.begin();
        for(size_t p = 0; p < total_size; ++p){
            if(*cur != outsideKeys[p]){
                return false;
            }else{
                cur = ++cur;
            }
        }
        return true;
    }
private:
    string masterpw;
    list<T> authKeys;
};

int main(){
    cout << "works";
}