/*
Eric Wang, twang173, Programming Assignment 2
*/
#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "List.h"

#define INF -1
#define NIL -2
#define GRAY 1
#define WHITE 0
#define BLACK 2

typedef struct GraphObj *Graph;

Graph newGraph(int n);
void freeGraph(Graph *pG);

int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

void printGraph(FILE* out, Graph G);
