/*
Eric Wang, twang173, Programming Assignment 6
*/
#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include "List.h"
#include "BigInteger.h"
#include <cstring>

long base = 1000000000;
long power = 9;

void negateList(List& L);
void sumList(List& S, List A, List B, int sgn);
int normalizeList(List& L);
void shiftList(List& L, int p);
void scalarMultList(List& L, ListElement m);

// BigInteger()
// Constructor that creates a new BigInteger in the zero state: 
// signum=0, digits=().
BigInteger::BigInteger(){
    signum = 0;
}

// BigInteger()
// Constructor that creates a new BigInteger from the long value x.
BigInteger::BigInteger(long x){
    std::string s = std::to_string(x); // change long to string

    //using the same BigInteger::BigInteger(std::string s)
    if(s.length() == 0){
        exit(EXIT_FAILURE);
    }
    signum = 0;
    std::string tempStr;
    int size = s.length();
    
    if(s[0] == 45){
        signum = -1;
        int i = 1;
        while(i < size){
            tempStr = tempStr + s[i];
            i++;
        }
        s = tempStr;
        tempStr.clear();
        size--;
        if(s[0] == 43){
            signum = 1;
            int i = 1;
            while(i < size){
                tempStr = tempStr + s[i];
                i++;
            }
            s = tempStr;
            tempStr.clear();
            size--;
        }
    } else {
        signum = 1;
    }

    reverse(s.begin(), s.end());
    int i = 0;
    while(i < size){
        tempStr += s[i];
        if(((i + 1) % power) == 0){
            reverse(tempStr.begin(), tempStr.end());
            digits.insertAfter(std::stoi(tempStr));
            tempStr.clear();
        }
        i++;
    }
    if(size % power != 0){
        reverse(tempStr.begin(), tempStr.end());
        digits.insertAfter(std::stoi(tempStr));
        tempStr.clear();
    }
    normalizeList(digits);
    
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s){
    if(s.length() == 0){
        exit(EXIT_FAILURE);
    }
    signum = 0;
    std::string tempStr;
    int size = s.length();
    
    if(s[0] == 45){
        signum = -1;
        int i = 1;
        while(i < size){
            tempStr = tempStr + s[i];
            i++;
        }
        s = tempStr;
        tempStr.clear();
        size--;
        if(s[0] == 43){
            signum = 1;
            int i = 1;
            while(i < size){
                tempStr = tempStr + s[i];
                i++;
            }
            s = tempStr;
            tempStr.clear();
            size--;
        }
    } else {
        signum = 1;
    }

    reverse(s.begin(), s.end());
    int i = 0;
    while(i < size){
        tempStr += s[i];
        if(((i + 1) % power) == 0){
            reverse(tempStr.begin(), tempStr.end());
            digits.insertAfter(std::stoi(tempStr));
            tempStr.clear();
        }
        i++;
    }
    if(size % power != 0){
        reverse(tempStr.begin(), tempStr.end());
        digits.insertAfter(std::stoi(tempStr));
        tempStr.clear();
    }
    normalizeList(digits);
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N){
    signum = N.signum;
    digits = N.digits;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive, 
// negative or 0, respectively.
int BigInteger::sign() const{
    return(signum);
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const{
    BigInteger X; // create a new big int
    X.digits = digits;
    X.signum = signum;

    // 4 cases
    if(signum == 1 && N.signum == -1){
        return 1;
    } else if(signum == -1 && N.signum == 1){
        return -1;
    } else if(signum == 1 && N.signum == 1){
        X = X.sub(N);
    } else if(signum == -1 && N.signum == -1){
        BigInteger B = N;
        negateList(B.digits);
        X = X.add(B);
    }
    if(X.signum == 0){
        return 0;
    }
    if(X.signum != -1){
        return 1;
    } else {
        return -1;
    }
}


// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero(){
    digits.clear();
    signum = 0;
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of 
// this BigInteger positive <--> negative. 
void BigInteger::negate(){
    if(signum != 0){
        signum = -signum;
    }
}


// BigInteger Arithmetic operations ----------------------------------------

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const{
    List newL;
    BigInteger X;
    newL = digits;
    if(signum == -1){
        negateList(newL);
    }
    sumList(newL, newL, N.digits, N.signum);
    X.signum = normalizeList(newL);
    X.digits = newL;
    return X;
}

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const{
    List newL;
    BigInteger X;
    newL = digits;
    if(signum == -1){
        negateList(newL);
    }
    sumList(newL, newL, N.digits, -N.signum);
    X.signum = normalizeList(newL);
    X.digits = newL;
    return X;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const{
    BigInteger Product;
    List L = digits;
    List M = N.digits;
    BigInteger X;
    X.signum = 1;
    long num = 0;
    int count  = 0;
    M.moveBack();
    while(M.position() > 0){
        L = digits;
        num = M.peekPrev();
        shiftList(L, count);
        scalarMultList(L, num);
        List temp(L);
        X.digits = temp;
        Product = Product.add(X);
        count++;
        M.movePrev();
    }
    if(Product.digits.length() == 0){
        Product.signum = 0;
        return Product;
    }
    if((signum == -1 && N.signum == 1) || (signum == 1 && N.signum == -1)){
        Product.signum = -1;
    }

    return Product;
}


// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string 
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string(){
    std::string s;
    if(signum == -1){
        s += "-";
    }
    bool isFirst = true;
    digits.moveFront();
    while(digits.position() < digits.length()){
        if(digits.peekNext() == 0 && digits.length() == 1){
            s += "0";
            return s;
        }
        if(digits.peekNext() != 0){
            s += std::to_string(digits.peekNext());
        } else if (!isFirst && digits.peekNext() < (base / 10)){
            long n = digits.peekNext();
            int count = 0;
            while (n != 0){
                count++;
                n = n / 10;
            }
            int i = 0;
            while(i < (power - count)){
                s += "0";
                i++;
            }
            s += std::to_string(digits.peekNext());
        } else { // if digits.peekNext() == 0
            int i = 0;
            while(i < power){
                s += std::to_string(digits.peekNext());
                i++;
            }
        }
        isFirst = false;
        digits.moveNext();
    }
    return s;
}


// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ){
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ){
    int c = A.compare(B);
    if(c != 0){
        return false;
    }
    else{
        return true;
    }
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ){
    int c = A.compare(B);
    if(c != -1){
        return false;
    }
    else{
        return true;
    }
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ){
    int c = A.compare(B);
    if(c == -1 || c == 0){
        return true;
    }else{
        return false;
    }
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ){
    int c = A.compare(B);
    if(c != 1){
        return false;
    }
    else{
        return true;
    }
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ){
    int c = A.compare(B);
    if(c == 1 || c == 0){
        return true;
    }else{
        return false;
    }
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ){
    BigInteger S;
    S = A.add(B);
    return S;
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ){
    A = A.add(B);
    return A;
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ){
    BigInteger D;
    D = A.sub(B);
    return D;
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ){
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ){
    BigInteger P;
    P = A.mult(B);
    return P;
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ){
    A = A.mult(B);
    return A;
}

//List Helpers-----------------------------
void negateList(List& L){
    L.moveFront();
    while(L.position() < L.length()){
        long t;
        t = L.peekNext();
        t = -t;
        L.setAfter(t);
        L.moveNext();
    }
}

void sumList(List& S, List A, List B, int sgn){
    if(sgn == -1){
        negateList(B);
    }

    bool b = false;

    //List C, D;
    if(A.length() < B.length()){
        S = B;
        b = true;
    } else {
        S = A;
    }

    if(b){
        S.moveBack();
        A.moveBack();
        while(A.position() > 0){
            S.setBefore(S.peekPrev() + A.peekPrev());
            S.movePrev();
            A.movePrev();
        }
    } else {
        S.moveBack();
        B.moveBack();
        while(B.position() > 0){
            S.setBefore(S.peekPrev() + B.peekPrev());
            S.movePrev();
            B.movePrev();
        }

    }
}
void normalizeMult(List& l) {
    long carry = 0;
    ListElement x;
    l.moveBack();
    while (l.position() > 0) {
        x = l.movePrev();
        if (carry != 0) {
            x += carry;
            carry = 0;
        }

        if (x >= base) {
            carry = x / base;
            x %= base;
            l.setAfter(x);
        } else {
            l.setAfter(x);
        }
    }

    if (carry != 0) {
        l.moveFront();
        l.insertBefore(carry);
    }

    return;
}

int normalizeList(List& L){
    bool a = false; //for one positive
    bool b = false; //for first negative
    bool c = false; //for first
    bool d = true;  //for all zero
    if(L.length() == 0){
        return 0;
    }

    L.moveFront();
    while(L.position() < L.length()){
        if(c == false){
            if(L.peekNext() < 0){
                b = true;
            }
            c = true;
        }
        if(L.peekNext() > 0){
            a = true;
        }
        if(L.peekNext() != 0){
            d = false;
        }
        L.moveNext();
    }

    if(d){
        L.moveFront();
        while(L.peekNext() == 0 && L.length() > 1){
            L.eraseAfter();
        }
        return 0;
    }

    if(!a){
        L.moveFront();
        while(L.peekNext() == 0){
            L.eraseAfter();
        }
        negateList(L);
        return -1;
    }

    if(b){
        long fC = 0;
        long nC = 0;
        long temp = 0;
        L.moveBack();
        while(L.position() > 0){
            fC = nC;
            temp = L.peekPrev();
            if(temp > 0){
                nC = 1;
                temp = temp - base + fC;
                L.setBefore(temp);
            }
            if(temp <= 0){
                nC = 0;
                temp = temp + fC;
                L.setBefore(temp);
            }
            L.movePrev();
        }

        L.moveFront();
        if(L.peekNext() == 0){
            L.eraseAfter();
        }
        negateList(L);
        return -1;
    }

    //Last case (default case)
    long ntemp = 0;
    long nfC = 0;
    long nnC = 0;
    long numDigits = 0;
    long x = 0;
    L.moveBack();
    while(L.position() > 0){
        nfC = nnC;
        ntemp = L.peekPrev();
        x = ntemp;
        while(x != 0){
            x = x / 10;
            numDigits += 1;
        }
        if(numDigits > power){
            ntemp = ntemp + nfC;
            long counter = ntemp / base;
            nnC = counter;
            ntemp = ntemp - (base * counter);
            L.setBefore(ntemp);
            if(L.position() == 1){
                L.movePrev();
                L.insertBefore(nnC);
            }
        }
        else if(ntemp < 0){
            nnC = -1;
            ntemp = base + ntemp + nfC;
            L.setBefore(ntemp);
        } else {
            nnC = 0;
            ntemp = ntemp + nfC;
            L.setBefore(ntemp);
        }
        numDigits = 0;
        L.movePrev();
    }

    L.moveFront();
    if(L.peekNext() == 0){
        while(L.peekNext() == 0 && L.length() > 1){
            L.eraseAfter();
        }
    }
    return 1;
}

void shiftList(List& L, int p){
    int i = 0;
    while(i < p){
        L.moveBack();
        L.insertAfter(0);
        i++;
    }
}

void scalarMultList(List& L, ListElement m){
    long t;
    L.moveBack();
    while(L.position() > 0){
        t = L.peekPrev();
        L.setBefore(m*t);
        L.movePrev();
    }
}

