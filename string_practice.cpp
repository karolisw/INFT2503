#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int main() {
    string word1;
    string word2;
    string word3;
    string sentence;
    string sentence2;

    cout << "Write three words: " << endl;
    cin >> word1;
    cin >> word2;
    cin >> word3;

    sentence = word1 + " " + word2 + " " + word3 + ".";

    cout << "\nThe words form the sentence: " << sentence << endl;

    cout << "\nPrinting out the length of the three words..." << endl;
    cout << "Word 1: " << word1.length() << endl;
    cout << "Word 2: " << word2.length() << endl;
    cout << "Word 3: " << word3.length() << endl;

    cout << "\nThe length of the sentence is: " << sentence.length() << endl;

    cout << "Copying sentence onto a new string..." << endl;
    sentence2 = sentence;

    cout << "The new sentence now looks like this: " << sentence2 << endl;

    cout << "Replacing the letters at pos 10-12 of the new sentence with x's..." << endl;

    // Length should not be shorter than 12
    while (sentence2.length() < 12) {
        sentence2.append("a");
    }

    sentence2.replace(10,3,"xxx");

    cout << "Sentence 1 looks like this now: " << sentence << endl;
    cout << "Sentence 2 looks like this now: " << sentence2 << endl;

    cout << "Copying the first 5 letters of sentence 1 into a new string..." << endl;

    string sentence_start = sentence.substr(0,5);
    cout << "The new string: " << sentence_start << endl;

    size_t index_of_hello = sentence_start.find("hello");

    if (index_of_hello != string::npos) {
        cout << "The new string contains the string 'hello' at pos: " << index_of_hello << endl;
    }
    
    int pos = 0;
    while (pos != sentence.length()) {

        // Searching from the current pos
        int index = sentence.find("er", pos, 5);
        if (index != string::npos) {
            cout << "Found an 'er' sequence at index: " << index << endl;

            // pos = index + 1 in order to not hit the same index again
            pos = index + 1;
        }
    }



    






}