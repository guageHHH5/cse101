/*
Eric Wang, twang173, Programming Assignment 3
*/

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

typedef struct GraphObj{
    List *adjacent;
    int *color;
    int *parent;
    int *d;
    int *f;
    int order;
    int size;
} GraphObj;

Graph newGraph(int n){
    Graph g = malloc(sizeof(GraphObj));
    if(g != NULL){
        g->adjacent = malloc((n + 1) * sizeof(List));
        g->color = malloc((n + 1) * sizeof(int));
        g->parent = malloc((n + 1) * sizeof(int));
        g->d = malloc((n + 1) * sizeof(int));
        g->f = malloc((n + 1) * sizeof(int));
        g->order = n;
        g->size = 0;
        int i = 0;
        while(i < (n + 1)){
            g->adjacent[i] = newList();
            g->color[i] = WHITE;
            g->parent[i] = NIL;
            g->d[i] = UNDEF;
            g->f[i] = UNDEF;
            i++;
        }
    }
    return g;
}

void freeGraph(Graph *pG){
    if(pG && (*pG)){
        int i = 0;
        while(i < getOrder(*pG) + 1){
            freeList(&(*pG)->adjacent[i]);
            i++;
        }
        free((*pG)->adjacent);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->d);
        free((*pG)->f);
        free(*pG);
        *pG = NULL;
    }
    return;
}

int getOrder(Graph G){
    if(G == NULL){
        printf("ERROR: calling getOrder on NULL Graph\n");
        exit(1);
    }
    return G->order;
}

int getSize(Graph G){
    if(G == NULL){
        printf("ERROR: calling getSize on NULL Graph\n");
        exit(1);
    }
    return G->size;
}

int getParent(Graph G, int u){
    if(G == NULL){
        printf("ERROR: calling getParent on NULL Graph\n");
        return NIL;
        //exit(1);
    }
    if(1 > u || u > getOrder(G)){
        //printf("Graph Error: getParent() Oob Error\n");
        return NIL;
        //exit(1);
    }
    return G->parent[u];
}

int getDiscover(Graph G, int u){
    if(G == NULL){
        printf("ERROR: calling getDiscover on NULL Graph\n");
        return NIL;
        //exit(1);
    }
    if(1 > u || u > getOrder(G)){
        //printf("Graph Error: getDiscover() Oob Error\n");
        return NIL;
        //exit(1);
    }
    return G->d[u];
}

int getFinish(Graph G, int u){
    if(G == NULL){
        printf("ERROR: calling getFinish on NULL Graph\n");
        return NIL;
        //exit(1);
    }
    if(1 > u || u > getOrder(G)){
        //printf("Graph Error: getParent() Oob Error\n");
        return NIL;
        //exit(1);
    }
    return G->f[u];
}

void addArc(Graph G, int u, int v){
    if(G == NULL){
        printf("ERROR: calling addArc on NULL Graph\n");
        exit(1);
    }
    if (1 > u || u > getOrder(G) || 1 > v || v > getOrder(G)) {
        printf("Error: calling addArc on vertex out of bounds\n");
        exit(1);
    }

    if(length(G->adjacent[u]) == 0) {
        append(G->adjacent[u], v);
        G->size++;
        return;
    }

    moveBack(G->adjacent[u]);
    while(index(G->adjacent[u]) >= 0 && v < get(G->adjacent[u])){
        movePrev(G->adjacent[u]);
    }

    if(get(G->adjacent[u]) == v) {
        return;
    }

    if(index(G->adjacent[u]) >= 0){
        insertAfter(G->adjacent[u], v);
    }
    else{
        prepend(G->adjacent[u], v);
    }
    G->size++;
    return;
}

void addEdge(Graph G, int u, int v){
    if(G == NULL){
        printf("ERROR: calling addEdge on NULL Graph\n");
        exit(1);
    }
    if (1 > u || u > getOrder(G) || 1 > v || v > getOrder(G)) {
        printf("Error: calling addEdge on vertex out of bounds\n");
        exit(1);
    }
    addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
    return;
}

//Visit(): Helper function for DFS
void Visit(Graph G, List S, int x, int *time){
    G->d[x] = ++(*time);
    G->color[x] = GRAY;
    moveFront(G->adjacent[x]);
    while(index(G->adjacent[x]) >= 0){
        int i = get(G->adjacent[x]);
        if(G->color[i] == WHITE){
            G->parent[i] = x;
            Visit(G, S, i, time);
        }
        moveNext(G->adjacent[x]);
    }
    G->color[x] = BLACK;
    G->f[x] = ++(*time);
    prepend(S, x);
    return;
}

void DFS(Graph G, List S){
    if(G == NULL){
        printf("ERROR: calling DFS on NULL Graph\n");
        exit(1);
    }
    if(length(S) != getOrder(G)){
        printf("ERROR: calling DFS on incorrect List length\n");
        exit(1);
    }
    int i = 1;
    while(i < getOrder(G) + 1){
        G->color[i] = WHITE;
        G->parent[i] = NIL;
        i++;
    }
    int time = 0;
    List Copied = copyList(S);
    clear(S);
    moveFront(Copied);
    while(index(Copied) >= 0){
        int x = get(Copied);
        if(G->color[x] == WHITE){
            Visit(G, S, x, &time);
        }
        moveNext(Copied);
    }
    freeList(&Copied);
    return;
}

Graph transpose(Graph G){
    if(G == NULL){
        printf("ERROR: calling transpose on NULL Graph\n");
        exit(1);
    }
    Graph N = newGraph(getOrder(G)); //newGraph for transpose
    int i = 1;
    while(i < getOrder(G) + 1){
        moveFront(G->adjacent[i]);
        while(index(G->adjacent[i]) >= 0){
            addArc(N, get(G->adjacent[i]), i);
            moveNext(G->adjacent[i]);
        }
        i++;
    }
    return N;
}

Graph copyGraph(Graph G){
    if(G == NULL){
        printf("ERROR: calling copyGraph on NULL Graph\n");
        exit(1);
    }
    Graph Copied = newGraph(getOrder(G)); //new graph for copied
    int i = 1;
    while(i < getOrder(G) + 1){
        moveFront(G->adjacent[i]);
        while(index(G->adjacent[i]) >= 0){
            addArc(Copied, i, get(G->adjacent[i]));
            moveNext(G->adjacent[i]);
        }
        i++;
    }
    return Copied;
}

void printGraph(FILE *out, Graph G){
    if(G == NULL){
        printf("ERROR: calling printGraph on NULL Graph\n");
        exit(1);
    }
    for(int i = 1; i <= getOrder(G); i++){
        fprintf(out, "%d: ", i);
        printList(out, G->adjacent[i]);
        fprintf(out, "\n");
    }
    return;
}
