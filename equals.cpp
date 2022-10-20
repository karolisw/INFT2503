#include <iostream>
#include <random>
#include <vector>

using namespace std;

// Template for generic use
template <typename Type>
bool equal(Type a, Type b) {
    cout << "Template was used" << endl;
    if (a == b) {
        cout << a << " and " << b << " are equal" << endl;
        return true;
    }
    cout << a << " and " << b << " are not equal" << endl;
    return false;
};

// Special version for double
bool equal(double a, double b) {
    cout << "Special version was used" << endl;
    double limit = 0.00001;

    if (fabs(a-b) <= limit) {
        cout << a << " and " << b << " are equal" << endl;
        return true;
    }
    cout << a << " and " << b<< " are not equal" << endl;
    return false;
}

int main() {

    cout.precision(6);

    // These two do not qualify as equal
    double a = 7.21;
    double b = 3.66;

    // These two qualify as equal
    double c = 1.000001;
    double d = 1.000002;

    // These use the template version
    int e = 4;
    int f = 5;

    equal(a,b);
    equal(c,d);
    equal(e,f);
}
