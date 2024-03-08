/*
•    Anh Le // First and Last name
•    mle288 // UCSC UserID
•    2024 Winter CS101 PA5
•    List.cpp// FileName
•    The blackbox, the logic behind the function stated in List.h, which is hidden to the users// Describe the program
*/

#include<iostream>
#include<string>
#include"List.h"

using namespace std;

#define DUMMY 0

// //Constructor
List::Node::Node(ListElement x) : data(x), next(nullptr), prev(nullptr) {}


//Empty state
// creating a pointer dummy to node
List::List() : frontDummy(new Node(0)), backDummy(new Node(0)), beforeCursor(frontDummy), afterCursor(backDummy), pos_cursor(0), num_elements(0) {
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
}


// Copy constructor
List::List(const List& L) : frontDummy(new Node(0)), backDummy(new Node(0)), beforeCursor(frontDummy), afterCursor(backDummy), pos_cursor(0), num_elements(0) {
    frontDummy->next = backDummy;
    backDummy->prev = frontDummy;
    Node* N = L.frontDummy->next;
    while (N != L.backDummy) {
        this->insertBefore(N->data);
        N = N->next;
    }
    
    //Position the cursor position the same as the original copy
    this->moveFront();
    while(this->pos_cursor != L.pos_cursor){
        this->moveNext();
    }
}


//Destructor
List::~List(){
    this->clear();
    delete this->frontDummy;
    delete this->backDummy;
}

// // Access functions --------------------------------------------------------

/*
In C++, this is a keyword that represents a pointer to the current instance of a 
class or the current object. It is automatically available within non-static member functions of a 
class and is used to refer to the object on which the member function is called.
*/
// length()
// Returns the length of this List.
/*

The const keyword is used to declare a member function as a "const member function" within a C++ class. 
this member function promises not to modify any of the non-static data members of the class.
*/
int List::length() const{
    return this->num_elements;
}

// front()
// Returns the front element in this List.
ListElement List::front() const{
    if(this->length() <= 0){
        // pre: length()>0
        std::cerr << "pre: length()>0";
        exit(EXIT_FAILURE);
    }
    else{
        return frontDummy->next->data;
    }
}

// back()
// Returns the back element in this List.
// pre: length()>0
ListElement List::back() const{
    if(this->length() <= 0){
        std::cerr << "pre: length()>0";
        exit(EXIT_FAILURE);
    }
    else{
        return backDummy->prev->data;
    }
}


// position()
// Returns the position of cursor in this List: 0 <= position() <= length().
int List::position() const{
    return this->pos_cursor;
}

// peekNext()
// Returns the element after the cursor.
ListElement List::peekNext() const{
    // pre: position()<length()
    if(this->position() >= this->length()){
        std::cerr << "pre: position()<length()" << endl;
        exit(EXIT_FAILURE);
    }
    else{
        return afterCursor->data;
    }
}

// peekPrev()
// Returns the element before the cursor.
ListElement List::peekPrev() const{
    // pre: position()>0
    if(this->position() <= 0){
        std::cerr << "pre: position()>0" << endl;
        exit(EXIT_FAILURE);
    }
    else{
        return beforeCursor->data;
    }
}


// // Manipulation procedures -------------------------------------------------

// clear()
// Deletes all elements in this List, setting it to the empty state.
void List::clear(){
    this->moveFront();
    while(this->length() > 0){
        this->eraseAfter();
    }
}

// moveFront()
// Moves cursor to position 0 in this List.
void List::moveFront(){
    this->beforeCursor = this->frontDummy;
    this->afterCursor = this->beforeCursor->next;
    this->pos_cursor = 0;
}

// moveBack()
// Moves cursor to position length() in this List.
void List::moveBack(){
    this->afterCursor = this->backDummy;
    this->beforeCursor = this->afterCursor->prev;
    this->pos_cursor = this->length();
}


// moveNext()
// Advances cursor to next higher position. Returns the List element that
// was passed over.
ListElement List::moveNext(){
    if(this->position() >= this->length()){
        // pre: position()<length()
        std::cerr << "pre: position()<length()" <<endl;
        exit(EXIT_FAILURE);
    }
    else{
        beforeCursor = afterCursor;
        afterCursor = afterCursor->next;
        this->pos_cursor ++;
        return beforeCursor->data;
    }
}


