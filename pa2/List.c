/*
Eric Wang, twang173, Programming Assignment 2
*/

#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include <stdbool.h>

typedef struct NodeObj* Node;

typedef struct NodeObj {
    int data;
    Node next;
    Node prev;
} NodeObj;

typedef struct ListObj {
    Node front;
    Node back;
    Node cursor;
    int index;
    int size;
} ListObj;

Node newNode(int data){
    Node victor = malloc(sizeof(NodeObj));
    if(victor != NULL){
        victor->data = data;
        victor->next = NULL;
        victor->prev = NULL;
    }
    return victor;
}

void nodeDelete(Node *n){
    if((*n) != NULL){
        free((*n));
        (*n) = NULL;
    }
    return;
}

List newList(void){
    List newL = malloc(sizeof(ListObj));
    if(newL != NULL){
        newL->front = NULL;
        newL->back = NULL;
        newL->cursor = NULL;
        newL->index = -1;
        newL->size = 0;
    }
    return newL;
}

void freeList(List* pL){
    if(pL != NULL && *pL != NULL){
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

int length(List L){
    return L->size;
}

int index(List L){
    if(L->index >= 0){
        return L->index;
    }
    return -1;
}

int front(List L){
    if(L->size > 0){
        return L->front->data;
    }
    return -50;
}

int back(List L){
    if(L->size > 0){
        return L->back->data;
    }
    return -50;
}

int get(List L){
    if(L->size > 0 && L->index >= 0){
        return L->cursor->data;
    }
    return -50;
}

bool equals(List A, List B){
    if(length(A) != length(B)){
        return false;
    }
    Node a = A->front;
    Node b = B->front;
    for (int i = 0; i < length(A); i++) {
        if(a->data != b->data){
            return false;
        }
        a = a->next;
        b = b->next;
    }
    return true;
}

void clear(List L){
    if(L != NULL){
        if(L->size > 0){
            //moveFront(L);
            while(L->size > 0){
                deleteFront(L);
            }
            L->size = 0;
            L->index = -1;
        }
    }
}

void set(List L, int x){
    if(L->size > 0 && L->index >= 0){
        L->cursor->data = x;
    }
    return;
}

void moveFront(List L){
    if(L->size > 0){
        L->cursor = L->front;
        L->index = 0;
    }
    return;
}

void moveBack(List L){
    if(L->size > 0){
        L->index = L->size - 1;
        L->cursor = L->back;
    }
    return;
}

void movePrev(List L){
    if(L->cursor != NULL && L->cursor != L->front){
        L->cursor = L->cursor->prev;
        L->index -= 1; 
    }
    else if(L->cursor != NULL && L->cursor == L->front){
        L->cursor = NULL;
        L->index = -1;
    }
    else{
        return;
    }
}

void moveNext(List L){
    if(L->cursor != NULL && L->cursor != L->back){
        L->cursor = L->cursor->next;
        L->index += 1; 
    }else if(L->cursor != NULL && L->cursor == L->back){
        L->cursor = NULL;
        L->index = -1;
    }
    else{
        return;
    }
}

void prepend(List L, int x){
    Node n = newNode(x);
    if(L->size != 0){
        L->front->prev = n;
        n->next = L->front;
        L->front = n;
        L->size++;
        if(L->cursor != NULL){
            L->index++;
        }
    }
    else{
        L->front = L->back = n;
        L->size++;
    }
    return;
}

void append(List L, int x){
    Node n = newNode(x);
    if(L->size != 0){
        L->back->next = n;
        n->prev = L->back;
        L->back = n;
        L->size++;
    }
    else{
        L->front = L->back = n;
        L->size++;
    }
    return;
}

void insertBefore(List L, int x){
    if(L->size <= 0 || L->index < 0){
        return;
    }
    if(L->cursor != L->front){
        Node n = newNode(x);
        n->next = L->cursor;
        n->prev = L->cursor->prev;
        L->cursor->prev->next = n;
        L->cursor->prev = n;
        L->index++;
        L->size++;
    }
    else{
        prepend(L, x);
    }
    return;
}

void insertAfter(List L, int x){
    //printf("%d, %d\n", L->size, L->index);
    if(L->size <= 0 || L->index < 0){
        return;
    }

    if(L->cursor != L->back){
        Node n = newNode(x);
        n->prev = L->cursor;
        n->next = L->cursor->next;
        L->cursor->next->prev = n;
        L->cursor->next = n;
        L->size++;
    }
    else{
        append(L, x);
    }
    return;
}

void deleteFront(List L){
    if(L->size <= 0){
        return;
    }
    Node temp = L->front;
    if(L->cursor != NULL){
        L->index--;
    }

    if (L->cursor == L->front) {
        L->cursor = NULL;
        L->index = -1;
    }

    if (L->size > 1) {
        L->front = L->front->next;
        L->front->prev = NULL;
    } else {
        L->front = L->back = NULL;
    }
    L->size--;

    nodeDelete(&temp);
}
void deleteBack(List L){
    if(L->size <= 0){
        return;
    }
    Node temp = L->back;

    if (L->cursor == L->back) {
        L->cursor = NULL;
        L->index = -1;
    }

    if (L->size > 1) {
        L->back = L->back->prev;
        L->back->next = NULL;
    } else {
        L->front = L->back = NULL;
    }
    L->size--;

    nodeDelete(&temp);
}
void delete(List L){
    if(L->size  > 0 && L->index >= 0){
        if(L->cursor == L->front){
            deleteFront(L);
        }   
        else if(L->cursor == L->back){
            deleteBack(L);
        }
        else{
            L->cursor->prev->next = L->cursor->next;
            L->cursor->next->prev = L->cursor->prev; 
            L->index = -1;
            L->size--;
        }

    }
    else{
        return;
    }
} 

void printList(FILE* out, List L){
    if(L == NULL){
        fprintf(stderr, "Error, calling printList on a NULL list.\n");
        exit(EXIT_FAILURE);
    }
    Node n = NULL;
    for(n = L->front; n != L->back->next; n = n->next){
        fprintf(out, "%d ", n->data);
    }
}

List copyList(List L){
    if(L == NULL){
        fprintf(stderr, "Error, calling copyList on a NULL list.\n");
        exit(EXIT_FAILURE);
    }
    List copiedList = newList();
    for(Node n = L->front; n != NULL; n = n->next){
        append(copiedList, n->data);
    }
    return copiedList;
}

List concatList(List A, List B);