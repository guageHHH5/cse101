/*
Eric Wang, twang173, Programming Assignment 7
*/
#include <iostream>
#include <string>
#include <fstream>
#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]){
    ifstream i;
    ofstream o;
    string s;

    if(argc != 3){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }

    i.open(argv[1]);
    if(!i.is_open()){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    o.open(argv[2]);
    if(!o.is_open()){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }

    Dictionary D;
    int count = 0;
    while(getline(i, s)){
        count += 1;
        D.setValue(s, count);
    }
    o << D << endl;
    o << D.pre_string() << endl;

    i.close();
    o.close();
    return 0;
}