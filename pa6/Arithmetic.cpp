/*
Eric Wang, twang173, Programming Assignment 5
*/
#include <iostream>
#include <stdexcept>
#include <fstream>
#include "BigInteger.h"

#define MAX_LEN 300

using namespace std;

int main(int argc, char *argv[]){

    ifstream i;
    ofstream o;
    string s;

    if(argc != 3){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    i.open(argv[1]);
    if(i.is_open() == false){
        cerr << "Can't open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    o.open(argv[2]);
    if(o.is_open() == false){
        cerr << "Can't open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    // Scan for lines
    getline(i, s);
    BigInteger A = BigInteger(s);
    getline(i, s);
    getline(i, s);
    BigInteger B = BigInteger(s);

    BigInteger C = BigInteger("9");
    BigInteger D = BigInteger("16");

    o << A << "\n" << endl;
    o << B << "\n" << endl;
    o << A+B << "\n" << endl;
    o << A-B << "\n" << endl;
    o << A-A << "\n" << endl;
    o << (A+A+A)-(B+B) << "\n" << endl;
    o << A*B << "\n" << endl;
    BigInteger E = A*A;
    o << E << "\n" << endl;
    BigInteger F = B*B;
    o << F << "\n" << endl;
    o << C*(E*E) + D*((F*F)*B) << "\n" << endl;
    return 0;     
}