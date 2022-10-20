#include <cctype>
#include <cstring> 
#include <iostream>

using namespace std;

int main() {

    int i = 3;
    int j = 5;
    int *p = &i; // Points to 3
    int *q = &j; // Points to 5

    // Adresses
    cout << "The adresses of the attributes...\n" << endl;

    cout << "i :" << &i << endl;
    cout << "j :" << &j << endl;
    cout << "*p :" << &*p << endl;
    cout << "*q :" << &*q << endl;

    // Values
    cout << "\nThe values of the attributes...\n" << endl;

    cout << "i :" << i << endl;
    cout << "j :" << j << endl;
    cout << "*p :" << *p << endl;
    cout << "*q :" << *q << endl;

    *p = 7; // Points to 7 --> so does i now

    *q += 4; // Points to 9 --> so does j now

    *q = *p + 1; // Points to 8 --> so does j now

    p = q; // *p points to 8 --> i still points to 7 
    cout << *p << " " << *q << endl;  
}
