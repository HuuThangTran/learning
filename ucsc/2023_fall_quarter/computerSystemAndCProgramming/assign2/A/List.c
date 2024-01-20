#include <stdio.h>
#include "List.h"

/*
The underlying data structure for the List ADT will be a doubly linked list.  The file List.c should therefore contain 
a  private  (non-exported)  struct  called  NodeObj  and  a  pointer  to  that  struct  called  Node.    The  struct  NodeObj 
should contain fields for an int (the data), and two Node references (the previous and next Nodes, respectively.)  
You should also include a constructor and destructor for the private Node type.  The private (non-exported) struct 
ListObj should contain fields of type Node referring to the front, back and cursor elements, respectively.  ListObj 
should also contain int fields for the length of a List, and the index of the cursor element.  When the cursor is 
undefined, an appropriate value for the index field is -1, since that is what is returned by function index() in 
such a case.  Study the examples Queue.c and Stack.c on the course webpage, and feel free to use either file as a 
starting point for List.c.   

// front, back, cursor, (int) fields, index
The examples Queue.c and Stack.c on the website are good starting points for the List ADT module in this project.  
You  are  welcome  to  simply  start  with  one  of  those  files,  rename  things,  then  add  functionality  until  the 
specifications for the List ADT are met.  You should first design and build your List ADT, test it thoroughly, and 
only then start coding Lex.c.  Start early and ask questions if anything is unclear.  Information on how to turn in 
your project is posted on the class webpage.   
*/

//Private struct not exported
typedef struct NodeObj {
    int data;
    struct NodeObj* next;
    struct NodeObJ* prev;
}   NodeObj;

// Private reference type, not exported
typedef NodeObj* Node;

Node newNode(int data) {
    //
}

void freeNode(Node* pN) {
    //
}

// Private ListObj struct, constructor -destructor
typedef struct ListObj {
    // front, back, cursor, (int) fields, index
    

}
//Constructors - Destructors
    // Create and return  new empty list
    List newList(void);
    // Frees all heap memory associate with *pl and set *pl to NULL;
    void freeList(List* pL); 
//