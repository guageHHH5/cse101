/*
Eric Wang, twang173, Programming Assignment 6
*/

#include <iostream>
#include <string>
#include <stdexcept>

#include "List.h"

List::Node::Node(ListElement x){
    data = x;
    next = nullptr;
    prev = nullptr;
}

//newList()
List::List(){
    frontDummy = new Node(-5);
    backDummy = new Node(-5);

    frontDummy->prev = nullptr;
    frontDummy->next = backDummy;

    backDummy->prev = frontDummy;
    backDummy->next = nullptr;

    beforeCursor = frontDummy;
    afterCursor = backDummy;

    pos_cursor = 0;
    num_elements = 0;
}

//Copy Constructor
List::List(const List& L){
    //empty list
    frontDummy = new Node(-5);
    backDummy = new Node(-5);

    frontDummy->prev = nullptr;
    frontDummy->next = backDummy;

    backDummy->prev = frontDummy;
    backDummy->next = nullptr;

    beforeCursor = frontDummy;
    afterCursor = backDummy;

    pos_cursor = 0;
    num_elements = 0;

    //load new elements
    Node* N = L.frontDummy->next;
    while(N != L.backDummy){
        insertBefore(N->data);
        N = N->next;
    }
}

//Destructor
List::~List(){
    clear();
    delete(this->frontDummy);
    delete(this->backDummy);
}

int List::length()const{
    return(num_elements);
}

ListElement List::front()const{
    if(length() != 0){
        return(frontDummy->next->data);
    }
    //error
    else{
        throw std::length_error("empty List");
    }
}

ListElement List::back()const{
    if(length() != 0){
        return(backDummy->prev->data);
    }
    //error
    else{
        throw std::length_error("empty List");
    }
}

int List::position()const{
    return(pos_cursor);
}

ListElement List::peekNext()const{
    if(position() < length()){
        //throw std::range_error("empty List or bad position");
        return afterCursor->data;
    }
    //error
    else{
        throw std::range_error("empty List or bad position");
        exit(EXIT_FAILURE);
    }
}

ListElement List::peekPrev()const{
    if(length() == 0 || position() <= 0 || position() > length()){
        throw std::range_error("empty List or bad position");
        
    }
    //error
    else{
        return beforeCursor->data;
    }
}

void List::clear(){
    moveFront();
    while(num_elements != 0){
        eraseAfter();
    }
}

void List::moveFront(){
    pos_cursor = 0;
    beforeCursor = frontDummy;
    afterCursor = frontDummy->next;
}

void List::moveBack(){
    pos_cursor = num_elements;
    beforeCursor = backDummy->prev;
    afterCursor = backDummy;
}

ListElement List::moveNext(){
    if(position() < length()){
        beforeCursor = afterCursor;
        afterCursor = afterCursor->next;
        pos_cursor += 1;
        return beforeCursor->data;
    }
    //throw error
    else{
        throw std::range_error("empty List or bad position");
    }
}

ListElement List::movePrev(){
    if(position() != 0){
        beforeCursor = beforeCursor->prev;
        afterCursor = afterCursor ->prev;
        pos_cursor -= 1;
        return afterCursor->data;
    }
    //throw error
    else{
        throw std::range_error("empty List or bad position");
    }
}

void List::insertAfter(ListElement x){
    Node *N = new Node(x);
    N->next = afterCursor;
    afterCursor->prev = N;
    N->prev = beforeCursor;
    beforeCursor->next = N;

    afterCursor = N;
    num_elements += 1;
}

void List::insertBefore(ListElement x){
    Node *N = new Node(x);
    N->next = afterCursor;
    afterCursor->prev = N;
    N->prev = beforeCursor;
    beforeCursor->next = N;

    beforeCursor = N;
    num_elements += 1;
    pos_cursor += 1;
}

void List::setAfter(ListElement x){
    if(position() < length()){
        afterCursor->data = x;
    }
    //throw error
    else{
        throw std::range_error("empty List or bad position");
    }
}

