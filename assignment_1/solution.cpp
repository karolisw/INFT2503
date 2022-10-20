#include <cctype>
#include <cstring> 
#include <iostream>


using namespace std;

int main() {

    const int length = 5;
    double temperature;

    int countUnder10 = 0;
    int countBetween10And20 = 0;
    int countOver20 = 0;

    cout << "\nDu skal skrive inn 5 temperaturer: \n"; 

    // Reading in 5 temperatures and counting where they belong
    for (int i = 0; i < length; i++) {

        cout << "Temperatur nr " << i + 1 << ": " << endl;

        cin >> temperature;

        if (temperature > 20.0) {
            countOver20 ++;
        }              
        else if (temperature < 10.0) {
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

