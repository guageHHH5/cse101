/*
Eric Wang, twang173, Programming Assignment 1
*/
/****************************************************************************************
*  ListTest.c
*  Test client for List ADT
*****************************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
    printf("Prepend, append\nPrint test 1:\n");
    List C = newList();
    List D = newList();
    for(int i=1; i<=20; i++){
        append(C,i);
        prepend(D,i);
    }
    printList(stdout,C); 
    printf("\nPrint test 2:\n");
    printList(stdout,D); 
    printf("\nPrepend, Moveback, equals\n");
    //
    freeList(&C);
    freeList(&D);
    //
    List A = newList();
    List B = newList();
    prepend(A, 1);
    prepend(B, 1);
    prepend(A, 2);
    prepend(B, 2);
    //printf("hi\n");
    moveBack(A);
    //printf("index: %d\n", index(A));
    delete(A);
    if (!equals(A, B)) {
        printf("Delete Test 1 passed\n");
    }
    moveBack(B);
    delete(B);
    if (equals(A, B)){
        printf("Delete Test 2 passed\n");
    }
    append(A, 3);
    append(B, 3);
    moveBack(A);
    delete (A);
    moveBack(B);
    delete(B);
    if (equals(A, B)){
        printf("Delete Test 3 passed\n");
    }
    //
    List E = copyList(A);
    printf("%s\n", equals(A,B)?"true":"false");
    printf("%s\n", equals(B,E)?"true":"false");
    printf("%s\n", equals(E,A)?"true":"false");
    //
    //
    moveFront(A);
    for(int i=0; i<5; i++) moveNext(A); // at index 5
    insertBefore(A, -1);            // at index 6
    for(int i=0; i<9; i++) moveNext(A); // at index 15
    insertAfter(A, -2);
    for(int i=0; i<5; i++) movePrev(A); // at index 10
    delete(A);
    printList(stdout,A);
    printf("\n");
    printf("%d\n", length(A));
    clear(A);
    printf("%d\n", length(A));
    //
    freeList(&A);
    freeList(&B);
    freeList(&E);
    return(0);
}