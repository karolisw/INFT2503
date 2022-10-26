#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

ostream &operator<<(ostream &out, const vector<int> &table) {
  for (auto &e : table)
    out << e << " ";
  return out;
}

bool greaterThan(int i) {
    if (i > 15) {
        return true;
    }
    return false;
}

// "About the same" is defined (by us) as value1 - value2 <= 2. 
bool theSame(int i, int j) {
    if (abs(i-j) <= 2) {
        return true;
    }
    return false;
}

bool isOdd(int number) {
    if (number % 2 != 0) {
        return true;
    }
    return false;
}

int main() {
    vector<int> v1 = {3, 3, 12, 14, 17, 25, 30};

    vector<int> v2 = {2, 3, 12, 14, 24};

    // Find the first elemenet of v1 > 15 using 'find_if' 
    auto it = find_if (v1.begin(), v1.end(), greaterThan);
    cout << "The first element greater than 15 is: " << *it << '\n';

    // Doing the same thing using lambda instead of function
    auto it2 = find_if (v1.begin(), v1.end(), [] (auto s) { 
        return s > 15; 
        });
    cout << "The first element greater than 15 is: " << *it2 << '\n';

    // Is the interval [v1.begin(), v1.begin() + 5] and v2 equal using this definition?
    if (equal(v1.begin(), v1.begin() + 5, v2.begin(), theSame)) {
        cout << "The contents of v1-v1+5 and v2 are equal.\n";
    }
    else {
        cout << "The contents of v1-v1+5 and v2 differ.\n";
    }

    // Is the interval [v1.begin(), v1.begin() + 4] equal to v2?
    if (equal(v1.begin(), v1.begin() + 4, v2.begin(), theSame)) {
        cout << "The contents of v1-v1+4 and v2 are equal.\n";
    }
    else {
        cout << "The contents of v1-v1+4 and v2 differ.\n";
    }    

    // Creating a new vector with room for v1
    vector<int> v3;
    v3.resize(v1.size());

    cout << "v1 before replacing odd numbers with 100: " << v1 << endl;

    // Replace all odd numbers in v1 with 100 using replace_copy_if
    replace_copy_if (v1.begin(), v1.end(), v3.begin(), isOdd, 100);

    cout << "v1 after replacing odd numbers with 100: " << v3 << endl;
}