/*
Eric Wang, twang173, Programming Assignment 4
*/

#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"

int main() {
    int n = 3;
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    changeEntry(A, 1, 1, 4);
    changeEntry(A, 1, 2, 2);
    changeEntry(A, 1, 3, 0);
    changeEntry(A, 2, 1, 2);
    changeEntry(A, 3, 1, 0);
    changeEntry(A, 2, 2, 2);
    changeEntry(A, 3, 3, 0);
    if (size(A) != 10){
        printf("1");
    }else{
        printf("0");
    }
    if (NNZ(A) != 0){
        printf("1");
    }else{
        printf("0");
    }
    changeEntry(B, 1, 1, 1);
    changeEntry(B, 1, 3, 1);

    changeEntry(B, 3, 1, 1);
    changeEntry(B, 3, 3, 1);

    printf("Matrix B: %d NNZ\n", NNZ(B));
    printMatrix(stdout, B);
    printf("\n");

    Matrix C = sum(A, B);
    printf("A + B\n");
    printMatrix(stdout, C);
    printf("\n");

    Matrix D = diff(A, B);
    printf("A - B\n");
    printMatrix(stdout, D);
    printf("\n");

    Matrix E = transpose(A);
    printf("transpose A\n");
    printMatrix(stdout, E);
    printf("\n");

    Matrix F = transpose(B);
    printf("transpose B\n");
    printMatrix(stdout, F);
    printf("\n");

    Matrix G = product(A, B);
    printf("A * B\n");
    printMatrix(stdout, G);
    printf("\n");

    Matrix H = scalarMult(2, A);
    printf("2 * A\n");
    printMatrix(stdout, H);
    printf("\n");

    Matrix I = scalarMult(500, B);
    printf("500 * B\n");
    printMatrix(stdout, I);
    printf("\n");

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    return 0;
}