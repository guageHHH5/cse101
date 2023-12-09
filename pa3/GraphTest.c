/****************************************************************************************
*  Eric Wang, twang173, Programming Assignment 3  
*  GraphTest.c
*  Test client for Graph ADT
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"

int main(){
    //int n = 35;
    Graph A = newGraph(100);
    List L = newList();
    if (getSize(A) != 0)
        printf("1");
    addArc(A, 54, 1);
    addArc(A, 54, 2);
    addArc(A, 54, 2);
    addArc(A, 54, 3);
    addArc(A, 1, 54);
    addArc(A, 1, 54);
    addArc(A, 1, 55);
    addArc(A, 1, 55);
    if (getSize(A) != 5)
        printf("2");
    
    for(uint8_t i = 1; i <= 100; i++){
        append(L, i);
    }
    DFS(A, L);
    if (getSize(A) != 5)
        printf("3");
    addArc(A, 55, 1);
    if (getSize(A) != 6)
        printf("4");
    printf("0\n");
    freeGraph(&A);
    freeList(&L);

    Graph B = newGraph(100);
    List M = newList();
    for (uint8_t i = 1; i <= 100; i++)
        if (getParent(B, i) != NIL)
            printf("aaaababab1\n");
    addArc(A, 64, 4);
    addArc(A, 64, 3);
    addArc(A, 42, 2);
    addArc(A, 2, 64);
    addArc(A, 4, 2);
    addArc(A, 3, 42);
    for(uint8_t i = 1; i <= 100; i++){
        append(M, i);
    }
    DFS(B, M);
    if (getParent(B, 100) != NIL)
        printf("aaaababab2\n");
    if (getParent(B, 2) != NIL)
        printf("aaaababab3\n");
    if (getParent(B, 42) != 3)
        printf("aaaababab4\n");
    if (getParent(B, 3) != 64)
        printf("aaaababab5\n");
    if (getParent(B, 4) != 2)
        printf("aaaababab6\n");
    printf("getParent\n");
    //makeNull(A);
    freeGraph(&B);
    freeList(&M);

    Graph C = newGraph(100);
    List N = newList();
    for (uint8_t i = 1; i <= 100; i++)
        if (getDiscover(C, i) != UNDEF)
            printf("1");
    addArc(C, 64, 4);
    addArc(C, 64, 3);
    addArc(C, 42, 2);
    addArc(C, 2, 64);
    addArc(C, 4, 2);
    addArc(C, 3, 42);
    for(uint8_t i = 1; i <= 100; i++){
        prepend(N, i);
    }
    DFS(C, N);
    if (getDiscover(C, 100) != 1)
        printf("test2\n");
    if (getDiscover(C, 64) != 73)
        printf("test3\n");
    if (getDiscover(C, 4) != 80)
        printf("test4\n");
    DFS(C,N);
    if (getDiscover(C, 4) != 126)
        printf("test5\n");
    if (getDiscover(C, 63) != 117)
        printf("test6\n");
    DFS(C,N);
    if (getDiscover(C, 65) != 71)
        printf("test7\n");
    if (getDiscover(C, 1) != 199)
        printf("test9\n");
    printf("getDiscover\n");
    freeGraph(&C);
    freeList(&N);
    printf("bababooie\n");
    // 
}