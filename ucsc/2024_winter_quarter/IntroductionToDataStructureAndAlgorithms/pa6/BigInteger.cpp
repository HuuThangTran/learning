//    Anh Le // First and Last name
//    mle288 // UCSC UserID
//    2024 Winter CS101 PA6
//    BigInterger.cpp // FileName
//    the black box contain the main logic for this ADT type // Describe the program




#include<iostream>
#include<string>
#include <cmath>
#include <stdexcept>
#include <cctype>
#include"BigInteger.h"
#include"List.h"

using namespace std;


// BASE = 10^pow; 0<= pow <= 9
#define BASE 1000000000
#define POWER 9



// -----Helper function 
// Remove leading zeros
void rmLeadZero( List* list) {
    list->moveFront();
    while (list->length() > 0 && list->peekNext() == 0) {
        list->eraseAfter();
    }
}



// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger() {
    this-> signum = 0;
    this-> digits = List(); 
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x) {
    
    
    // zero
    if (x == 0) {
        this->signum = 0;
        digits.insertAfter(0);
        return;
    }

    // negative numbers
    if (x < 0) {
        this->signum = -1;
        x = -x;
    } else {
        this->signum = 1;
    }

    // extracting digits
    while (x > 0) {
        this->digits.insertBefore(x % BASE);
        x /= BASE;
    }
}


// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) BASE 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
/*
The constructor from string
BigInteger(std::string s);
will create a BigInteger object representing the integer specified by s. The string s 
will begin with an optional sign ('+' or '-'), followed by decimal digit 
characters {0, 1, 2, 3, 4, 5, 6, 7, 8, 9}. If this constructor
is called on a non-empty string that cannot be parsed as a signed integer, it will throw an
invalid_argument exception (from the standard library <stdexcept> with the error message:
"BigInteger: Constructor: non-numeric string"
If called on an empty string, it will throw an invalid_argument exception with the error message
"BigInteger: Constructor: empty string"
*/BigInteger::BigInteger(std::string s) {
    
    
    // required
    if (!s.length()) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }


    int offset = 0;
    if ((s[0] == '+') | (s[0] == '-')) {
        signum = 1;
        if (s[0] == '-') {
            signum = -1;
        }
        offset = 1;
        s = s.substr(offset, s.length() - 1);
    } else {
        signum = 1;
    }


    for (long unsigned int i = 0; i < s.length();) {
        if (!std::isdigit(s[i])) {
            throw std::invalid_argument("BigInt Constructor is non-numeric");
        }
        i = i + 1;
    }



    std::string numString = "";
    List L;
    size_t max = 0;
    size_t currentDigits = s.length();
    // Divide the input string into chunks of POWER digits and convert each chunk to a number
    while (max < s.length() / POWER) {
        numString = s.substr(currentDigits - POWER, POWER);
        digits.insertAfter(std::stol(numString, nullptr, 10));
        currentDigits = currentDigits - POWER;
        max++;
    }


    // convert the remain digits and and insert them
    if (currentDigits > 0) {
        numString = s.substr(0, currentDigits);
        digits.insertAfter(std::stol(numString, nullptr, 10));
    }

    rmLeadZero(&digits);  
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
    this->signum = N.signum;
    this->digits = N.digits;
}


    // Optional Destuctor
    // ~BigInteger()
    // ~BigInteger();

// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const {
    return this->signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
    
    // compare signs
    if (this->signum > N.signum) {
        return 1;
    }
    else if (this->signum < N.signum) {
        return -1;
    }
    else if (this->signum == 0 && N.signum == 0) {
        return 0;
    }


    // Same sign, check length
    const List& A = this->digits;
    const List& B = N.digits;
    int length = A.length();

    if (length != B.length()) {
        // different length, the longer 
        return (length > B.length()) ? this->signum : -N.signum;
    }



    // Create copies of A and B to avoid modifying the originals
    List digitsA = A;
    List digitsB = B;


    // Move cursors to the front of the lists
    digitsA.moveFront();
    digitsB.moveFront();
    // xompare digits element by element when same sign same length
    for (int i = 0; i < length; ++i) {


        if (digitsA.peekNext() > digitsB.peekNext()) {
            // digit in A is larger, so A is larger overall
            return this->signum;
        }
        else if (digitsA.peekNext() < digitsB.peekNext()) {
            // digit in B is larger, so B is larger overall
            return -N.signum;
        }

        // move cursors to the next element
        digitsA.moveNext();
        digitsB.moveNext();
    }


    // auto return 0 if all different case fail  digits are equal
    return 0;
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    this->signum = 0;
    this->digits.clear();
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate() {
    this->signum *= -1;
}


// BigInteger Arithmetic operations---------------------------------------------------------------------------------------------------------
// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
  
  
    BigInteger X = *this;
    BigInteger Y = N;
    BigInteger result_add;



    // Handle cases where signs differ
    if (X.sign() > 0 && Y.sign() < 0) {
        Y.negate();
        return X.sub(Y);
   
    } else if (X.sign() < 0 && Y.sign() < 0) {
        X.negate();
        Y.negate();
        result_add= X.add(Y);
        result_add.negate();
        return result_add;
    }

    else if (X.sign() < 0 && Y.sign() > 0) {
        X.negate();
        return Y.sub(X);
    }
    
    // Ensure X is the smaller BigInteger
    if (X > Y) {
        return Y.add(X);
    }

    List x = X.digits;
    List y = Y.digits;
    List result = result_add.digits;

    long keria = 0;
    long temp = 0;

    // Perform addition digit by digit
    x.moveBack();
    y.moveBack();
    while (x.position() > 0 && y.position() > 0) {
        temp = keria + x.peekPrev() + y.peekPrev();
        keria = temp / BASE;
        temp %= BASE;
        result.insertAfter(temp);
        x.movePrev();
        y.movePrev();
    }

    // Handle remaining digits of Y
    while (y.position() > 0) {
        temp = keria + y.peekPrev();
        keria = temp / BASE;
        temp %= BASE;
        result.insertAfter(temp);
        y.movePrev();
    }

    // If there is a final keria, insert it
    if (keria > 0) {
        result.insertAfter(keria);
    }

    result_add.signum = 1;
    result_add.digits = result;
    return result_add;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {


    BigInteger Y = *this;
    BigInteger X = N;
    BigInteger result_sub;
    List x = X.digits;
    List y = Y.digits;
    List result = result_sub.digits;

    // Check for different cases
    
    if (X.sign() > 0 && Y.sign() < 0) {
        X.negate();
        result_sub = X.add(Y);
        return result_sub;  // Return (X + (-Y)) if X is positive and Y is negative
    }
    
    if (X.sign() && !Y.sign()) {
        X.negate();
        return X;  // Return negation of X if X is positive and Y is negative
    }
    
    if (X < Y) {
        result_sub = X.sub(Y);
        result_sub.negate();
        return result_sub;  // Return negation of (X - B) if X is less than B
    }
    
    if (X.sign() < 0 && Y.sign() < 0) {
        X.negate();
        Y.negate();
        result_sub = Y.sub(X);
        result_sub.negate();
        return result_sub;  // Return (Y - X) negated if both X and Y are negative
    }
    
    if (X == Y) {
        return result_sub;  // Return zero if X and Y are equal
    }
    
    if (X.sign() < 0 && Y.sign() > 0) {
        Y.negate();
        result_sub = X.add(Y);
        result_sub.negate();
        return result_sub;  // Return (X + (-Y)) negated
    }
    
    if (!X.sign() && Y.sign()) {
        return Y;  // Return Y if X is negative and Y is positive
    }
    

    // Perform digit-by-digit subtraction
    x.moveBack();
    y.moveBack();
    long distance = 0;
    long doge = 0;
    int i = y.position();
    while (!(i <= 0)) {
        if (x.peekPrev() - distance < y.peekPrev()) {
            doge = x.peekPrev() + BASE - y.peekPrev() - distance;
            distance = 1;
        } else {
            doge = x.peekPrev() - distance - y.peekPrev();
            if (!(x.peekPrev() <= 0)) {
                distance = 0;
            }
        }
        result.insertAfter(doge);
        x.movePrev();
        y.movePrev();
        i--;
    }


    while (x.position() > 0) {
        if (x.peekPrev() - distance < 0) {
            doge = x.peekPrev() + BASE - 0 - distance;
            distance = 1;
        } else {
            doge = x.peekPrev() - distance - 0;
            if (!(x.peekPrev() <= 0)) {
                distance = 0;
            }
        }
        result.insertAfter(doge);
        x.movePrev();
    }
    

    result_sub.digits = result;
    rmLeadZero(&(result_sub.digits));  // Remove leading zeros from the result
    result_sub.signum = -1;  // Set the sign of the result to negative
    return result_sub;
}



