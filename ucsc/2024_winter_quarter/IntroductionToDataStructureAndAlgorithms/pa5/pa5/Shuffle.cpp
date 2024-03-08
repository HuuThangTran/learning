/*
•    Anh Le // First and Last name
•    mle288 // UCSC UserID
•    2024 Winter CS101 PA5
•    Shuffle.cpp// FileName
•    The user interface for List.h and List.cpp, actively doing the shuffling function// Describe the program
*/

#include"List.h"

using namespace std;

// This function alter its List& (List reference) argument D
// by performing one shuffle operation, as described in pa5.pdf.
void shuffle(List& D);
void printHead();

int main(int argc, char * argv[]){

    /*
    ===================================================
    1/ check for cmd aruguments
    a/ correct number
    b/ as a number not char/string
    ===================================================
    */

    // check the correct number of command line argument
    if( argc != 2 ){
        cerr << "Usage ./Shuffle <deck size>" << endl;
        return(EXIT_FAILURE);
    }

    // check each "charactter" input in the command line argument as number
    std::string checkerArray = argv[1];
    for( char c : checkerArray) {
        if(isdigit(c) == 0) {
            cerr << "Error: <decksize> must be a positive integer" << endl;
            return(EXIT_FAILURE);
        }
    }
  

    /*
    ===================================================
    2/ print the result to the terminal
    ===================================================
    */
    printHead();
    
    int deck = std::stoi(argv[1]);

    // creating an empty List in the default contrusctor state
    List originalList;
    for(int i = 1; i <= deck; i++){

        // winsert the data to originalList.
        originalList.insertBefore(i-1);

        // copy List to compare with the orginal List
        List copyList(originalList);

        // shuffle the coppyList till it is the same with the original list
        int count = 0;
        do{
            shuffle(copyList);

            // record shuffle count and print them out
            count ++;
        }while(! copyList.equals(originalList));

        // the size with the suffer count
        cout << i << "\t\t" << count << "\n";
    }
    
    return(EXIT_SUCCESS);
}


void printHead() {
    cout << "deck size       shuffle count" << "\n";
    cout << "------------------------------" << "\n";
}

void shuffle(List& split2){
    

    /*
    ===================================================
    Spliting
    ===================================================
    */
    // creating a temp list
    List split1;
    split2.moveFront();
    // having the split int , if even => two equal halves, if odds we place the extra on right half
    int split = (split2.length())/2;
    
    for(int i = 0; i < split; i++){
        int data = split2.moveNext();
        split1.insertBefore(data);
        split2.eraseBefore();
    }
    // cerr << "split1:" << split1 << endl;
    // cerr << "split2:" << split2 << endl;


    /*
    ===================================================
    Merging
    ===================================================
    */
    split1.moveFront();
    while(split2.position() < split2.length()){

        // move from dummy position
        split2.moveNext();

        //merge
        if(split1.position() < split1.length()){
            split2.insertAfter(split1.moveNext());
            split2.moveNext();
        }
    }
    // cerr << "split2 after merge:" << split2 << endl;
}


