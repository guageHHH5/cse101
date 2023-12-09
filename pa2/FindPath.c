/*
Eric Wang, twang173, Programming Assignment 2
*/

#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

int main(int argc, char* argv[]){
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

    int vert; // number of vertices
    fscanf(i, "%d", &vert);

    Graph newG = newGraph(vert);

    int sourc, dest; // source and destination for edges
    while(!feof(i)){
        fscanf(i, "%d %d\n", &sourc, &dest);
        if(sourc == 0 && dest == 0){
            break;
        }
        else{
            addEdge(newG, sourc, dest);
        }
    }

    printGraph(o, newG);

    int sp, dp; // source and destination for paths
    while(!feof(i)){
        fscanf(i, "%d %d\n", &sp, &dp);
        if(sp == 0 && dp == 0){
            break;
        }
        BFS(newG, sp);

        List newL = newList();
        getPath(newL, newG, dp);

        int pathDist = getDist(newG, dp);

        fprintf(o, "\nThe distance from %d to %d is ", sp, dp);
        if(pathDist == INF){
            fprintf(o, "infinity\n");
            fprintf(o, "No %d-%d path exists\n", sp, dp);
        }
        else{
            fprintf(o, "%d\n", pathDist);
            fprintf(o, "A shortest %d-%d path is: ", sp, dp);
            printList(o, newL);
            fprintf(o, "\n");
        }
        freeList(&newL);
    }

    fclose(i);
    fclose(o);
    freeGraph(&newG);

    return 0; //end
}