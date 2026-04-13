#include <stdio.h>
#include <stdlib.h>

#define V 5
#define E 7   // Number of edges in the example

// Structure for an edge
typedef struct Edge {
    int src, dest, weight;
} Edge;

// Structure for Union-Find
int parent[V];
int rank[V];

void makeSet() {
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);   // Path compression
    return parent[x];
}

void unionSets(int x, int y) {
    int xroot = find(x);
    int yroot = find(y);

    if (xroot != yroot) {
        if (rank[xroot] < rank[yroot])
            parent[xroot] = yroot;
        else if (rank[xroot] > rank[yroot])
            parent[yroot] = xroot;
        else {
            parent[yroot] = xroot;
            rank[xroot]++;
        }
    }
}

// Compare function for qsort
int compareEdges(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

void kruskalMST() {
    Edge edges[E] = {
        {0,1,2}, {1,2,3}, {1,4,5}, {0,3,6},
        {2,4,7}, {1,3,8}, {3,4,9}
    };

    qsort(edges, E, sizeof(Edge), compareEdges);

    makeSet();

    printf("Kruskal's Algorithm - MST Edges:\n");
    printf("Edge \tWeight\n");

    int e = 0, i = 0;
    while (e < V - 1 && i < E) {
        Edge next_edge = edges[i++];
        int x = find(next_edge.src);
        int y = find(next_edge.dest);

        if (x != y) {
            printf("%d - %d \t%d\n", next_edge.src, next_edge.dest, next_edge.weight);
            unionSets(x, y);
            e++;
        }
    }
}

int main() {
    kruskalMST();
    return 0;
}