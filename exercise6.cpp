#include <cctype>
#include <cstring> 
#include <iostream>

using namespace std;

// Declaration
int find_sum(const int *table, int length);

int main() {
    int table[20];

    // Fill the table with values 1 through 20
    for (int i = 0; i < 20; i++) {
        table[i] = i + 1;
    }
   
    // Pointer to the start of the table
    int* const pointer = table; 

    // Sum of the 10 first numbers
    int sum1 = find_sum(pointer, 10);

    // Move the pointer 10 elements
    *pointer = table[10];

    // Sum of the 5 numbers after the 10 first
    int sum2 = find_sum(pointer, 5);

    // Reassigning the value of the pointer
    *pointer = table[15];

    // Sum of the 5 numbers after the 15 first
    int sum3 = find_sum(pointer, 5);

    cout << "\nSum of the first 10 numbers: " << sum1 << endl;
    cout << "\nSum of the 5 numbers after the first 10: " << sum2 << endl;
    cout << "\nSum of the 5 last numbers: " << sum3 << endl;
}


// Definition
int find_sum(const int *table, int length) {
    int sum = 0;

    for (int i = 0; i < length; i++) {
        // Add the current value to the sum
        sum += *table + i;
    }
    
    return sum;
}