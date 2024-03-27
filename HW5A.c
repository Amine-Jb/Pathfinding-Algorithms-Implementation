#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

#define V 5


//This implementation is using an adjacency matrix.

//This function takes in two arrays: dist[], which holds the distances from the start node to all other nodes, and visited[], which keeps track of which nodes have been visited.
int minDistance(int dist[], bool visited[]) {
    //Initialize min to a very large value (using INT_MAX) and minIndex to 0.
    int min = INT_MAX, minIndex;
    //Loop through all the nodes in the graph, where V is the number of nodes.
    for(int i=0; i<V; i++) {
        //If the current node has not been visited yet and its distance is less than or equal to min, set min to its distance and minIndex to its index.
        if(visited[i] == false && dist[i] <= min) {
            min = dist[i];
            minIndex = i;
        }
    }
    //Return the index of the node with the minimum distance.
    return minIndex;
}


//This function takes in the start node, goal node, and the adjacency matrix of the graph and returns the heuristic (estimated) cost of traveling from the start node to the goal node.
int heuristic(int start, int goal, int graph[V][V]) {
    //In this implementation, the heuristic is simply the weight of the edge connecting the start node and the goal node.
    return graph[start][goal];
}


//This function takes in the adjacency matrix of the graph, the start node, and the goal node, and finds the shortest path using the A* algorithm.
void AStar(int graph[V][V], int start, int goal) {
    //Initialize an array dist[] to hold the distance from the start node to all other nodes.
    int dist[V];
    //Initialize an array visited[] to keep track of which nodes have been visited.
    bool visited[V];
    //Initialize an array cameFrom[] to keep track of the node that came before each node in the shortest path.
    int cameFrom[V];
    //Loop through all the nodes in the graph, where V is the number of nodes.
    for(int i=0; i<V; i++) {
        //Set the distance from the start node to node i to a very large value (using INT_MAX).
        dist[i] = INT_MAX;
        //Set visited[i] to false to indicate that node i has not been visited yet.
        visited[i] = false;
    }
    //Set the distance from the start node to itself to 0.
    dist[start] = 0;
    //Set the node that came before the start node to -1 (to indicate that there is no previous node).
    cameFrom[start] = -1;
    //Loop through all the nodes in the graph V-1 times (meaning until all nodes have been visited).
    for(int count=0; count<V-1; count++) {
        //Find the node u with the minimum distance from the start node that has not been visited yet.
        int u = minDistance(dist, visited);
        //Mark node u as visited.
        visited[u] = true;
        //This loop iterates through all the vertices v in the graph.
        for(int v=0; v<V; v++) {
            //The if condition checks if the vertex v has not been visited yet, there exists an edge between u and v, the shortest path to vertex u is not infinite, and if the sum of the shortest path to u, the weight of the edge from u to v, and the heuristic distance from v to the goal is less than the current shortest path to v.
            if(graph[u][v] && visited[v]==false && dist[u]!=INT_MAX && dist[u] + graph[u][v] + heuristic(v, goal, graph) < dist[v]) {
                //If the condition is satisfied, the shortest path to vertex v is updated by adding the weight of the edge from u to v to the shortest path to u.
                dist[v] = dist[u] + graph[u][v];
                //The cameFrom array is updated to record that u is the predecessor of v on the shortest path to v.
                cameFrom[v] = u;
            }
        }
    }
    //Finally, the function prints the shortest path by iterating from the goal vertex to the start vertex using the cameFrom array. It prints each vertex in the path in reverse order, from the goal to the start vertex.
    printf("Path: ");
    int current = goal;
    printf("%d ", current);
    while(current != start) {
        printf("%d ", cameFrom[current]);
        current = cameFrom[current];
    }
}

int main() {
    //Declaring a 2D array called "graph" of size V x V, where V is a constant representing the number of vertices in the graph. This array holds the weights between all pairs of vertices in the graph. Specifically here, it represents a weighted undirected graph with 5 vertices
    int graph[V][V] = {
        {0, 3, 2, 0, 0},
        {3, 0, 0, 2, 4},
        {2, 0, 0, 1, 0},
        {0, 2, 1, 0, 2},
        {0, 4, 0, 2, 0}
    };
    //Next, we call the Astar function with the parameteres of "graph" array containing the weights between all pairs of vertices, the start vertex 0, and the goal vertex which is 4.
    AStar(graph, 0, 4);
    return 0;
}