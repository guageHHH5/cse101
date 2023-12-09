/*
Eric Wang, twang173, Programming Assignment 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "List.h"
#include "Matrix.h"

typedef struct EntryObj* Entry;

typedef struct EntryObj{
    int column;
    double data;
}EntryObj;

typedef struct MatrixObj{
    int size;
    int nnz;
    List* ListArray;
}MatrixObj;

Entry newEntry(int c, double d){
    Entry E = malloc(sizeof(EntryObj));
    if(E != NULL){
        E->column = c;
        E->data = d;
    }
    return E;
}

void freeEntry(Entry* pE){
    if((*pE) != NULL){
        free((*pE));
        (*pE) = NULL;
    }
    return;
}

Matrix newMatrix(int n){
    Matrix M = malloc(sizeof(MatrixObj));
    if(M != NULL){
        M->size = n;
        M->nnz = 0;
        M->ListArray = malloc((n + 1)*sizeof(List));
        for(int i = 0; i < n + 1; i++){
            M->ListArray[i] = newList();
            assert(M->ListArray[i] != NULL);
        }
    }
    return M;
}

void freeMatrix(Matrix* pM){
    if(pM && (*pM)){
        makeZero(*pM);
        for(int i = 0; i < size(*pM) + 1; i++){
            freeList(&(*pM)->ListArray[i]);
        }
        free((*pM)->ListArray);
        
    }
    free((*pM));
    *pM = NULL;
}

int size(Matrix M){
    if(M == NULL){
        printf("ERROR: calling size on NULL Matrix\n");
        exit(1);
    }
    return M->size;
}
int NNZ(Matrix M){
    if(M == NULL){
        printf("ERROR: calling NNZ on NULL Matrix\n");
        exit(1);
    }
    return M->nnz;
}

int equals(Matrix A, Matrix B){
    if (A == NULL || B == NULL) {
        exit(1);
    }
    if(size(A) == size(B) && NNZ(A) == NNZ(B)){
        for(int i = 1; i < size(A) + 1; i++){
            moveFront(A->ListArray[i]);
            moveFront(B->ListArray[i]);
            while(index(A->ListArray[i]) >= 0 && index(B->ListArray[i]) >= 0){
                if(((Entry)get(A->ListArray[i]))->column == ((Entry)get(B->ListArray[i]))->column && 
                ((Entry)get(A->ListArray[i]))->data == ((Entry)get(B->ListArray[i]))->data){
                    moveNext(A->ListArray[i]);
                    moveNext(B->ListArray[i]);
                }
                else{
                    return 0;
                }
            }
        }
    }else{
        return 0;
    }
    return 1;
}

void makeZero(Matrix M){
    if (M == NULL) {
        exit(1);
    }
    int i = 1;
    while(i < size(M) + 1){
        Entry E = NULL;
        moveFront(M->ListArray[i]);
        while(index(M->ListArray[i]) >= 0){
            E = get(M->ListArray[i]);
            freeEntry(&E);
            //M->nnz--;
            moveNext(M->ListArray[i]);
        }
        clear(M->ListArray[i]);
        i++;
    }
    M->nnz = 0;
}

void changeEntry(Matrix M, int i, int j, double x){
    if(M != NULL){
        if(x != 0.0){
            //Entry E = newEntry(j, x);
            if(length(M->ListArray[i]) == 0){
                append(M->ListArray[i], newEntry(j,x));
                M->nnz++;
            }
            else{
                moveFront(M->ListArray[i]);
                while(index(M->ListArray[i]) >= 0 && ((Entry)get(M->ListArray[i]))->column < j){
                    moveNext(M->ListArray[i]);
                }
                if(index(M->ListArray[i]) == 0){
                    if(j != ((Entry)get(M->ListArray[i]))->column){
                        prepend(M->ListArray[i], newEntry(j,x));
                        M->nnz++;
                    }
                } else if(index(M->ListArray[i]) == -1){
                    append(M->ListArray[i], newEntry(j,x));
                    M->nnz++;
                }
                else if(((Entry)get(M->ListArray[i]))->column == j){
                    Entry n = get(M->ListArray[i]);
                    n->data = x;
                }
                else{
                    insertBefore(M->ListArray[i], newEntry(j,x));
                    M->nnz++;
                }
            }
        } else{ //if x == 0.0
            moveFront(M->ListArray[i]);
            while(index(M->ListArray[i]) >= 0 && ((Entry)get(M->ListArray[i]))->column < j){
                moveNext(M->ListArray[i]);
            }
            if(index(M->ListArray[i]) >= 0){
                Entry e = get(M->ListArray[i]);
                freeEntry(&e);
                delete(M->ListArray[i]);
                M->nnz--;
            }
        }
    }
    return;
}

Matrix copy(Matrix A){
    if (A == NULL) {
        exit(1);
    }
    Matrix C = newMatrix(size(A));

    int i = 1;
    while(i < size(A) + 1){
        List N = A->ListArray[i];

        moveFront(N);

        while(index(N) >= 0){
            Entry E = get(N);
            append(C->ListArray[i], newEntry(E->column, E->data));
            C->nnz++;
            moveNext(N);
        }
        i++;
    }
    return C;
}

Matrix transpose(Matrix A){
    if (A == NULL) {
        exit(1);
    }
    Matrix C = newMatrix(size(A));

    int i = 1;
    while(i < size(A) + 1){
        List N = A->ListArray[i];

        moveFront(N);

        while(index(N) >= 0){
            Entry E = get(N);
            append(C->ListArray[E->column], newEntry(i, E->data));
            C->nnz++;
            moveNext(N);
        }
        i++;
    }
    return C;
}

Matrix scalarMult(double x, Matrix A){
    if (A == NULL) {
        exit(1);
    }
    Matrix C = newMatrix(size(A));
    if(x != 0.0){
        int i = 1;
        while(i < size(A) + 1){
            List N = A->ListArray[i];

            moveFront(N);

            while(index(N) >= 0){
                Entry E = get(N);
                append(C->ListArray[i], newEntry(E->column, E->data * x));
                C->nnz++;
                moveNext(N);
            }
            i++;
        }    
    }
    return C;
}

Matrix sum(Matrix A, Matrix B){
    if (A == NULL || B == NULL) {
        exit(1);
    }
    if(size(A) != size(B)){
        exit(1);
    }
    if(A == B){
        Matrix S = scalarMult(2.0, A);
        return S;
    }

    Matrix S = newMatrix(size(A));

    int i = 1;
    while(i < size(A) + 1){
        List N = A->ListArray[i];
        List N2 = B->ListArray[i];

        moveFront(N);
        moveFront(N2);

        while(index(N) >= 0 && index(N2) >=0){
            if(((Entry)get(N))->column > ((Entry)get(N2))->column){
                append(S->ListArray[i], newEntry(((Entry)get(N2))->column, ((Entry)get(N2))->data));
                S->nnz++;
                moveNext(N2);
            } else if(((Entry)get(N2))->column > (((Entry)get(N))->column)){
                append(S->ListArray[i], newEntry(((Entry)get(N))->column, ((Entry)get(N))->data));
                S->nnz++;
                moveNext(N);
            } else {
                if(((Entry)get(N))->data + ((Entry)get(N2))->data != 0.0){
                    append(S->ListArray[i], newEntry(((Entry)get(N))->column, ((Entry)get(N))->data + ((Entry)get(N2))->data));
                    S->nnz++;
                }
                moveNext(N);
                moveNext(N2);
            }
        }

        while(index(N) >= 0){
            Entry a = get(N);
            append(S->ListArray[i], newEntry(a->column, a->data));
            S->nnz++;
            moveNext(N);
        }

        while(index(N2) >= 0){
            Entry b = get(N2);
            append(S->ListArray[i], newEntry(b->column, b->data));
            S->nnz++;
            moveNext(N2);
        }
        i++;
    }
    return S;    
}

Matrix diff(Matrix A, Matrix B){
    if (A == NULL || B == NULL) {
        exit(1);
    }
    if(size(A) != size(B)){
        exit(1);
    }
    if(A == B){
        Matrix D = newMatrix(size(A));
        return D;
    }

    Matrix D = newMatrix(size(A));
    
    int i = 1;
    while(i < size(A) + 1){
        List N = A->ListArray[i];
        List N2 = B->ListArray[i];

        moveFront(N);
        moveFront(N2);

        while(index(N) >= 0 && index(N2) >=0){
            if(((Entry)get(N))->column > ((Entry)get(N2))->column){
                append(D->ListArray[i], newEntry(((Entry)get(N2))->column, ((Entry)get(N2))->data * -1));
                D->nnz++;
                moveNext(N2);
            } else if(((Entry)get(N2))->column > (((Entry)get(N))->column)){
                append(D->ListArray[i], newEntry(((Entry)get(N))->column, ((Entry)get(N))->data));
                D->nnz++;
                moveNext(N);
            } else {
                if(((Entry)get(N))->data - ((Entry)get(N2))->data != 0.0){
                    append(D->ListArray[i], newEntry(((Entry)get(N))->column, ((Entry)get(N))->data - ((Entry)get(N2))->data));
                    D->nnz++;
                }
                moveNext(N);
                moveNext(N2);
            }
        }

        while(index(N) >= 0){
            Entry a = get(N);
            append(D->ListArray[i], newEntry(a->column, a->data));
            D->nnz++;
            moveNext(N);
        }

        while(index(N2) >= 0){
            Entry b = get(N2);
            append(D->ListArray[i], newEntry(b->column, b->data * -1));
            D->nnz++;
            moveNext(N2);
        }
        i++;
    }
    return D;    
}
Matrix product(Matrix A, Matrix B){
    if (A == NULL || B == NULL) {
        exit(1);
    }
    if(size(A) != size(B)){
        exit(1);
    }

    Matrix P = newMatrix(size(A));
    Matrix Pt = transpose(B);

    int i = 1;
    while(i < size(A) + 1){

        int j = 1;
        while(j < size(A) + 1){
            if(length(A->ListArray[i]) == 0){
                break;
            }

            double s = 0.0;

            moveFront(A->ListArray[i]);
            moveFront(Pt->ListArray[j]);
            while(index(A->ListArray[i]) >= 0 && index(Pt->ListArray[j]) >= 0){
                Entry a = get(A->ListArray[i]);
                Entry b = get(Pt->ListArray[j]);

                if(a->column > b->column){
                    moveNext(Pt->ListArray[j]);
                } else if(b->column > a->column){
                    moveNext(A->ListArray[i]);
                } else 
                {
                    s += (a->data * b->data);
                    moveNext(A->ListArray[i]);
                    moveNext(Pt->ListArray[j]);
                }
            }

            if(s != 0.0){
                append(P->ListArray[i], newEntry(j, s));
                P->nnz++;
            }
            j++;
        }
        i++;
    }
    freeMatrix(&Pt);
    return P;
}

void printMatrix(FILE* out, Matrix M){
    if(M == NULL){
        fprintf(stderr, "Error, calling printMatrix on a NULL Matrix.\n");
        exit(EXIT_FAILURE);
    }
    for(int i = 1; i < size(M) + 1; i++){
        if(length(M->ListArray[i]) != 0){
            fprintf(out, "%d:", i);
            moveFront(M->ListArray[i]);
            while(index(M->ListArray[i]) >= 0){
                fprintf(out, " (%d, %.1f)", ((Entry)get(M->ListArray[i]))->column, ((Entry)get(M->ListArray[i]))->data);
                moveNext(M->ListArray[i]);
            }
            fprintf(out, "\n");
        }
    }
}