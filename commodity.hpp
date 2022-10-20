#include <iostream>

using namespace std;

// Global
const double sales_tax = 1.05;

// Class declaration
class Commodity {

    // Constructor
    public:
        Commodity(string name_, long id_, double price_);

        // Methods
        string get_name() const;
        long get_id() const;
        double get_price(double quantity);
        double get_price();
        void set_price(double price);
        double get_price_with_sales_tax(double quantity); 

    // Private attributes
    private:
        string name;
        long id;
        double price;
};

// Class implementation
Commodity::Commodity(string name_, long id_, double price_) : name(name_), id(id_), price(price_) {}

string Commodity::get_name() const {
  return name;
}

long Commodity::get_id() const {
  return id;
}

double Commodity::get_price(double quantity) {
  return price * quantity;
}

double Commodity::get_price() {
  return price;
}

void Commodity::set_price(double new_price) {
  price = new_price;
}

double Commodity::get_price_with_sales_tax(double quantity) {
  double new_price = price * sales_tax;
  return new_price * quantity;
}

