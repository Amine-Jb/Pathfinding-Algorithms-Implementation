#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

//This implementation is using an adjacency list.


//this structure is a custom data type that represents a node in the graph, consisting the destination of the node, weight of the edge, and .
typedef struct Node {
    int dest;
    int weight;
    struct Node* next;
} Node;

//this structure is a custom data type that represents a graph, consisting of the number of vertices (V), the number of edges (E), and an array of edges (edges).
typedef struct Graph {
    int V;
    Node** array;
} Graph;

Graph* createGraph(int V) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->V = V;
    graph->array = (Node**)malloc(V*sizeof(Node*));
    for(int i=0; i<V; i++) {
        graph->array[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = graph->array[src];
    graph->array[src] = newNode;
}

void BellmanFord(Graph* graph, int src) {
    int V = graph->V;
    int dist[V];
    for(int i=0; i<V; i++) {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;

    for(int i=1; i<V; i++) {
        for(int j=0; j<V; j++) {
            Node* currentNode = graph->array[j];
            while(currentNode != NULL) {
                if(dist[j] != INT_MAX && dist[j] + currentNode->weight < dist[currentNode->dest]) {
                    dist[currentNode->dest] = dist[j] + currentNode->weight;
                }
                currentNode = currentNode->next;
            }
        }
    }

    for(int i=0; i<V; i++) {
        printf("Vertex %d distance from source is: %d\n", i, dist[i]);
    }
}

int main() {
    int V = 5;
    Graph* graph = createGraph(V);

    addEdge(graph, 0, 1, -1);
    addEdge(graph, 0, 2, 4);
    addEdge(graph, 1, 2, 3);
    addEdge(graph, 1, 3, 2);
    addEdge(graph, 1, 4, 2);
    addEdge(graph, 3, 2, 5);
    addEdge(graph, 3, 1, 1);
    addEdge(graph, 4, 3, -3);

    BellmanFord(graph, 0);

    return 0;
}