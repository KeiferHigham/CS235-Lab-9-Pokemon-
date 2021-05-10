//
// Created by Keifer Higham on 11/30/20.
//

#ifndef POKEMON_OLDSET_H
#define POKEMON_OLDSET_H

#include "SetInterface.h"
#include "BST2.h"
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
        return tree.addNode(item);
    }

    /** Removes all items from the set. */
    void clear() {
        tree.clearTree();
    }

    /** @return: the number of elements contained by the Set. */
    size_t size() const {
        return tree.Size();
    }

    /** @return: return 1 if contains element equivalent to item, else 0. */
    size_t count(const T& item) {
        if(tree.Find(item)) {
            return 1;
        }
        return 0;
    }

    /** @return: string representation of items in Set. */
    string toString() const {
        return tree.toString();
    }

    friend ostream& operator<<(ostream& os, Set<T>& set) {
        os << set.toString();
        return os;
    }










private:
    BinaryTree<T> tree;



};











#endif //POKEMON_OLDSET_H
