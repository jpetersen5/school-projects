#include <iostream>
using namespace std;


void bellmanFord(struct graph* g);


// edge and graph structures to hold data needed for bellman-ford
struct edge {
        int start;
        int end;
        int w;
};

struct graph {
        int numEdge;
        int verts;
        // all edges in graph as an array
        struct edge* edges;
};


// creates a new graph and allocates space for list of edges
struct graph* newGraph(int numEdge, int verts) {
        struct graph* tempGraph = new graph;
        tempGraph->numEdge = numEdge;
        tempGraph->verts = verts;

        tempGraph->edges = new edge[numEdge];
        return tempGraph;
}


// driver code, takes input and assigns values
// then prints bellman-ford algorithm output
int main() {
        int v, e, i;

        cin >> v;
        cin >> e;

        struct graph* g = newGraph(e, v);

        for (i = 0; i < e; i++) {
                cin >> g->edges[i].start;
                cin >> g->edges[i].end;
                cin >> g->edges[i].w;
        }

        bellmanFord(g);

        return 0;
}


// bellman-ford algorithm, computes shortest paths to each vertex
void bellmanFord(struct graph* g) {
        // array of distances to compare and print later
        int i, j;
        int distance[g->verts];

        // fill array with infinity initially
        for (i = 0; i < g->verts; i++)
                distance[i] = 2147483647;
        // source vertex 0 has 0 distance
        distance[0] = 0;

        // relax edges |v|-1 times
        for (i = 1; i < g->verts; i++)
                // each edge
                for (j = 0; j < g->numEdge; j++)
                        // compare size; select lesser
                        if (distance[g->edges[j].start] + g->edges[j].w
                            < distance[g->edges[j].end]
                            && distance[g->edges[j].start] != 2147483647)
                                // set new distance
                                distance[g->edges[j].end] = distance[g->edges[j].start]
                                                            + g->edges[j].w;

        // negative cycle check
        for (i = 0; i < g->numEdge; i++)
                // if there's another shorter path
                if (distance[g->edges[i].start] + g->edges[i].w
                    < distance[g->edges[i].end]
                    && distance[g->edges[i].start] != 2147483647) {
                        // there must be a negative cycle
                        cout << "FALSE" << endl;
                        return;
                }

        // print out results
        cout << "TRUE" << endl;
        for (i = 0; i < g->verts; i++)
                cout << (distance[i] == 2147483647 ? "INFINITY" : to_string(distance[i])) << endl;
}