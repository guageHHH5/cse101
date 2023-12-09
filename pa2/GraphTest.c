/****************************************************************************************
*  Eric Wang, twang173, Programming Assignment 2  
*  GraphClient.c
*  Test client for Graph ADT
*****************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"

int main(){
    //int n = 35;
    Graph A = newGraph(100);
    if (getSize(A) != 0)
        printf("1");
    addArc(A, 54, 1);
    addArc(A, 54, 2);
    addArc(A, 54, 3);
    addArc(A, 1, 54);
    addArc(A, 1, 55);
    if (getSize(A) != 5)
        printf("2");
    BFS(A, 67);
    if (getSize(A) != 5)
        printf("3");
    addArc(A, 55, 1);
    if (getSize(A) != 6)
        printf("4");
    printf("0\n");
    makeNull(A);

    for (uint8_t i = 1; i <= 100; i++)
        if (getParent(A, i) != NIL)
            printf("aaaababab1\n");
    addArc(A, 64, 4);
    addArc(A, 64, 3);
    addArc(A, 42, 2);
    addArc(A, 2, 64);
    addArc(A, 4, 2);
    addArc(A, 3, 42);
    BFS(A, 42);
    if (getParent(A, 42) != NIL)
        printf("aaaababab2\n");
    if (getParent(A, 2) != 42)
        printf("aaaababab3\n");
    if (getParent(A, 8) != NIL)
        printf("aaaababab4\n");
    printf("getParent\n");
    makeNull(A);
    for (uint8_t i = 1; i <= 100; i++)
        if (getDist(A, i) != INF)
            printf("test1");
    addArc(A, 64, 4);
    addArc(A, 64, 3);
    addArc(A, 42, 2);
    addArc(A, 2, 64);
    addArc(A, 4, 2);
    addArc(A, 3, 42);
    BFS(A, 64);
    if (getDist(A, 64) != 0)
        printf("test2\n");
    if (getDist(A, 2) != 2)
        printf("test3\n");
    BFS(A, 4);
    if (getDist(A, 42) != 4)
        printf("test4\n");
    if (getDist(A, 43) != INF)
        printf("test5\n");
    BFS(A, 99);
    if (getDist(A, 64) != INF)
        printf("test6\n");
    printf("getDist\n");
    freeGraph(&A);
    printf("bababooie\n");
    // 
}