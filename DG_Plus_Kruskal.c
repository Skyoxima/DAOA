//Dynamic Graph Implementation (HN Sir method)
// Here we first take in the number of nodes the graph will have.
// Then we ask the edges it will make with others, along with respective weights of that edges.

#include<stdio.h>
#include<stdlib.h>
#define MAX 30

typedef struct Graph_Edge
{
    int src, dest, weight; //each edge has 3 values: source, destination and weight
}Edge;
 
typedef struct Graph_Node
{
    int data;                       //has the node/vertex Number
    int weight;                     //! when the node is the destination, in the adjacency list the weight to get to it will be stored here
    struct Graph_Node* link;        //address of the node the current node is connected to cause linked list
    Edge indv_edge_list[MAX];            //?-- TRY THIS? --done
    int no_of_edges;
}Node; 

//! Global array for all the edges, had to keep it global cause readGraph is returning 'graph'
Edge edge_list[3 * MAX]; 
int total_edge_count = 0;

typedef struct Graph
{
    Node* head[MAX]; //array of Node type linked list
}Graph;

Graph* readGraph(int n) //taking in the number of nodes
{
    int i, j, links, from, to, weight;
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    
    for(i = 0; i < n; i++)
    {
        graph -> head[i] = (Node*)malloc(sizeof(Node));
        graph -> head[i] -> link = NULL;
        graph -> head[i] -> data = i;
        graph -> head[i] -> weight = 0;     //*each starting node's weight-to-get-to will be zero

        printf("\nFor Node %d:\n", i);
        printf("Enter the number of Edges: ");
        scanf("%d",&links);
        graph -> head[i] -> no_of_edges = links;

        for(j = 0; j < links; j++)
        {
            printf("Enter edge (format:- dest, weight): ");
            scanf("%d, %d", &to, &weight);

            //!this is essentially making a list of all the edges, global 'edge_list'
            edge_list[total_edge_count].src = i;     
            edge_list[total_edge_count].dest = to;
            edge_list[total_edge_count].weight = weight;
            total_edge_count += 1;

            //! this is giving each node's edge_list a 'Edge' type data
            graph -> head[i] -> indv_edge_list[j].src = i; 
            graph -> head[i] -> indv_edge_list[j].dest = to;
            graph -> head[i] -> indv_edge_list[j].weight = weight;

            Node *temp = (Node*)malloc(sizeof(Node));
            temp -> data = to;
            temp -> weight = weight;             //weight to get to this node
            temp -> link = NULL;

            Node *current = graph -> head[i];   //*Node currently indexed by i in the head array of the Graph Structure
            while(current -> link != NULL)
                current = current -> link;

            current -> link = temp;
        }
    }

    return graph;
}

void adj_list(Graph* graph, int n)
{
    printf("Adjacency List:\n");
    for(int i = 0; i < n; i++)
    {
        Node *p = graph -> head[i];
        for(p = graph -> head[i]; p -> link != NULL; p = p -> link)
        {
            printf("%d (%d) --> ", p -> data, p -> weight);
        }
        printf("%d (%d) --> NULL", p -> data, p -> weight);
        printf("\n");
    }
}

void print_edges_per_Node(Graph* graph, int n)
{
    int i, j;

    for(i = 0; i < n; i++)
    {
        printf("\nFor Node %d:\n", i);
        for(j = 0; j < graph -> head[i] -> no_of_edges; j++)
        {
            printf("Source: %d, Destination: %d, Weight: %d\n", 
                    graph -> head[i] -> indv_edge_list[j].src, 
                    graph -> head[i] -> indv_edge_list[j].dest, 
                    graph -> head[i] -> indv_edge_list[j].weight); //for this one, 'source' can be removed...
        }
    }

}

void sort_edges_by_weight(Edge *total_edge_list)
{
    int i, j;
    Edge temp;
    for(i = 1; i < total_edge_count; i++)
    {
        for(j = 0; j < total_edge_count - i; j++)
        {
            if(total_edge_list[j].weight > total_edge_list[j + 1].weight)
            {
                temp = total_edge_list[j];
                total_edge_list[j] = total_edge_list[j + 1];
                total_edge_list[j + 1] = temp;
            }
        }
    }
}

Edge* remove_repeats(Edge *total_edge_list, Edge* new_list)
{
    int i, j = 0, k = 0;

    for(i = 0; i < total_edge_count; i++)
    {
        for(j = i + 1; j < total_edge_count; j++)
        {
            if((total_edge_list[j].weight == total_edge_list[i].weight) && (total_edge_list[j].src == total_edge_list[i].dest && total_edge_list[j].dest == total_edge_list[i].src))
            {
                new_list[k] = total_edge_list[i];
                k++;
                break;
            }
        }
    }
    return new_list;
} 

void update_parent(int* parents_array, Edge curr_edge, int noofnodes)
{
    int i;
    for(i = 0; i < noofnodes; i++)
        if(parents_array[i] == parents_array[curr_edge.dest])
            parents_array[i] = parents_array[curr_edge.src];
}

void Kruskals(Edge* prcsd_edge_list, int noofnodes)
{
    Edge* MST = (Edge*)malloc((noofnodes - 1) * sizeof(Edge));
    int* parents = (int*)malloc(((noofnodes) * sizeof(int)));
    int i = 0, j, k = 0, min_cost = 0;

    for(j = 0; j < noofnodes; j++)
        parents[j] = j;

    for(i = 0; i < total_edge_count / 2; i++)
    {
        if(k == noofnodes - 1)
            break;
            
        if(parents[prcsd_edge_list[i].src] != parents[prcsd_edge_list[i].dest])
        {
            MST[k] = prcsd_edge_list[i];
            update_parent(parents, prcsd_edge_list[i], noofnodes);
            k++;
        }
    }

    printf("\n\nThe Minimum Spanning Tree: ");
    for(j = 0; j < (noofnodes - 1); j++)
    {
        printf("\n%d -> %d : %d", MST[j].src, MST[j].dest, MST[j].weight);
        min_cost += MST[j].weight;
    }
    printf("\nCost of the Minimum Spanning Tree: %d units.", min_cost);
}

void main()
{
    int i, j, noofnodes, count;
    Graph* Main_Graph = NULL;
    system("cls");
    Edge new_list[3 * MAX];

    printf("Enter the number of Nodes required in the Graph: ");
    scanf("%d",&noofnodes);

    Main_Graph = readGraph(noofnodes); //!
    printf("\n");

    adj_list(Main_Graph, noofnodes); //!
    printf("\n\n");

    printf("\nAll the Edges: \n");
    for(i = 0; i < total_edge_count; i++)
        printf("(%d, %d, %d) ",edge_list[i].src, edge_list[i].dest, edge_list[i].weight);

    sort_edges_by_weight(edge_list); //!
    printf("\nAll the Edges (Sorted by weights): \n");
    for(i = 0; i < total_edge_count; i++)
        printf("(%d, %d, %d) ",edge_list[i].src, edge_list[i].dest, edge_list[i].weight);

    remove_repeats(edge_list, new_list); //!
    printf("\nRepeats removed: \n");
    for(i = 0; i < total_edge_count / 2; i++)
        printf("(%d, %d, %d) ",new_list[i].src, new_list[i].dest, new_list[i].weight);

    Kruskals(new_list, noofnodes);
}

//in the Node structure definition, I have written data and weight separately to write comments, no other reason
//What if each node has an array of Edges, just that it will only contain all the edges that node is the source of -- implemented