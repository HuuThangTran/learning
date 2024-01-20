#include <stdio.h>
#include <stdlib.h>
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

// Private function to create a new Node
Node newNode(int data) {
    Node N = (Node)malloc(sizeof(NodeObj));
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return N;
}

// Private function to free a Node
void freeNode(Node* pN) {
    free(*pN);
    *pN = NULL;
}

// Private ListObj struct, constructor -destructor
typedef struct ListObj {
    // Node referring to the front, back and cursor element front, back, cursor, (int) fields, (int) index
    Node front;
    Node back;
    Node cursor;
    int length;
    int cursorindex;
} ListObj;


//Constructors - Destructors
    // Create and return  new empty list
    List newList(void) {
        List L = (List)malloc(sizeof(ListObj));
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->length = 0;
        L->cursorindex; = -1;
        return L;      
    }
    // Frees all heap memory associate with *pl and set *pl to NULL;
    void freeList(List* pL) {
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }

// Access function
    // Returns the number of element in L
    int length(List L) {
        int count = 0;
        Node traversing = L->front;
        while (traversing != NULL) {
            count++;
            traversing = traversing->next;
        }
        return count;
    }

    // Returns indexof cursor element if defined, -1 otherwise.
    int getindex(List L) {
        if (L->cursor !=NULL) {
            return L->cursorindex;;
        }
        return -1;
    }

    // returns front element of L. Pre: length() > 0
    int front(List L) {
        if (length(L) <= 0) {
            return 1; //Error
        }
        return L->front->data;
    }

    // returns back element of L. Pre: length() > 0
    int back(List L) {
        if (length(L) <= 0) {
            return 1; //Error
        }
        return L->back->data;
    }

    // returns cursor element of L. Pre: length() >0, index() >=0
    int get(List L) {
        if (length(L) <= 0 || getindex(L) < 0) {
            return 1;
        }
        return L->cursor->data;
    }

    // Returns true if List A ang B contain the same sequence of elemtns, retuns false othewise
    bool equals(List A, List B) {
        Node traversingA = A->front;
        Node traversingB = B->front;
        while (traversingA != NULL && traversingB != NULL) {
            if (traversingA->data != traversingB->data) {
                return false;
            }
            traversingA = traversingA->next;
            traversingB = traversingB-> next;
        }
        return traversingA == NULL && traversingB == NULL;
    }

