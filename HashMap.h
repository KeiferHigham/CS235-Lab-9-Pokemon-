#ifndef POKEMON_HASHMAP_H
#define POKEMON_HASHMAP_H
#include "HashMapInterface.h"
#include "Pair.h"
#include "sstream"
#include <algorithm>
#include <cmath>

#define DEFAULT_MAP_HASH_TABLE_SIZE	31
#define HASH_CONSTANT				3
#define LOAD_THRESHOLD				75

using namespace std;

template<typename K, typename V>
class HashMap : public HashMapInterface<K,V> {



private:

    Pair<K,V>* pairs;
    size_t capacity;
    size_t numItems = 0;

    /*template<typename J>
    struct hash
    {
        size_t operator()(const J& Key)
        {
            return 0;
        }
    };
    template<>
    struct hash<string> {

        size_t operator()(const string& b) {
            size_t hash = 0;
            for(size_t i = 0; i < b.length(); i++) {
                hash = hash * HASH_CONSTANT + b[i];
            }
            return hash;
        }
    };
     */

public:

    HashMap() {
        capacity = DEFAULT_MAP_HASH_TABLE_SIZE;
        pairs = new Pair<K,V>[DEFAULT_MAP_HASH_TABLE_SIZE];
    }
    ~HashMap() {
        clear();
    }

    size_t Hash(const K& key) {
        long long index = 0;
        for(size_t i = 0; i < key.size(); ++i) {
            // index = index * HASH_CONSTANT + key[i];
            index += (key[i] * pow(HASH_CONSTANT, key.size()-(i+1)));
        }

        return index;
    }
/** Read/write index access operator.
    If the key is not found, an entry is made for it.
    @return: Read and write access to the value mapped to the provided key. */
      V& operator[](const K& key) {

        if((size() * 100) / capacity > LOAD_THRESHOLD) {
            Rehash();
        }
      size_t index = Hash(key) % capacity;
      size_t originalIndex = index;
       size_t i = 1;
      while(1)
      {
         if(pairs[index].first != K()) {

            if(pairs[index].first == key) {
              break;
            }
            index = (originalIndex + (i * i)) % capacity;
            i = i + 1;
         } else {
             numItems = numItems + 1;
             pairs[index].first = key;
             break;
         }
      }
      return pairs[index].second;

    }

    void Rehash()  {
          /*size_t newCapacity = capacity * 2;
          Pair<K,V>* newPairs = new Pair<K,V>[newCapacity];
          size_t k = 1;

          for(int i = 0; i < capacity; ++i) {
              if(pairs[i].first.length() > 0 ) {

                  size_t newHashIndex = Hash((pairs[i].first)) % (newCapacity);
                  size_t originalIndex = newHashIndex;
                 // if(newPairs[newHashIndex].first == pairs[i].first) {
                  //    continue;
                 // }
                  while(newPairs[newHashIndex].first != K()) {

                      newHashIndex = (originalIndex + (k * k)) % newCapacity;
                      k+=1;
                  }
                  newPairs[newHashIndex].first = pairs[i].first;
                  newPairs[newHashIndex].second = pairs[i].second;
              }
          }
          capacity = newCapacity;
          swap(pairs,newPairs);
          delete [] newPairs;
          newPairs = NULL;*/

          size_t oldCapacity = capacity;
          capacity = capacity * 2 ;
          numItems = 0;

          Pair<K, V>* oldPairs = pairs;
          pairs = new Pair<K, V>[capacity];

          for (size_t i = 0; i < oldCapacity; i++) {
              if (oldPairs[i].first != "") {
                  operator[](oldPairs[i].first) = oldPairs[i].second;
              }
          }

          delete[] oldPairs;
      }
    /** @return: the number of elements that match the key in the Map. */
    size_t count(const K& key) {

        for(size_t i = 0; i < capacity; ++i) {
            if(key == pairs[i].first) {
                return 1;
            }
        }
        return 0;


    }
    /** Removes all items from the Map. */
    void clear(void) {
      delete [] pairs;
      pairs = NULL;


    }


    /** @return: number of Key-Value pairs stored in the Map. */
    size_t size(void) const {
       return numItems;
    }
    /** @return: maximum number of Key-Value pairs that the Map can hold. */
     size_t max_size(void) const {
         return capacity;
    }
    /** @return: string representation of Key-Value pairs in Map. */
    std::string toString(void) const {
         stringstream out;
         out << size() << "/" << capacity << endl;
        for(int i = 0; i < capacity; ++i) {
              if(pairs[i].first != K()) {
                 out << "  [" << i << ":" << pairs[i].first << "->" << pairs[i].second << "]" << endl;
              }
          }
        return out.str();


    }











};












#endif //POKEMON_HASHMAP_H
