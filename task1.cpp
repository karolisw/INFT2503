#include <iostream>

using namespace std;

// Global
const double pi = 3.141592;

// Class declaration
class Circle {

    // Constructor
    public:
        Circle(double radius_);

        // Methods
        int get_area() const;
        double get_circumference() const;

    // Private attributes
    private:
        double radius;
};

// Class implementation
Circle::Circle(double radius_) : radius(radius_) {}

int Circle::get_area() const {
  return pi * radius * radius;
}

double Circle::get_circumference() const {
  double circumference = 2.0 * pi * radius;
  return circumference;
}

int main() {

    Circle circle(5);
    int area = circle.get_area();
    cout << "Arealet er lik " << area << endl;

    double circumference = circle.get_circumference();
    cout << "Omkretsen er lik: " << circumference << endl;
}