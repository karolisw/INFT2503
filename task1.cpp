#include "fraction.hpp"
#include <iostream>
#include <string>

using namespace std;

// To print fraction using ostream!
ostream &operator<<(ostream &out, const Fraction &fraction) {
  out << fraction.numerator << "/" << fraction.denominator;
  return out;
}

void print(const Fraction &frac) {
  cout << frac.numerator << " / " << frac.denominator << endl;
}

int main() {
  // Defining a fraction and an integer
  Fraction fraction1(12, 5);

  Fraction result1 = fraction1 - 5;
  Fraction result2 = 5 - fraction1; 

  cout << "fraction1 - 5 = ";
  print(result1);
  cout << "5 - fraction1 = ";
  print(result2);

}