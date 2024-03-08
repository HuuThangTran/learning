// •    Anh Le // First and Last name
// •    mle288 // UCSC UserID
// •    2024 Winter CS101 PA6
// •    BigIntergerTest // FileName
// •    Testing the code for BiginteGerfile // Describe the program

#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main(){
    
    string s1 = "91287346671234543892345634563400005619187236478";
    string s2 = "98765454390000003456345600098475602000034565430000000006543654365346534";
    string s3 = "9876545439000003456345619187236345634561918723486906456345756780000065436543";
    
    //BigInteger N;
    BigInteger X = BigInteger(s1);
    BigInteger Y = BigInteger(s2);
    BigInteger Z = BigInteger(s3);
    
    cout << endl;
    
    cout << "X = " << X << endl;
    cout << "Y = " << Y << endl;
    cout << "Z = " << Z << endl;
    cout << endl;
    
    BigInteger D = X+Y;
    BigInteger E = Y+X;
    BigInteger F = D-E;
    BigInteger G = 198736*X + 2847632*Y + 1987272*Z;
    BigInteger H = X*Y;
    BigInteger I = Y*X;
    
    cout << "(X==Y) = " << ((X==Y)?"True":"False") << endl;
    cout << "(X<Y)  = " << ((X<Y)? "True":"False") << endl;
    cout << "(X<=Y) = " << ((X<=Y)?"True":"False") << endl;
    cout << "(X>Y)  = " << ((X>Y)? "True":"False") << endl;
    cout << "(X>=Y) = " << ((X>=Y)?"True":"False") << endl << endl;
    
    cout << "D = " << D << endl;
    cout << "E = " << E << endl;
    cout << "(D==E) = " << ((D==E)?"True":"False") << endl;
    cout << "F = " << F << endl;
    cout << "G = " << G << endl;
    cout << "H = " << H << endl;
    cout << "I = " << I << endl;
    cout << "(H==I) = " << ((H==I)?"True":"False") << endl;
    
    cout << endl;
    
    X += Y;
    Y -= Z;
    
    cout << "A = " << X << endl;
    cout << "B = " << Y << endl;
    cout << endl;
    cout << endl;
    
    return EXIT_SUCCESS;
}