#include <iostream>

using namespace std;

 // 3 ways to assign a value to number
int main() {
    double number;
    double *pointer = &number;
    double &ref = number; 

    number = 5;
    cout << "Number is now: " << number << endl;

    *pointer = 7;
    cout << "Number is now: " << number << endl;

    ref = 17;
    cout << "Number is now: " << number << endl;
}