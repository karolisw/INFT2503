#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;
ifstream file;   
const char filename[] = "temperatures.txt";   
double temperature;

// Function declaration
void read_temperatures(double temperatures[], int length);

int main() {
    int length = 10; 

    int countUnder10 = 0;
    int countBetween10And20 = 0;
    int countOver20 = 0;

    double temperatures[100];

    cout << "\nLeser inn temperaturene fra fil... \n"; 

    // Using the method 
    read_temperatures(temperatures, length);

    cout << "length is: " << length << endl;

    // Reading in the temperatures and counting where they belong
    for (int i = 0; i < length; i++) {

        cout << "Temperatur nr " << i + 1 << ": " << temperatures[i] << endl;

        if (temperatures[i] > 20.0) {
            countOver20 ++;
        }              
        else if (temperatures[i] < 10.0) {
            countUnder10 ++;
        }
        else {
            countBetween10And20 ++;
        }
    }

    // Returning the counts
    cout << "Antall under 10 er: " << countUnder10 << endl;
    cout << "Antall mellom 10 og 20 er: " << countBetween10And20 << endl;
    cout << "Antall over 20 er: " << countOver20 << endl;
}

// Function definition
void read_temperatures(double temperatures[], int length) {
     int counter = 0;

    // Opening the file 
    file.open(filename); 
    if (!file) {
        cout << "Feil ved åpning av innfil." << endl;
        exit(EXIT_FAILURE);
    }

    // Until we reach the end of the file
    while (file >> temperature) {
        temperatures [counter] = temperature;
        counter ++;
    }

    cout << "Fant: " << counter << " temperaturer" << endl;
    file.close();
}
