// Anh Le // First and Last name
// mle288 // UCSC UserID
// 2024 Winter CS101 PA7
// DictionaryTest.cpp // FileName
// the testfile for the object methods // Describe the program

#include <iostream>
#include "Dictionary.h"

using namespace std;

int main() {
    // Test constructor
    Dictionary dict;

    // Test setValue and getValue
    dict.setValue("apple", 5);
    dict.setValue("banana", 10);
    dict.setValue("orange", 7);

    cout << "Value of apple: " << dict.getValue("apple") << endl;
    cout << "Value of banana: " << dict.getValue("banana") << endl;
    cout << "Value of orange: " << dict.getValue("orange") << endl;

    // Test size
    cout << "Size of dictionary: " << dict.size() << endl;

    // Test contains
    cout << "Contains apple? " << (dict.contains("apple") ? "Yes" : "No") << endl;
    cout << "Contains grape? " << (dict.contains("grape") ? "Yes" : "No") << endl;

    // Test remove
    dict.remove("banana");
    cout << "After removing banana, size: " << dict.size() << endl;

    // Test begin and end
    dict.begin();
    cout << "First key: " << dict.currentKey() << endl;
    dict.end();
    cout << "Last key: " << dict.currentKey() << endl;

    // Test next and prev
    dict.begin();
    dict.next();
    cout << "Next key after first: " << dict.currentKey() << endl;
    dict.prev();
    cout << "Prev key before first: " << dict.currentKey() << endl;

    // Test to_string
    cout << "Dictionary contents:\n" << dict.to_string() << endl;

    return 0;
}