void List::setBefore(ListElement x){
    if(position() > 0){
        beforeCursor->data = x;
    }
    //throw error
    else{
        throw std::range_error("empty List or bad position");
    }
}

void List::eraseAfter(){
    if(pos_cursor < num_elements){
        Node *N = afterCursor;

        beforeCursor->next = N->next;
        N->next->prev = beforeCursor;
        afterCursor = N->next;
        num_elements -= 1;
        delete N;
    }
    else{
        throw std::range_error("empty List or bad position");
    }
}

void List::eraseBefore(){
    if(position() != 0){
        Node *N = beforeCursor;

        afterCursor->prev = N->prev;
        N->prev->next = afterCursor;
        beforeCursor = N->prev;
        num_elements -= 1;
        pos_cursor -= 1;
        delete N;
    }
    else{
        throw std::range_error("empty List or bad position");
    }
}

int List::findNext(ListElement x){
    while(pos_cursor < num_elements){
        if(moveNext() == x){
            break;
        }
    }
    if(beforeCursor->data == x){
        return pos_cursor;
    }
    return -1;
}

int List::findPrev(ListElement x){
    while(position() > 0){
        if(movePrev() == x){
            break;
        }
    }
    if(afterCursor->data == x){
        return pos_cursor;
    }
    return -1;
}

void List::cleanup(){
    Node *N = this->frontDummy->next;
    Node *M;
    Node *X;

    int n_in = 1;
    int m_in = 1;

    while(N != nullptr && N->next != nullptr){
        M = N;
        m_in = n_in;
        while(M->next != backDummy){
            if(N->data != M->next->data){
                M = M->next;
                m_in++;
            }
            else{
                X = M->next;
                M->next->next->prev = M;
                M->next = M->next->next;

                if(m_in < position()){
                    if(X == beforeCursor){
                        beforeCursor = beforeCursor->prev;
                        pos_cursor--;
                    }
                    else if(X == afterCursor){
                        afterCursor = afterCursor->next;
                    }
                    else{
                        pos_cursor--;
                    }
                }
                if(X->next == backDummy){
                    backDummy->prev = M;
                    M->next = backDummy;
                    if(X == afterCursor){
                        afterCursor = backDummy;
                    }
                }
                num_elements--;
                delete X;
            }
        }
        N = N->next;
        n_in++;
    }
}

List List::concat(const List& L)const{
    List M = *this;
    M.moveBack();
    Node *N = L.frontDummy->next;
    while(N->next != nullptr)
    {
        if(N != backDummy){
            M.insertBefore(N->data);
            N = N->next;
        }
    }
    M.moveFront();
    return M;
}

std::string List::to_string()const{
    Node *N = nullptr;
    std::string s = "(";

    N = frontDummy->next;
    while(N != backDummy){
        if(N->next == backDummy){
            s += std::to_string(N->data);
        }
        else{
            s += std::to_string(N->data) + ", ";
        }
        N = N->next;
    }
    s += ")";
    return s;
}

bool List::equals(const List& R) const{
    bool equals = false;
    Node *N = this->frontDummy->next;
    Node *M = R.frontDummy->next;

    equals = (this->num_elements == R.num_elements);

    while(equals && N != nullptr){
        equals = (N->data == M->data);
        N = N->next;
        M = M->next;
    }
    return equals;
}

std::ostream& operator<< ( std::ostream& stream, const List& L ){
    return stream << L.List::to_string();
}

bool operator== ( const List& A, const List& B ){
    return A.List::equals(B);
}

List& List::operator=(const List& L){
    if(this != &L){
        List t = L;

        std::swap(frontDummy, t.frontDummy);
        std::swap(backDummy, t.backDummy);
        std::swap(beforeCursor, t.beforeCursor);
        std::swap(afterCursor, t.afterCursor);
        std::swap(pos_cursor, t.pos_cursor);
        std::swap(num_elements, t.num_elements);
    }

    return *this;
}