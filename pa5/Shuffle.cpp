/*
Eric Wang, twang173, Programming Assignment 5
*/

#include <iostream>
#include <fstream>
#include <iomanip>

#include "List.h"

using namespace std;

void shuffle(List &D){
    int n = D.length() / 2;
    int m = D.length() - n;

    List L = D;

    D.moveFront();
    L.moveFront();

    int i, j, k;

    i = 0;
    while(i < n){
        L.moveNext();
        i++;
    }

    j = 0;
    while(j < m){
        D.insertBefore(L.moveNext());
        D.moveNext();
        j++;
    }

    D.moveBack();
    k = 0;
    while(k < m){
        D.eraseBefore();
        k++;
    }
}

int main(int argc, char* argv[]){
    if(argc != 2){
        cerr << "Usage: " << argv[0] << " number" << endl;
        return EXIT_FAILURE;
    }
    int i = stoi(argv[1]);
    List L;

    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;

    int j = 0;
    while(j < i){
        int z = 0;
        L.moveBack();
        L.insertBefore(j);

        List M = L;

        do{
            shuffle(L);
            z++;
        }while(L.equals(M) == false);

        cout << " " << setw(16) << left << j + 1 << setw(16) << left << z << endl;
        j++;
    }
    return 0;
}