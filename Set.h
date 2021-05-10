#ifndef POKEMON_SET_H
#define POKEMON_SET_H
#include "SetInterface.h"
#include <list>
#include <iostream>
#include <iomanip>

using namespace std;
template<typename T>
class Set : public SetInterface<T>
{

public:
    Set() {

    };
    ~Set(){
        clear();
    };


    bool insert(const T& item) {
      myList.push_back(item);
      myList.sort();
      myList.unique();
      return true;
    }

    /** Removes all items from the set. */
    void clear() {
        myList.clear();
    }

    /** @return: the number of elements contained by the Set. */
    size_t size() const {
       return myList.size();
    }

    /** @return: return 1 if contains element equivalent to item, else 0. */
    size_t count(const T& item) {
       typename std::list<T>::iterator iter;
       iter = find (myList.begin(), myList.end(), item);

       if (iter != myList.end()) {
           return 1;
       }
       else {
           return 0;
       }
    }

    /** @return: string representation of items in Set. */
    string toString() const {
        stringstream out;
        if(myList.empty()) {
            return "";
        }
        typename std::list<T>::const_iterator iter = myList.begin();
        while(iter != myList.end()) {
            out << *iter << ",";
            ++iter;
        }
        string finalOut = out.str();
        finalOut.pop_back();
        return finalOut;
    }

     friend ostream& operator<<(ostream& os, Set<T>& set) {
        os << set.toString();
        return os;
    }










private:
list<T> myList;



};









#endif //POKEMON_SET_H
