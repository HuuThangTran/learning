// Anh Le // First and Last name
// mle288 // UCSC UserID
// 2024 Winter CS101 PA7
// Order.cpp // FileName
// the userclient interface file which have the main logic postO, inO, preO for binary tree // Describe the program

#include <fstream>
#include "Dictionary.h"

using namespace std;




int main(int argc, char* argv[]) {

    ifstream in;
    ofstream out;

    // check command line for correct number of arguments
    if (argc != 3) {
        cerr << "Usage ./Order <input file> <output file>" << '\n';
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

    Dictionary D;

    std::string key = "";
    int value = 1;

    // set value into dictionary D
    while (std::getline(in, key)) {
        D.setValue(key, value);
        value++;
    }

    // output content
    // string of post order
    out << D.to_string() << std::endl;
    // string of pre order
    out << D.pre_string() << std::endl;

    D.clear();

    // close files
    in.close();
    out.close();

    return (EXIT_SUCCESS);
}