//Helper function
List tempMult(long longNum, List *list, int* current) {
    
    List L;
    long keria = 0;
    long tempo = 0;


    for (list->moveBack(); list->position() > 0; list->movePrev()) {
        tempo = (list->peekPrev() * longNum) + keria ;
        keria  = tempo/ BASE;
        tempo %= BASE;
        L.insertAfter(tempo);
    }

    if (keria > 0) {

        L.insertAfter(keria );
    }

    L.moveBack();

    for (int i = 0; i < *current; i++) {
        L.insertAfter(0);
    }
    return L;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const {

    
    BigInteger B = *this;
    BigInteger A = N;
    BigInteger C;
    List digitsA = A.digits;
    List digitsB = B.digits;
    int control = 0;
    digitsA.moveBack();
    digitsB.moveBack();

    int aPos = digitsA .position();


    //A x B and accumulate in C
    for (int i = aPos; i > 0; i--) {

        List tempList = tempMult(digitsA.peekPrev(), &digitsB, &control);  
        BigInteger T;
        T.signum = 1;
        T.digits = tempList;
        C = C.add(T);  
        digitsA .movePrev();  
        control++;
    }

    //sign of the result
    C.signum = A.signum * B.signum;  
    return C;
}



// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// BASE 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.

string BigInteger::to_string() {
    string result = "";

        if(signum == -1){
            result += "-";
        }
        
     else if (this->signum == 0) {
        return "0";
    }

    digits.moveFront();
    // Remove leading zeros from the digits list
    while (digits.length() > 1 && digits.front() == 0 ) {
        digits.eraseAfter();
    }
    
    for (digits.moveFront(); digits.position() < digits.length(); digits.moveNext()) {
        string X = std::to_string(digits.peekNext());
        string Y = "";
        // Pad the number with zeros to ensure each chunk has POWER digits
        while (digits.position() != 0 && (int)(Y.length() + X.length()) < POWER ) {
            Y += '0';
        }
        result += (Y + X);  // Concatenate the padded chunk with the output string
    }
    return result;
}



// Overriden Operators --------------------------------------------------------------------------------------------------------------




// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream<<N.BigInteger::to_string();
}





// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return (i == 0) ? true : false;
}



// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return (i == -1) ? true : false;
}



// operator<=()
// Returns true if and only if A is less than or equal to B. 

bool operator<=( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return ((i == 0) || (i == -1)) ? true : false;
}



// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return (i == 1) ? true : false;
}



// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return ((i == 0) || (i == 1)) ? true : false;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    BigInteger I = A.add(B);
    A.digits = I.digits;
    A.signum = I.signum;
    return A; 
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    BigInteger I = A.sub(B);
    A.digits = I.digits;
    A.signum = I.signum;
    return A; 
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.mult(B);
}
// dung file

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    BigInteger I = A.mult(B);
    A.digits = I.digits;
    A.signum = I.signum;
    return A; 
}
