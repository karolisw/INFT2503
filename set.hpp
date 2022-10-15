#pragma once
#include <vector>
#include <iostream>

using namespace std;

class Set {
public:
    vector<int> numbers;

    // Constructor that does nothing
    Set();

    // Empty vector of ints (the empty set)
    Set(const vector<int> &vector);

    // Method to set (mutate) the vector 'numbers' for *this set
    void setVector(const vector<int> &numbers_);

    // Returns a new set containing the union of the this vector and another vector
    Set operatorUnion(const vector<int> &vector) const;

    // Add a new number to this set. Nothing happens if the number is already part of the set
    Set &insert(int number);

    // Converts this Set into another set 'vector' (turns *this into a copy)
    Set &convert(vector<int> &vector); 

    void print();

    bool hasDuplicates(vector<int> &vector);
};

// To print
ostream &operator<<(ostream &os, const Set &set);