// Manipulation procedures
    // Resets L to its original empty state. 
    void clear(List L) {
        Node traversing = L->front;
        while (traversing != NULL) {
            Node traversing_next = traversing->next;
            freeNode(&traversing);
            traversing = traversing_next;
        }
        L->front = NULL;
        L->back = NULL;
        L->cursor = NULL;
        L->cursorindex = -1;
        L->length = 0;
    }

    // Overwrites the cursor element’s data with x. Pre: length()>0, index()>=0 
    void set(List L, int x) {
        if (length(L) <= 0 || getindex(L) <0){
            exit(EXIT_FAILURE); //error
        }
        L->cursor->data = x;
    }

    // If L is non-empty, sets cursor under the front element, otherwise does nothing. 
    void moveFront(List L) {
        if (L->front != NULL) {
            L->cursor = L->front;
            L->cursorindex = 0;
        }
    }
    // If L is non-empty, sets cursor under the back element, otherwise does nothing. 
    void moveBack(List L) {
        if (L->back != NULL) {
            L->cursor = L->back;
            L->cursorindex = length(L) -1;
        }
    }

    // If cursor is defined and not at front, move cursor one step toward the front of L; if cursor is defined and at front, cursor becomes undefined; if cursor is undefined do nothing 
    void movePrev(List L) {
        if (L->cursor != NULL && L->cursor != L->front) {
            L->cursor = L->cursor->prev;
            L->index--;
        } 
        //if cursor is defined and at front, cursor becomes undefined; if cursor is undefined do nothing 
        else {
            L->cursor = NULL;
            L->index = -1;
        }
    }
    // If cursor is defined and not at back, move cursor one step toward the back of L; if cursor is defined and at back, cursor becomes undefined; if cursor is undefined do nothing 
    void moveNext(List L) {
        if (L->cursor != NULL && L->cursor != L->back) {
            L->cursor = L->cursor->next;
            L->index++;
        }
        // if cursor is defined and at back, cursor becomes undefined; if cursor is undefined do nothing 
        else {
            L->cursor = NULL;
            L->index = -1;
        }
    }
    // Insert new element into L.  If L is non-empty, insertion takes place before front element. 
    void prepend(List L, int x) {
        Node new = newNode(x);
        if (L->front == NULL) {
            L->front = new;
            L->back = new;
            L->length = 1;
        } else {
            L->front->prev = new;
            new->next = L->front;
            L->front = new;
            L->length++;
            if (L->cursor != NULL) {
                L->index++;
            }
        }
    }
    // Insert new element into L.  If L is non-empty, insertion takes place after back element. 
    void append(List L, int x) {
        Node new = newNode(x);
        if (L->back == NULL) {
            L->front = new;
            L->back = new;
            L->length = 1;
        } else {
            L->back->next = new;
            new->prev = L->back;
            L->back = new;
            L->length++;
        }
    }
    // Insert new element before cursor. Pre: length()>0, index()>=0 
    void insertBefore(List L, int x) {
        if (length(L) <= 0 || index(L) <0) {
            exit(EXIT_FAILURE); //error
        }
        Node new = newNode(x);
        new->next = L->cursor;
        if (L->cursor->prev == NULL) {
            new->prev = NULL;
            L->front = new;
        } else {
            new->prev = L->cursor->prev;
            L->cursor->prev->next = new;
        }
        L->cursor->prev = new;
        L->index++;
    }

    // Insert new element after cursor. Pre: length()>0, index()>=0 
    void insertAfter(List L, int x) {
        if (length(L) <= 0 || index(L) <0) {
            exit(EXIT_FAILURE); //error
        }
        Node new = newNode(x);
        new->prev = L->cursor;
        if (L->cursor->next == NULL) {
            new->next = NULL;
            L->back = new;
        } else {
            new->next = L->cursor->next;
            L->cursor->next->prev = new;
        }
        L->cursor->next = new;
    }

    // Delete the front element. Pre: length()>0 
    void deleteFront(List L) {
        if(length(L) <= 0) {
            exit(EXIT_FAILURE); //error
        }
        // Check if the cursor is at the front
        if (L->cursor == L->front) {
            L->cursor = NULL;
            L->index = -1;
        } else if (L->cursor != NULL) {
            L->index--;
        }
        // delete front node
        Node del = L->front;
        L->front = L->front->next;

        // check if list is now empty
        if (L->front = NULL) {
            L->back = NULL;
        } else {
            L->front->prev=NULL
        }
        freeNode(&del);
    }
    // Delete the back element. Pre: length()>0 
    void deleteBack(List L) {
        if(length(L) <= 0) {
            exit(EXIT_FAILURE); //error
        }
        // Check if the cursor is at the back
        if (L->cursor == L->back) {
            L->cursor = NULL;
            L->index = -1;
        } 
        // delete back node
        Node del = L->back;
        L->back = L->back->prev;
        // check if list is now empty
        if (L->back ==NULL) {
            L->front = NULL;
        } else {
            L->back->next = NULL;
        }
        freeNode(&del);
    }
    // Delete cursor element, making cursor undefined. Pre: length()>0, index()>=0
    void delete(List L) {
        if (length(L) <= 0 || index(L) <0) {
            exit(EXIT_FAILURE); //error
        }
        Node del = L-> cursor;
        
        // if the cursor is the same with front element
        if (L->cursor->prev == NULL) {
            L->front = L->cursor->next;
            if (L->front != NULL) {
                L->front->prev = NULL;
            } else {
                L->back = NULL;
            }
        } else {
            L->cursor->prev->next = L->cursor->next;
        }
        // if the cursor is the same with back element
          if (L->cursor->next == NULL) {
                L->back = L->cursor->prev;
            if (L->back != NULL) {
                L->back->next = NULL;
            } else {
                L->front = NULL;
            }
        } else {
            L->cursor->next->prev = L->cursor->prev;
        }
        L->cursor = NULL;
        L->index = -1;
        freeNode(&del);
    }


// Other functions
    // Prints to the file pointed to by out, a string representation of L consisting of a space separated sequence of integers, with front on left. 
    void printList(FILE* out, List L) {
        fprintf(out, "(");
        int count = 0;
        Node traversing = L->front;
        while (traversing != NULL) {
            if (count != 0) {
                fprintf(out, ", ");
            }
            if (count == L->index) {
                if (traversing != L->cursor) {
                    fprintf(out, "<error>");
                } else {
                    fprintf(out, "<");
                }
            }
            fprintf(out, "%d", traversing->data);
            if (count == L->index) {
                fprintf(out, ">");
            }
            count++;
            traversing = traversing->next;
        }
        fprintf(out, ")");
    }

    // Returns a new List representing the same integer sequence as L. The cursor in the new list is undefined, regardless of the state of the cursor in L. The state of L is unchanged. 
    List copyList(List L) {
        List New = newList();
        Node copy = L->front;
        while (copy != NULL) {
            append(New, copy->data);
            copy = copy->next;
        }
        return New;        
    }