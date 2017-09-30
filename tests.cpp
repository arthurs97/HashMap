/*
    tests.cpp
    Arthur Shi
    9.23.2017
    Testing suite for the HashMap class
*/

#include "HashMap.h"
#include <iostream>
#include <cmath>
#include <cassert>
#include <string>
#include <limits>

using namespace std;

bool are_equal(float f1, float f2) {
    return abs(f1 - f2) < numeric_limits<float>::epsilon();
}

int main() {
    cout << "Begin testing" << endl;
    cout << "---------------" << endl;

    //constructing
    HashMap<string> hm1(5);
    assert(are_equal(hm1.load(), 0.0));

    //querying a key that isn't in the map
    assert(hm1.get("this key isn't in the map") == nullptr);

    //removing a key that isn't in the map
    assert(hm1.deleteKey("this key isn't in the map") == nullptr);
    
    //emplacing a pair
    string world = "world";
    assert(hm1.set("hello", world));
    assert(are_equal(hm1.load(), 0.2));
    cout << "hello " << *hm1.get("hello") << endl;

    //emplacing a pair
    string express1 = "express";
    assert(hm1.set("panda", express1));
    assert(are_equal(hm1.load(), 0.4));
    cout << "panda " << *hm1.get("panda") << endl;

    //Two value types with same value should have distinct addresses
    string express2 = "express";
    assert(hm1.set("orient", express2));
    assert(are_equal(hm1.load(), 0.6));
    assert(hm1.get("panda") != hm1.get("orient"));
    assert(*hm1.get("panda") == *hm1.get("orient"));

    //deleting a key that's not in the map
    assert(hm1.deleteKey("this key isn't in the map") == nullptr);

    //overwriting a key that already exists
    string kungfu = "kung fu";
    assert(hm1.set("panda", kungfu));
    assert(are_equal(hm1.load(), 0.6));
    cout << "panda " << *hm1.get("panda") << endl;

    //emplacing a pair
    string fellows = "fellows";
    assert(hm1.set("kpcb", fellows));
    assert(are_equal(hm1.load(), 0.8));
    cout << "kpcb " << *hm1.get("kpcb") << endl;

    //emplacing a pair
    string shi = "shi";
    assert(hm1.set("arthur", shi));
    assert(are_equal(hm1.load(), 1.0));
    cout << "arthur " << *hm1.get("arthur") << endl;

    //attempting to emplace a pair to a full table
    string full = "full";
    assert(!hm1.set("its", full));

    //deleting a pair
    string* shi_ptr = hm1.get("arthur");
    assert(hm1.deleteKey("arthur") == shi_ptr);
    assert(are_equal(hm1.load(), 0.8));

    //deleting a pair
    string* fellows_ptr = hm1.get("kpcb");
    assert(hm1.deleteKey("kpcb") == fellows_ptr);
    assert(are_equal(hm1.load(), 0.6));

    //verify that creating a node with key "" doesn't find the dummy node
    string empty_str = "";
    string empty = "empty";
    assert(hm1.get(empty_str) == nullptr);
    hm1.set(empty_str, empty);
    assert(hm1.get(empty_str) == &empty);

    cout << endl << endl << endl;
    cout << "---------------" << endl;
    cout << "All tests passed!" << endl;
    return 0;
}