// movePrev()
// Advances cursor to next lower position. Returns the List element that
// was passed over.
int List::movePrev(){
    // pre: position()>0
    if(position() <= 0){
        std::cerr << "pre: position()>0" <<endl;
        exit(EXIT_FAILURE);
    }
    else{
        afterCursor = beforeCursor;
        beforeCursor = beforeCursor->prev;
        this->pos_cursor --;
        return afterCursor->data;
    }
}

// insertAfter()
// Inserts x after cursor.
void List::insertAfter(ListElement x){
    Node* node = new Node(x);
    node->prev = this->beforeCursor;
    node->next = this->afterCursor;
    this->beforeCursor->next = node;
    this->afterCursor->prev = node;
    this->afterCursor = node;
    this->num_elements ++;
}


// insertBefore()
// Inserts x before cursor.
void List::insertBefore(ListElement x){
    Node* node = new Node(x);
    node->prev = this->beforeCursor;
    node->next = this->afterCursor;
    this->beforeCursor->next = node;
    this->afterCursor->prev = node;
    this->beforeCursor = node;
    this->num_elements ++;
    this->pos_cursor ++;
}

// setAfter()
// Overwrites the List element after the cursor with x.
void List::setAfter(ListElement x){
    // pre: position()<length()
    if (position() >= length()) {
            std::cerr << "pre: position()<length()" << endl;
            exit(EXIT_FAILURE);
        }
    else{
        afterCursor->data = x;
    }
}

// setBefore()
// Overwrites the List element before the cursor with x.
void List::setBefore(ListElement x){
    if (position() <= 0) {
            // pre: position()>0
            std::cerr << "pre: position()>0" << endl;
            exit(EXIT_FAILURE);
        }
    else{
        beforeCursor->data = x;
    }
}

// eraseAfter()
// Deletes element after cursor.
void List::eraseAfter(){

    // pre: position()<length()
    if(position() >= length()){
        std::cerr << "pre: position()<length()" <<endl;
        exit(EXIT_FAILURE);
    }

    else{
        Node* temp = afterCursor;
        this->afterCursor = temp->next;
        this->beforeCursor->next = this->afterCursor;
        this->afterCursor->prev = this->beforeCursor;
        delete temp;
        this->num_elements--;
    }
}


// eraseBefore()
// Deletes element before cursor.
void List::eraseBefore(){

    // pre: position()>0
    if(position() <= 0){
        std::cerr << "pre: position()>0" <<endl;
        exit(EXIT_FAILURE);
    }

    else{
        Node* temp = beforeCursor;
        this->beforeCursor = temp->prev;
        this->afterCursor->prev = this->beforeCursor;
        this->beforeCursor->next = this->afterCursor;
        delete temp;
        this->num_elements--;
        pos_cursor--;
    }
}

// // Other Functions ---------------------------------------------------------

// findNext()
// Starting from the current cursor position, performs a linear search (in
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then
int List::findNext(ListElement x){

    // creat a traversing node
    Node* node = this->afterCursor;
    int relative_right = 1;

    //traversing
    while(node != this->backDummy){
        if(node->data == x){
            this->beforeCursor = node;
            this->afterCursor = node->next;
            this->pos_cursor = this->pos_cursor + relative_right;
            return pos_cursor;
        }
        node = node->next;
        relative_right++;
    }

    // returns the final cursor position. If x is not found, places the cursor
    // at position length(), and returns -1.
    this->afterCursor = this->backDummy;
    this->beforeCursor = this->afterCursor->prev;
    this->pos_cursor = this->length();
    return -1;
}

// findPrev()
// Starting from the current cursor position, performs a linear search (in
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then returns the final cursor position.
int List::findPrev(ListElement x){

    //create a traversing node
    Node* node = this->beforeCursor;
    int relative_left = 1;

    //traversing
    while(node != this->frontDummy){
        if(node->data == x){
            this->beforeCursor = node->prev;
            this->afterCursor = node;
            this->pos_cursor = this->pos_cursor - relative_left;
            return this->pos_cursor;
        }
        node = node->prev;
        relative_left ++;
    }

    //  If x is not found, places the cursor
    // at position 0, and returns -1.
    this->beforeCursor = this->frontDummy;
    this->afterCursor = this->beforeCursor->next;
    this->pos_cursor = 0;
    return -1;
}


