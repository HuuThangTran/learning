/***
* Anh Le // First and Last name
* mle288 // UCSC UserID
* 2024 Winter CS101 PA1
* ListTest.c // FileName
* Testing the data strucutre fuction for client // Describe the program
***/

#include "List.h"
#include <stdio.h>
int main() {
    // Create a new list
    List myList = newList();
    // Test various List operations
    append(myList, 1);
    prepend(myList, 2);
    append(myList, 3);
    printf("Original List: ");
    printList(stdout, myList);
    printf("\n");
    // Test move functions
    moveFront(myList);
    moveNext(myList);
    printf("Current Element: %d\n", get(myList));
    // Test insert functions
    insertBefore(myList, 4);
    insertAfter(myList, 5);
    printf("Updated List: ");
    printList(stdout, myList);
    printf("\n");
    // Test delete functions
    deleteFront(myList);
    deleteBack(myList);
    delete(myList);
    printf("List after deletion: ");
    printList(stdout, myList);
    printf("\n");
    // Free allocated memory
    freeList(&myList);
    return 0;
}