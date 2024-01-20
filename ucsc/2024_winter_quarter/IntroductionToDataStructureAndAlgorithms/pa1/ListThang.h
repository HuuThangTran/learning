/*
    // Constructors-Destructors  
    List newList(void);       // Creates and returns a new empty List. 
    void freeList(List* pL);  // Frees all heap memory associated with *pL, and sets *pL to NULL.
    // Access functions ----------------------------------------------------------- 
    int length(List L); // Returns the number of elements in L. 
    int index(List L);  // Returns index of cursor element if defined, -1 otherwise. 
    int front(List L);  // Returns front element of L. Pre: length()>0 
    int back(List L);   // Returns back element of L. Pre: length()>0 
    int get(List L);    // Returns cursor element of L. Pre: length()>0, index()>=0 
    bool equals(List A, List B); // Returns true iff Lists A and B contain the same sequence of elements, returns false otherwise. 
    // Manipulation procedures  
    void clear(List L);      // Resets L to its original empty state. 
    void set(List L, int x); // Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0 
    void moveFront(List L);  // If L is non-empty, sets cursor under the front element, otherwise does nothing. 
    void moveBack(List L);   // If L is non-empty, sets cursor under the back element, otherwise does nothing. 
    void movePrev(List L);   // If cursor is defined and not at front, move cursor one step toward the front of L; if cursor is defined and at front, cursor becomes undefined; if cursor is undefined do nothing 
    void moveNext(List L);   // If cursor is defined and not at back, move cursor one step toward the back of L; if cursor is defined and at back, cursor becomes undefined; if cursor is undefined do nothing 
    void prepend(List L, int x); // Insert new element into L.  If L is non-empty, insertion takes place before front element. 
    void append(List L, int x);  // Insert new element into L.  If L is non-empty, insertion takes place after back element. 
    void insertBefore(List L, int x);  // Insert new element before cursor. Pre: length()>0, index()>=0 
    void insertAfter(List L, int x);   // Insert new element after cursor. Pre: length()>0, index()>=0 
    void deleteFront(List L);  // Delete the front element. Pre: length()>0 
    void deleteBack(List L);   // Delete the back element. Pre: length()>0 
    void delete(List L);       // Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0 
    
    // Other operations 
    void printList(FILE* out, List L);  // Prints to the file pointed to by out, a string representation of L consisting of a space separated sequence of integers, with front on left. 
    List copyList(List L);  // Returns a new List representing the same integer sequence as L. The cursor in the new list is undefined, regardless of the state of the cursor in L. The state of L is unchanged. 
    
    The above operations are required for full credit, though it is not expected that all will be used by the client module 
    in this project.  The following operation is optional, and may come in handy in some future assignment: 
    List concatList(List A, List B);  // Returns a new List which is the concatenation of A and B.  The cursor in the new List is undefined, regardless of the states of the cursors in A and B. The states of A and B are unchanged. 
*/


#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdbool.h>

// Define List to be a pointer to some struct c
typedef struct ListObj* List;

//Constructors - Destructors
    // Create and return  new empty list
    List newList(void);
    // Frees all heap memory associate with *pl and set *pl to NULL;
    void freeList(List* pL); 

// Acess functions
    // Returns the number of element in L
    int length(List L);
    // Returns indexof cursor element if defined, -1 otherwise.
    int listIndex(List L);
    // returns front element of L. Pre: length() > 0
    int front(List L);
    // returns back element of L. Pre: length() > 0
    int back(List L);
    // returns cursor element of L. Pre: length() >0, index() >=0
    int get(List L);
    // Returns true if List A ang B contain the same sequence of elemtns, retuns false othewise
    bool equals(List A, List B);


// Manipulation procedures
    // Resets L to its original empty state. 
    void clear(List L);
    // Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0 
    void set(List L, int x);
    // If L is non-empty, sets cursor under the front element, otherwise does nothing. 
    void moveFront(List L);
    // If L is non-empty, sets cursor under the back element, otherwise does nothing. 
    void moveBack(List L);
    // If cursor is defined and not at front, move cursor one step toward the front of L; if cursor is defined and at front, cursor becomes undefined; if cursor is undefined do nothing 
    void movePrev(List L);
    // If cursor is defined and not at back, move cursor one step toward the back of L; if cursor is defined and at back, cursor becomes undefined; if cursor is undefined do nothing 
    void moveNext(List L);
    // Insert new element into L.  If L is non-empty, insertion takes place before front element. 
    void prepend(List L, int x);
    // Insert new element into L.  If L is non-empty, insertion takes place after back element. 
    void append(List L, int x);
    // Insert new element before cursor. Pre: length()>0, index()>=0 
    void insertBefore(List L, int x);
    // Insert new element after cursor. Pre: length()>0, index()>=0 
    void insertAfter(List L, int x);
    // Delete the front element. Pre: length()>0 
    void deleteFront(List L);
    // Delete the back element. Pre: length()>0 
    void deleteBack(List L);
    // Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
    void delete(List L);       


// Other functions
    // Prints to the file pointed to by out, a string representation of L consisting of a space separated sequence of integers, with front on left. 
    void printList(FILE* out, List L);
    // Returns a new List representing the same integer sequence as L. The cursor in the new list is undefined, regardless of the state of the cursor in L. The state of L is unchanged. 
    List copyList(List L);
    
    // // The above operations are required for full credit, though it is not expected that all will be used by the client module 
    // in this project.  The following operation is optional, and may come in handy in some future assignment: 
    // List concatList(List A, List B);  // Returns a new List which is the concatenation of A and B.  The cursor in the new List is undefined, regardless of the states of the cursors in A and B. The states of A and B are unchanged.


#endif