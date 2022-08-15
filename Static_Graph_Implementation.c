// #include<stdio.h>
// #include<stdlib.h>
// #define MAX 50

// typedef struct Graph_Vertex //it is the vertex of the graph itself
// {
//     int dest, weight;
//     struct Graph_Vertex *link;
// }Vertex;

// typedef struct Graph_Edge //this is supposed to be just the edge between the two vertices src and dest specify
// {
//     int src, dest, weight;
// }Edge;

// typedef struct Graph //It is having the array of linked lists, starting from 0
// {    
//     Vertex *head[MAX];
// }Graph;

// Graph* createGraph(Edge edges[], int n) // in parameters it is accepting an array of edges structure (array of structure)
// {
//     int i = 0, src, dest, weight;
//     Graph *graph = (Graph *)malloc(sizeof(Graph)); //malloc returning a pointer which can be used to access the array inside the Graph structure which then can be used to create the graph/getting all the nodes

//     for(i = 0; i < MAX; i++)
//     {
//         graph -> head[i] = NULL; //each array element currently pointing to nothing
//     }

//     //now adding the edges we get from the passed parameter one by one into the Graph
//     for(i = 0; i < n; i++)
//     {
//         src = edges[i].src;
//         dest = edges[i].dest;
//         weight = edges[i].weight;

//         Vertex *newNode = (Vertex*)malloc(sizeof(Vertex));
//         newNode -> dest = dest;
//         newNode -> weight = weight;

//         newNode -> link = graph -> head[src];
//         graph -> head[src] = newNode;

//         newNode = (Vertex*)malloc(sizeof(Vertex));
// 		newNode -> dest = src;
// 		newNode -> weight = weight;


// 		newNode -> link = graph -> head[dest];
// 		graph -> head[dest] = newNode;
//     }

//     return graph;
// } 

// void printGraph(Graph* graph)
// {
// 	int i;
// 	for (i = 0; i < MAX; i++)
// 	{
// 		// print the current vertex and all its neighbors
// 		Vertex* ptr = graph -> head[i];
// 		while (ptr != NULL)
// 		{
// 			printf("%d -> %d (%d)\t", i, ptr -> dest, ptr -> weight);
// 			ptr = ptr -> link;
// 		}

// 		printf("\n");
// 	}
// }

// void main()
// {
//     int no_of_edges;
//     Edge edges[] = {{0, 1, 6}, {1, 2, 7}, {2, 0, 5}, {2, 1, 4}, {3, 2, 10}, {4, 5, 1}, {5, 4, 3}};

//     no_of_edges = sizeof(edges)/sizeof(edges[0]);

//     Graph *graph = createGraph(edges, no_of_edges);

//     printGraph(graph);
// }

#include <stdio.h>
#include <stdlib.h>

// Define the maximum number of vertices in the graph
#define N 6

// Data structure to store adjacency list nodes of the graph
struct Node
{
	int dest, weight;
	struct Node* next;
};

// Data structure to store graph
struct Graph
{
	// An array of pointers to `Node` for representing adjacency list
	struct Node* head[N];
};

// Data structure to store graph edges
struct Edge {
	int src, dest, weight;
};

// Function to create an adjacency list from specified edges
struct Graph* createGraph(struct Edge edges[], int n)
{
	unsigned i;

	// allocate memory for the graph data structure
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));

	// initialize head pointer for all vertices
	for (i = 0; i < N; i++) {
		graph->head[i] = NULL;
	}

	// add edges to the directed graph one by one
	for (i = 0; i < n; i++)
	{
		// get the source and destination vertex
		int src = edges[i].src;
		int dest = edges[i].dest;
		int weight = edges[i].weight;

		// allocate new node of adjacency list from `src` to `dest`
		struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode->dest = dest;
		newNode->weight = weight;

		// point new node to current head
		newNode->next = graph->head[src];

		// point head pointer to a new node
		graph->head[src] = newNode;

		// allocate new node of adjacency list from `dest` to `src`
		newNode = (struct Node*)malloc(sizeof(struct Node));
		newNode->dest = src;
		newNode->weight = weight;

		// point new node to current head
		newNode->next = graph->head[dest];

		// change head pointer to point to the new node
		graph->head[dest] = newNode;
	}

	return graph;
}

// Function to print adjacency list representation of a graph
void printGraph(struct Graph* graph)
{
	int i;
	for (i = 0; i < N; i++)
	{
		// print the current vertex and all its neighbors
		struct Node* ptr = graph->head[i];
		while (ptr != NULL)
		{
			printf("%d -> %d (%d)\t", i, ptr->dest, ptr->weight);
			ptr = ptr->next;
		}

		printf("\n");
	}
}

// Weighted Directed Graph Implementation in C
int main(void)
{
	// input array containing edges of the graph (as per above diagram)
	// `(x, y, w)` tuple in the array represents an edge from `x` to `y`
	// having weight `w`
	struct Edge edges[] =
	{
		{ 0, 1, 6 }, { 1, 2, 7 }, { 2, 0, 5 }, { 2, 1, 4 },
		{ 3, 2, 10 }, { 4, 5, 1 }, { 5, 4, 3 }
	};

	// calculate the number of edges
	int n = sizeof(edges)/sizeof(edges[0]);

	// construct a graph from the given edges
	struct Graph *graph = createGraph(edges, n);

	// print adjacency list representation of a graph
	printGraph(graph);

	return 0;
}
