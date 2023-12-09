/*
Eric Wang, twang173, Programming Assignment 6
*/

#include <iostream>
#include <string>
#include <stdexcept>

#include "List.h"

using namespace std;

int main(){
    int i = 1, n = 10;
    List L, M, N, O;

    if (L.length() != 0){
        return 1;
    }
    return 0;

    while(i <= n){
        L.insertAfter(i);
        M.insertAfter(11-i);
        N.insertBefore(i);
        O.insertBefore(11-i);
        i++;
    }

    cout << "A.length() = " << L.length() << endl;
    cout << "A.front() = " << L.front() << endl;
    cout << "A.back() = " << L.back() << endl;
    L.moveBack();
    cout << "A.movePrev() = " << L.movePrev() << endl;
    cout << "A.peekPrev() = " << L.peekPrev() << endl;

    cout << endl;
    cout << "A = " << L << endl;
    cout << "A.position() = " << L.position() << endl;
    cout << "B = " << M << endl;
    cout << "B.position() = " << M.position() << endl;
    cout << "C = " << N << endl;
    cout << "C.position() = " << N.position() << endl;
    cout << "D = " << O << endl;
    cout << "D.position() = " << O.position() << endl;
    cout << endl;

    L.moveBack();
    M.moveBack();
    N.moveFront();
    O.moveFront();

    cout << "A = " << L << endl;
    cout << "A.position() = " << L.position() << endl;
    cout << "B = " << M << endl;
    cout << "B.position() = " << M.position() << endl;
    cout << "C = " << N << endl;
    cout << "C.position() = " << N.position() << endl;
    cout << "D = " << O << endl;
    cout << "D.position() = " << O.position() << endl;

    cout << endl << "B: ";
    int j = 1;
    while(j <= 7){
        cout << M.movePrev() << " ";
        j++;
    }
    cout << endl << "B.position() = " << M.position() << endl;
   
    cout << endl << "C: ";

    int k = 1;
    while(k <= 7){
        cout << N.moveNext() << " ";
        k++;
    }
    cout << endl << "C.position() = " << N.position() << endl;

    cout << endl;
    cout << "A==B is " << (L==M?"true":"false") << endl;
    cout << "B==C is " << (M==N?"true":"false") << endl;
    cout << "C==D is " << (N==O?"true":"false") << endl;
    cout << "D==A is " << (O==L?"true":"false") << endl;
    cout << endl;

    cout << M.findNext(5) << endl;
    cout << M << endl;
    M.eraseBefore();
    M.eraseAfter();
    cout << M << endl;
    cout << M.position() << endl;
    cout << M.findPrev(2) << endl;
    M.eraseBefore();
    M.eraseAfter();
    cout << M << endl;
    cout << M.position() << endl; 
    cout << M.findNext(20) << endl; 
    cout << M.position() << endl;
    cout << M.findPrev(20) << endl;
    cout << M.position() << endl;
    cout << endl;

    for(i = 10; i >= 1; i--){
        L.insertAfter(i);
        L.movePrev();
    }
    cout << "A = " << L << endl;
    for(i = 1; i <= 15; i++){
        L.moveNext();
    }
    cout << L.position() << endl;
    L.cleanup();
    cout << "A = " << L << endl;
    cout << "A.position() = " << L.position() << endl;
    cout << "A.length() = " << L.length() << endl;
    cout << "A.front() = " << L.front() << endl;
    cout << "A.back() = " << L.back() << endl;

    List E = L;
    cout << "E==A is " << (E == L ? "true":"false") << endl;

    cout << endl;

    List F = L.concat(M);
    cout << "F = " << F << endl;
    cout << "length: " << F.length() << endl;
    cout << "front: " << F.front() << endl;
    cout << "back: " << F.back() << endl;
    cout << "position: " << F.position() << endl;
    for(i = 1; i <= 7; i++){
        cout << "peekNext: " << F.peekNext() << endl;
        F.insertBefore(-i);
        cout << F.moveNext() << endl; 
    }
    cout << "F = " << F << endl;

    cout << endl;

    cout << "test exceptions: " << endl;
    cout << "A = " << L << endl;
    L.moveFront();
    cout << "A.position() = " << L.position() << endl;
    cout << "A.length() = " << L.length() << endl;
    cout << "A.front() = " << L.front() << endl;
    cout << "A.back() = " << L.back() << endl;

    cout << endl;

    return( EXIT_SUCCESS );
}
