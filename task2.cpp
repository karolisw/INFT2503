#include "set.hpp"
#include <iostream>
#include <string>
#include <cassert>  

using namespace std;

int main() {

    // Creating the empty set
    Set set;

    // Asserting that the size is 0
    assert(set.numbers.size() == 0);

    // Adding an unknown number to a set
    set.insert(4);

    // Asserting that the set size changed
    assert(set.numbers.size() == 1);

    // Adding an allready present number to a set
    set.insert(4);

    // Asserting that the set size remained unchanged
    assert(set.numbers.size() == 1);

    // Creating a vector
    vector<int> vector {1,7,8,10,17};

    // Finding the union between the set and the vector
    Set unionSet = set.operatorUnion(vector);

    // The size of the union set should be vector.size() + 1 (Set contains 1 element not present in vector)
    assert(unionSet.numbers.size() == (vector.size() + 1));

    // Making the set equal to the vector
    set.convert(vector);

    // The set and the vector should now be equal in size
    assert(set.numbers.size() == vector.size());
    
    // Printing out a set
    set.print();
}