// cleanup()
// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost
// occurrance of each element, and removing all other occurances. The cursor
// is not moved with respect to the retained elements, i.e. it lies between
// the same two retained elements that it did before cleanup() was called.
void List::cleanup(){

    // creating a slow traversing node pointer
    Node* node = frontDummy->next;

    int outter_position = 0;

    //traversing the first pointer while having a placeholder
    while(node != backDummy){
        

        //create a fast traversing node pointer
        int a = node->data;
        Node* node_next = node->next;

        int inner_position = outter_position + 1;

        //traversing the fast pointer while comparing the data with slow pointer
        while(node_next != backDummy){
            int b = node_next->data;
            Node* erase = node_next;
            node_next = node_next->next;
            if(a == b){

                // changing the prev and next
                erase->prev->next = erase->next;
                erase->next->prev = erase ->prev;
                delete erase;
                num_elements --;
                if(inner_position <= pos_cursor){
                    pos_cursor --;
                }
            }
            inner_position ++;
            
        }
        outter_position ++;
        node = node->next;
    }

    //moving the cursor
    int position = pos_cursor;
    moveFront();
    while(this->position() != position){
        moveNext();
    }
}

// concat()
// Returns a new List consisting of the elements of this List, followed by
// the elements of L. 
List List::concat(const List& L) const{
    List result(*this);
    result.moveBack();
    Node* node = L.frontDummy->next;
    while (node != L.backDummy) {
        result.insertBefore(node->data);
        node = node->next;
    }

    // The cursor in the returned List will be at postion 0.
    result.beforeCursor = result.frontDummy;
    result.afterCursor = result.beforeCursor->next;
    result.pos_cursor = 0;
    return result;
}

// to_string()
// Returns a string representation of this List consisting of a comma
// separated sequence of elements, surrounded by parentheses.
std::string List::to_string() const{
    string printout;
    printout += "(" ;
    Node* node = this->frontDummy->next;
    while(node != this->backDummy){
        printout += std::to_string(node->data);
        if(node->next != this->backDummy){
            printout +=", " ;
        }
        node = node->next;
    }
    printout += ")" ;
    return printout;
}

// equals()
// Returns true if and only if this List is the same integer sequence as R.
// The cursors in this List and in R are unchanged.
bool List::equals(const List& R) const{
    if (this->length() != R.length()) {
            return false;
    }
    Node* current = this->frontDummy->next;
    Node* checker = R.frontDummy->next;
    while (current != backDummy && checker != R.backDummy) {
        if (current->data != checker->data) {
            return false;
        } 
        else {
            current = current->next;
            checker = checker->next;
        }
    }
    return true;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of L into stream.
// The overloaded << operator is just a convenience for streamlining the 
// process of outputting your class objects to various output 
//std::ostream is a C++ standard library class that represents an output stream.
std::ostream& operator<<(std::ostream& stream, const List & L ){
    return stream << L.to_string();
}

// operator==()
// Returns true if and only if A is the same integer sequence as B. The
// cursors in both Lists are unchanged.
bool operator==(const List& A, const List& B ){
    return A.equals(B);
}

// operator=()
// Overwrites the state of this List with state of L.
List& List::operator=( const List& L ){

    //checks if the current object (pointed to by the this pointer) 
    // is not the same as the address of the object L.
    if( this != &L ){
        // make a copy of L
        List temp = L;

        // then swap the copy's fields with fields of this
        std::swap(frontDummy, temp.frontDummy);
        std::swap(backDummy, temp.backDummy);
        std::swap(beforeCursor, temp.beforeCursor);
        std::swap(afterCursor, temp.afterCursor);
        std::swap(pos_cursor, temp.pos_cursor);
        std::swap(num_elements, temp.num_elements);
    }

    // return this with the new data installed
    return *this;

    // the copy temp, if there is one, is gonna be destructed and deleted by C++ compiler  
}

