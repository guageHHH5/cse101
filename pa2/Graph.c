/*
Eric Wang, twang173, Programming Assignment 2
*/
#include <stdbool.h>
#include <stdint.h>
#include "List.h"
#include "Graph.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct GraphObj{
    List* neighbor;
    int* color;
    int* parent;
    int* distance;
    int order;
    int size;
    int source;
} GraphObj;

Graph newGraph(int n){
    Graph g = malloc(sizeof(GraphObj));
    if(g != NULL){
        g->neighbor = malloc((n + 1) * sizeof(List));
        g->color = malloc((n + 1) * sizeof(int));
        g->parent = malloc((n + 1) * sizeof(int));
        g->distance = malloc((n + 1) * sizeof(int));
        g->order = n;
        g->size = 0;
        g->source = NIL;
        int i = 0;
        while(i < (n + 1)){
            g->neighbor[i] = newList();
            g->color[i] = WHITE;
            g->parent[i] = NIL;
            g->distance[i] = INF;
            i++;
        }
    }
    return g;
}

void freeGraph(Graph *pG){
    if(pG && (*pG)){
        int i = 0;
        while(i < getOrder(*pG) + 1){
            freeList(&(*pG)->neighbor[i]);
            i++;
        }
        free((*pG)->neighbor);
        free((*pG)->color);
        free((*pG)->parent);
        free((*pG)->distance);
        (*pG)->color = NULL;
        (*pG)->parent = NULL;
        (*pG)->distance = NULL;
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

int getSource(Graph G){
    if(G == NULL){
        printf("ERROR: calling getSource on NULL Graph\n");
        exit(1);
    }
    return G->source;
}

int getParent(Graph G, int u){
    if(G == NULL){
        printf("ERROR: calling getParent on NULL Graph\n");
        return NIL;
        //exit(1);
    }
    if(1 > u || u > getOrder(G) || getSize(G) == 0){
        //printf("Graph Error: getParent() Oob Error\n");
        return NIL;
        //exit(1);
    }
    return G->parent[u];
}

int getDist(Graph G, int u){
    if(G == NULL){
        printf("ERROR: calling getDist on NULL Graph\n");
        return INF;
        //exit(1);
    }
    if(1 > u || u > getOrder(G) || getSize(G) == 0){
        //printf("Graph Error: getDist() Oob Error\n");
        return INF;
        //exit(1);
    }
    if(G->source == NIL){
        return INF;
    }
    return G->distance[u];
}

void getPath(List L, Graph G, int u){
    if(G == NULL){
        printf("ERROR: calling getPath on NULL Graph\n");
        exit(1);
    }
    if (1 > u || u > getOrder(G)) {
        printf("Error: calling getPath on vertex out of bounds\n");
        exit(1);
    }    
    if(G->source == NIL){
        printf("ERROR: calling getPath on NIL source vertex\n");
        exit(1);
    }
    List newL = newList(); // temp List
    while(u != G->source){
        if(u == NIL){     
            break;
        }
        prepend(newL, u);
        u = G->parent[u];
    }

    if(u != NIL){
        prepend(newL, u);
        while(length(newL) != 0){
            append(L, front(newL)); // dequeue from the temp list, while adding to L
            deleteFront(newL);
        }
    } else {
        append(L, NIL);
    }

    freeList(&newL);
    return;
}

void makeNull(Graph G){
    if(G == NULL){
        printf("ERROR: calling makeNULL on NULL Graph\n");
        exit(1);
    }
    int i = 0;
    while(i < getOrder(G) + 1){
        clear(G->neighbor[i]);
        i++;
    }
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

void addArc(Graph G, int u, int v){
    if(G == NULL){
        printf("ERROR: calling addArc on NULL Graph\n");
        exit(1);
    }
    if (1 > u || u > getOrder(G) || 1 > v || v > getOrder(G)) {
        printf("Error: calling addArc on vertex out of bounds\n");
        exit(1);
    }
    moveBack(G->neighbor[u]);
    while(index(G->neighbor[u]) >= 0 && v < get(G->neighbor[u])){
        movePrev(G->neighbor[u]);
    }

    if(index(G->neighbor[u]) >= 0){
        insertAfter(G->neighbor[u], v);
    }
    else{
        prepend(G->neighbor[u], v);
    }
    G->size++;
    return;
}

void sort(List L, int i){
    if(length(L) == 0){
        append(L, i);
    }
    else if(i != front(L) && i != back(L)){
        if(front(L) > /*or "<" if default doesnt work*/ i){
            prepend(L, i);
        }
        else if(back(L) < /*or ">" if default doesnt work*/ i){
            append(L, i);
        }
        else{
            moveFront(L);
            moveNext(L);
            while(index(L) != -1){
                if(i == get(L))
                {
                    break;
                }
                if(i < get(L)){
                    insertBefore(L, i);
                    break;
                }
                if(i > get(L)){
                    moveNext(L);
                }
            }
        }
    }
}

void BFS(Graph G, int s){
    if(G == NULL){
        printf("ERROR: calling BFS on NULL Graph\n");
        exit(1);
    }
    int i = 1;
    while(i < getOrder(G) + 1){
        G->color[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
        i++;
    }
    G->source = s;
    G->color[s] = GRAY;
    G->distance[s] = 0;
    G->parent[s] = NIL;

    List newL = newList();
    prepend(newL, s);
    
    while(length(newL) != 0){
        int z = front(newL);
        deleteFront(newL);

        moveFront(G->neighbor[z]);
        while (index(G->neighbor[z]) >= 0)
        {
            int x = get(G->neighbor[z]);
            if(G->color[x] == WHITE){
                G->color[x] = GRAY;
                G->distance[x] = G->distance[z] + 1;
                G->parent[x] = z;

                append(newL, x);
            }
            moveNext(G->neighbor[z]);
        }
        G->color[z] = BLACK;
    }
    freeList(&newL);
    return;
}

void printGraph(FILE* out, Graph G){
    if(G == NULL){
        printf("ERROR: calling printGraph on NULL Graph\n");
        exit(1);
    }
    int i = 1;
    while(i < getOrder(G) + 1){
        fprintf(out, "%d: ", i);
        printList(out, G->neighbor[i]);
        fprintf(out, "\n");
        i++;
    }
    return;
}