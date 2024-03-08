// •    Anh Le // First and Last name
// •    mle288 // UCSC UserID
// •    2024 Winter CS101 PA6
// •    Arthimetic.cpp // FileName
// •    the User interface // Describe the program


#include<iostream>
#include<fstream>
#include<string>
#include"BigInteger.h"



using namespace std;


int main(int argc, char * argv[]){
    //Pre: check if the user used the correct usage
    ifstream in;
    ofstream out;

    // check command line for correct number of arguments
    if( argc != 3 ){
        cerr << "Usage ./Arithmetic <input file> <output file>" << '\n';
        return(EXIT_FAILURE);
    }

    // open files for reading and writing
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Can not open " << argv[1] << " for reading" << 'n';
        return(EXIT_FAILURE);
    }
    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Can not open " << argv[2] << " for writing" << '\n';
        return(EXIT_FAILURE);
    }

   //Get bigintegers A and B from input file
    string input;

    getline(in, input);
    BigInteger A(input); //get biginteger A

    getline(in, input); //blank line

    getline(in, input);
    BigInteger B(input); //get biginteger B


    // cout << A;
   //Perform calculation
    out << A << '\n' << '\n';
    out << B << '\n' << '\n';
    out << A + B << '\n' << '\n';
    out << A - B << '\n' << '\n';
    out << A - A << '\n' << '\n';

    BigInteger Tich_A = 3;
    BigInteger Tich_B = 2;
    out << A.mult(Tich_A) - B.mult(Tich_B) << '\n' << '\n';

    out << A * B << '\n' << '\n';
    out << A * A << '\n' << '\n';
    out << B * B << '\n' << '\n';

    BigInteger Tich_A_mu_4 = 9;
    BigInteger Tich_B_mu_5 = 16;
    out << (A * A * A * A).mult(Tich_A_mu_4) + (B * B * B * B * B).mult(Tich_B_mu_5) << '\n' << '\n';

    //Close files
    in.close();
    out.close();

    return(EXIT_SUCCESS);
}