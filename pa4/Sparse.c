/*
Eric Wang, twang173, Programming Assignment 4
*/

#include <stdio.h>
#include <stdlib.h>

#include "Matrix.h"

int main(int argc, char *argv[]){
    if(argc != 3){ //arg check
        printf("%s <infile> <outfile>\n", argv[0]);
        exit(1);
    }

    FILE *in = fopen(argv[1], "r"); // read infile
    if(in == NULL){
        printf("Can't open file %s for reading\n", argv[1]);
        exit(1);
    }

    FILE *out = fopen(argv[2], "w"); // write outfile
    if(out == NULL){
        printf("Can't open file %s for writing\n", argv[2]);
        exit(1);
    }

    // n: size of n x n Matrix
    // nnz1: nnz for Matrix 1/A
    // nnz2: nnz for Matrix 2/B
    int n, nnz1, nnz2;

    fscanf(in, "%d %d %d\n\n", &n, &nnz1, &nnz2);

    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    int a, b;
    double c;

    int i = 1;
    while(i <= nnz1){
        if(i == nnz1){
            fscanf(in, "%d %d %lf\n\n", &a, &b, &c);
            changeEntry(A, a, b, c);
        } else{
            fscanf(in, "%d %d %lf\n", &a, &b, &c);
            changeEntry(A, a, b, c);
        }
        i++;
    }

    int j = 1;
    while(j <= nnz2){
        fscanf(in, "%d %d %lf\n", &a, &b, &c);
        changeEntry(B, a, b, c);
        j++;
    }

    fprintf(out, "A has %d non-zero entries:\n", nnz1);
    printMatrix(out, A);
    fprintf(out, "\n");

    fprintf(out, "B has %d non-zero entries:\n", nnz2);
    printMatrix(out, B);
    fprintf(out, "\n");

    Matrix sM = scalarMult(1.5, A);
    fprintf(out, "(1.5)*A =\n");
    printMatrix(out, sM);
    fprintf(out, "\n");

    Matrix S = sum(A, B);
    fprintf(out, "A+B =\n");
    printMatrix(out, S);
    fprintf(out, "\n");

    Matrix S2 = sum(A, A);
    fprintf(out, "A+A =\n");
    printMatrix(out, S2);
    fprintf(out, "\n");

    Matrix D = diff(B, A);
    fprintf(out, "B-A =\n");
    printMatrix(out, D);
    fprintf(out, "\n");

    Matrix D2 = diff(A, A);
    fprintf(out, "A-A =\n");
    printMatrix(out, D2);
    fprintf(out, "\n");

    Matrix T = transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, T);
    fprintf(out, "\n");

    Matrix P = product(A, B);
    fprintf(out, "A*B =\n");
    printMatrix(out, P);
    fprintf(out, "\n");

    Matrix P2 = product(B, B);
    fprintf(out, "B*B =\n");
    printMatrix(out, P2);

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&sM);
    freeMatrix(&S);
    freeMatrix(&S2);
    freeMatrix(&D);
    freeMatrix(&D2);
    freeMatrix(&T);
    freeMatrix(&P);
    freeMatrix(&P2);

	fclose(in);
	fclose(out);
	return 0;
}