/*
Eric Wang, twang173, Programming Assignment 3
*/

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int main(int argc, char *argv[]){
    if(argc != 3){ //arg check
        printf("%s <infile> <outfile>\n", argv[0]);
        exit(1);
    }

    FILE *i = fopen(argv[1], "r"); // read infile
    if(i == NULL){
        printf("Can't open file %s for reading\n", argv[1]);
        exit(1);
    }

    FILE *o = fopen(argv[2], "w"); // write outfile
    if(o == NULL){
        printf("Can't open file %s for writing\n", argv[2]);
        exit(1);
    }

    int v; //num of vertices
    fscanf(i, "%d\n", &v);

    Graph newG = newGraph(v);

    int a, b; //initialize vertex pairs a->b
    while(!feof(i)){
        fscanf(i, "%d %d\n", &a, &b);
        if(a == 0 && b == 0){
            break;
        }
        else{
            addArc(newG, a, b);
        }
    }

    List newL = newList(); //creating stack

    int x = 1; 
    while(x <= v){
        append(newL, x);
        x++;
    }

    DFS(newG, newL);
    Graph transp = transpose(newG);
    DFS(transp, newL);

    int SC = 0; //strong components
    moveFront(newL);
    while(index(newL) >= 0){
        if(getParent(transp, get(newL)) == NIL){
            SC++;
        }
        moveNext(newL);
    }

    List L[SC]; // the list of strong components
    
    int y = 0;
    while(y < SC){
        L[y] = newList();
        y++;
    }

    moveBack(newL);

    int z = 0; // the index of sc in list
    while(index(newL) >= 0){
        if(SC == 0){ // sc check
            break;
        }

        prepend(L[z], get(newL));
        if(getParent(transp, get(newL)) == NIL){
            z++;
        }
        movePrev(newL);
    }

    fprintf(o, "Adjacency list representation of G:\n");
    printGraph(o, newG);

    fprintf(o, "\nG contains %d strongly connected components:", SC);

    int s = 0;
    while(s < SC){
        fprintf(o, "\nComponent %d: ", s + 1);
        printList(o, L[s]);

        s++;
    }
    fprintf(o, "\n");

    //freeing stuff now
    for(int i = 0; i < SC; i++){
        freeList(&L[i]);
    }
    freeGraph(&newG);
    freeGraph(&transp);
    freeList(&newL);

    fclose(i);
    fclose(o);
    
    return 0; //end
}