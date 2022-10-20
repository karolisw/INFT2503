#include <iostream>
#include <vector> 
#include <algorithm>

using namespace std;

int main() {
    vector<double> vec;
    

    // Adding numbers 1-5 from the beginning of the array
    vec.insert(vec.begin(), { 1.0, 2.2, 3.3, 4.5, 5.1, 6.7 });

    double front = vec.front();
    double back = vec.back();

    cout << "Front of vector: " << front << endl;
    cout << "Back of vector: " << back << endl;

    // Adding 7.2 to front
    vec.emplace(vec.begin(), 7.2);

    cout << "\nFront of vector after emplace" << vec.front() << endl;

    auto found = find(vec.begin(), vec.end(), 7.2);

    // If successfull
    if (found != vec.end()) {
        cout << "Element found in vec: " << *found << endl;
    }
}