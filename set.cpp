#include "set.hpp"
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>


using namespace std;

Set::Set() : numbers(){}; // IF does not work then initialize an empty vector inside parentheses

Set::Set(const vector<int> &vector) {
    setVector(vector);
}

void Set::setVector(const vector<int> &vector_) { 
    auto copy = vector_; // Necessary because the _vector is const and 'hasDuplicates' sorts the vector-input
    if (!vector_.empty() && !hasDuplicates(copy)) {
        numbers = vector_;
    } else {
        throw "Vector was empty or contained duplicates";
    }
};

// Creates a new Set containing the union of two sets
Set Set::operatorUnion(const vector<int> &vector) const {

    // Create a new set to hold the current set
    Set newSet = Set(numbers);

    // For all elements in the other set
    for (size_t i = 0; i < vector.size(); i++) {

        // If newSet contains value - do nothing
        if (find(newSet.numbers.begin(), newSet.numbers.end(), vector.at(i)) != newSet.numbers.end()) {
            continue;
        }

        // If the element is not present in new set - add it
        else {
            newSet.numbers.emplace_back(vector.at(i));
        }
    }
    // Return set
    return newSet;
};

// Add a new number to this set. Nothing happens if the number is already part of the set
Set &Set::insert(int number) {

    // If newSet does not contain value - add it
    if (find(numbers.begin(), numbers.end(), number) == numbers.end()) {
        numbers.push_back(number);
    }
    return *this;
};

// Converts this Set into another set 'vector' (turns *this into a copy)
Set &Set::convert(vector<int> &vector) {
    if (!vector.empty() && !hasDuplicates(vector)) {  
        numbers = vector;
    }
    return *this;
};

bool Set::hasDuplicates(vector<int> &vector) {

    // The vector must be sorted
    sort(vector.begin(), vector.end());
    return adjacent_find(vector.begin(), vector.end()) != vector.end();
}


// Prints the Set using friend function 
ostream &operator<<(ostream &os, const Set &set) {
    os << "{ ";
	for (size_t i = 0; i < set.numbers.size() - 1; i++ ) {
        os << set.numbers[i] << ", ";
        os << set.numbers[set.numbers.size()-1];
	    os << " }";
    }
	return os;
};

void Set::print() {
  for (size_t i = 0; i < this->numbers.size(); i++) {
    cout << this->numbers.at(i);
    cout << " ";
  }
  cout << " " << endl;
}


