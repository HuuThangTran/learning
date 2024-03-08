/*
•    Anh Le // First and Last name
•    mle288 // UCSC UserID
•    2024 Winter CS101 PA5
•    ListTest.cpp// FileName
•    Testing the basic function from List.h// Describe the program
*/
#include <iostream>
#include "List.h"

using namespace std;

void printList(const List& L) {
    cout << "List: " << L.to_string() << endl;
    cout << "Position: " << L.position() << endl;
}

int main() {
    // Test default constructor and access functions
    List list1;
    printList(list1);

    // Test manipulation functions
    list1.insertAfter(1);
    list1.insertBefore(2);
    list1.insertAfter(3);
    printList(list1);

    list1.moveNext();
    list1.setAfter(4);
    list1.movePrev();
    list1.setBefore(5);
    printList(list1);

    list1.eraseAfter();
    list1.eraseBefore();
    printList(list1);

    // Test search functions
    list1.insertAfter(1);
    list1.insertAfter(2);
    list1.insertAfter(3);
    int position = list1.findNext(2);
    cout << "Position after findNext(2): " << position << endl;

    position = list1.findPrev(2);
    cout << "Position after findPrev(2): " << position << endl;

    // Test other functions
    List list2 = list1.concat(list1);
    cout << "Concatenated List: " << list2.to_string() << endl;

    list2.cleanup();
    cout << "Cleaned-up List: " << list2.to_string() << endl;

    // Test copy constructor and operator=
    List list3 = list1;
    cout << "Copied List (using copy constructor): " << list3.to_string() << endl;

    List list4;
    list4 = list1;
    cout << "Copied List (using operator=): " << list4.to_string() << endl;

    return 0;
}
