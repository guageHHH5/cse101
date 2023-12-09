/*
Eric Wang, twang173, Programming Assignment 3
*/
#pragma once

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "List.h"

#define UNDEF -1
#define NIL -2
#define GRAY -20
#define WHITE -21
#define BLACK -22

typedef struct GraphObj *Graph;

Graph newGraph(int n);
void freeGraph(Graph *pG);

int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S);

Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);
