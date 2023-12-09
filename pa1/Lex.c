/*
Eric Wang, twang173, Programming Assignment 1
*/
#include <stdio.h>
#include "List.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define LINE_LENGTH 48

int main(int argc, char* argv[]){
    int count = 0;
    if(argc > 3 || argc < 3){
        fprintf(stderr, "More than/Less than 2 command argument spotted.\n");
        exit(1);
    }

    FILE *in, *out;
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if(in == NULL){
        fprintf(stderr, "Could not open file.\n");
        return 0;
    }

    for(char c = getc(in); c != EOF; c = getc(in)){
        if(c == '\n'){
            count++;
        }
    }

    fseek(in, 0, SEEK_SET);
    char** z = malloc(sizeof(char *) * count);
    for (int i = 0; i < count; i++)
    {
        z[i] = malloc(LINE_LENGTH * sizeof(char));
        fgets(z[i], LINE_LENGTH, in);
    }

    List L = newList();
    int fs = 0;
    int lu;
    append(L, 0); //the first element
    for(lu = 1; lu < count; lu++){
        if(strcmp(z[lu], z[fs]) < 0){
            fs = lu;
            prepend(L, lu);
        }
        else if(strcmp(z[lu], z[back(L)]) >= 0){
            append(L, lu);
        }
        else{
            moveFront(L);
            moveNext(L);
            while(index(L) != -1){
                if(strcmp(z[lu], z[get(L)]) < 0){
                    break;
                }
                moveNext(L);
            }
            insertBefore(L, lu);
        }
    }
    moveFront(L);
    for(int i = 0; i < count; i++){
        fputs(z[get(L)], out);
        moveNext(L);
    }

    fclose(in);
    fclose(out);

    for(int i = 0; i < count; i++){
        free(z[i]);
    }
    free(z);
    freeList(&L);
    return 0;
}