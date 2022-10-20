#include <iostream>

using namespace std;

// A pair consists of two types that do not have to be of the same type
template <typename Type1, typename Type2>
class Pair {
public:
    Type1 first;
    Type2 second;

    // Constructor
    Pair(Type1 first, Type2 second) : first(first), second(second) {}

    // Operator that sums two pairs
    Pair operator+(const Pair &other) {
        Pair pair = *this;
        
        pair.first += other.first;
        pair.second += other.second;

        return pair;
    }

    bool operator>(const Pair &other) {
        Pair pair = *this;
        double sum1 = pair.first + pair.second;
        double sum2 = other.first + other.second;

        // Returns true if *this pair is bigger than the other pair
        return sum1 > sum2;
    }

  friend ostream &operator<<(ostream &os, const Pair &pair) {
    return os << "(" << pair.first << ", " << pair.second << ")";
  }
};

int main() {
    Pair<double, int> p1(3.5, 14);
    Pair<double, int> p2(2.1, 7);
    cout << "p1: " << p1.first << ", " << p1.second << endl;
    cout << "p2: " << p2.first << ", " << p2.second << endl;

    if (p1 > p2)
        cout << "p1 er størst" << endl;
    else
        cout << "p2 er størst" << endl;

    auto sum = p1 + p2;
    cout << "Sum: " << sum.first << ", " << sum.second << endl;
}