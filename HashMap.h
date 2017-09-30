/*
    HashMap.h
    Arthur Shi
    9.23.2017
    Interface and implementation for C++ fixed-size hashmap using linear probing.
*/

#ifndef HASH_MAP_H
#define HASH_MAP_H

#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <cassert>

/// HashNode class to repesent key/value pairs

template <typename Value>
class HashNode {
public:
    std::string key;
    Value* value;

    HashNode(const std::string& k, Value* v) : key(k), value(v) {}
};

template <typename Value>
class HashMap {
public:
    /// Public interface

    /*
        Initializes a HashMap that can hold `size` key/value pairs.
    */
    HashMap(int size) : size_curr(0), size_max(size) {
         //dynamically allocate an array of `size` HashNode*, initialized as nullptrs
        table = new HashNode<Value>*[size]();
        str_hash = std::hash<std::string>();
        ghost = new HashNode<Value>("", nullptr);
    }

    /*
        Destructor which deallocates all memory from heap upon instance scope ending.
    */
    ~HashMap() {
        for (int i = 0; i < size_max; ++i) {
            if (table[i] != nullptr && table[i] != ghost) {
                delete table[i];
                table[i] = nullptr;
            }
        }
        delete ghost;
        delete[] table;
    }

    /*
        mplaces the specified key/value pair, updating the value if the specified key is already in the table.
    */
    bool set(const std::string& key, Value& value) {
        int idx = hashFunction(key);
        
        if (!probeSet(key, idx)) { //`key` not found
            if (idx == -1) { //full table
                std::cout << "Failed to create new key/value pair: table full.\n";
                return false;
            } else { //room available to insert new key
                assert(table[idx] == nullptr || table[idx] == ghost);
                table[idx] = new HashNode<Value>(key, &value);
                ++size_curr;
                std::cout << "Added new key/value pair to the table.\n";
                return true; 
            }
        } else { //`key` already exists in the table
            table[idx]->value = &value;
            std::cout << "Overwrote value associated with key \"" << key << "\".\n";
            return true;
        }
    }

    /*
        Returns the value at the requested key, or nullptr if the key doesn't exist.
    */
    Value* get(const std::string& key) {
        int idx = hashFunction(key);
        
        if (probe(key, idx)) {
            return table[idx]->value;
        } else {
            return nullptr;
        }
    }

    /*
        Deletes the requested key from the table.
    */
    Value* deleteKey(const std::string& key) {
        int idx = hashFunction(key);
        
        if (probe(key, idx)) {
            Value* temp = table[idx]->value;
            delete table[idx];
            table[idx] = ghost;
            --size_curr;
            std::cout << "Key \"" << key << "\" was deleted.\n";
            return temp;
        } else {
            std::cout << "function deleteKey: Key \"" << key << "\" not found.\n";
            return nullptr;
        }
    }

    /*
        Returns the current load factor of the table.
    */
    float load() {
        float k = float(size_curr) / size_max;
        return k;
    }

private:
    /// Helper functions
    
    /*
        Syntactic sugar for hashing function
    */
    int hashFunction(const std::string& key) {
        return int(str_hash(key) % size_max);
    }

    /*
        Probes for the requested key. 
        If found, `i` is updated to the index of the requested key in self->table and returns true.
        Returns false if requested key not found.
    */
    bool probe(const std::string& key, int& i) {
        int count = 0;
        i = hashFunction(key);
        //while we haven't seen all nodes, and consecutive nodes 
        // are non-null, and we haven't found our key
        while (count < size_max && table[i] != nullptr && table[i]->key != key) {
            ++count;
            ++i;
            if (i >= size_max) { i = 0; } 
        }
    
        //found value if the node exists and matches keys
        return table[i] != nullptr && table[i] != ghost && table[i]->key == key;
    }

    /*
        Returns true if the requested key exists, with `i` set to the index of the requested key.
        If the requested key isn't found, `i` is -1 if the table is full, else the index of the first available spot.
    */
    bool probeSet(const std::string& key, int& i) {
        //ghost_avail < size_max aka max value of i ==> an available ghost node has been found
        int ghost_avail = size_max;
        int count = 0;
        //while we haven't hit an empty spot and haven't found our key
        while (count < size_max && table[i] != nullptr && table[i]->key != key) {
            ++count;
            ++i;
            if (i >= size_max) { i = 0; }
            if (table[i] == ghost && ghost_avail >= size_max) { ghost_avail = i; }
        }

        if (table[i] != nullptr && table[i] != ghost && table[i]->key == key) {
            return true;
        }
        else {
            //leave i as the closest ghost or nullptr to the hashed index of `key`
            if (ghost_avail < i) { i = ghost_avail; }
            //leave i as -1 if `key` not found and table is full
            if (size_curr == size_max) { i = -1; }
            return false;
        }
    }

    /// Member data
    
    HashNode<Value>** table;
    std::hash<std::string> str_hash;
    HashNode<Value>* ghost;
    int size_curr;
    int size_max;
};

#endif