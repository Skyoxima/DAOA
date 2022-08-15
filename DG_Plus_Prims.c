#include<stdio.h>
#include<stdlib.h>
#define MAX 20

typedef struct Graph_Edge
{
    int src, dest, weight; 
}Edge;

typedef struct Edges_array
{
    Edge* edge_list;                        //dynamic array of edges
    int noofedges;
}Edge_list;

typedef struct Graph_Node
{
    int data;                       
    int weight;                     
    struct Graph_Node* link;
    Edge_list indv_edge_list;
}Node;

typedef struct Graph
{
    Node* head[MAX];                        //array of pointers of Node type linked list, pointers used cause malloc will be used to form a SLL
}Graph;


Graph* readGraph(int n, Edge_list* all_edges)     //taking in the number of nodes and a pointer to the object of Edge_list
{
    int i, j, links, from, to, weight;
    Graph* graph = (Graph*)malloc(sizeof(Graph)); 
    all_edges -> edge_list = (Edge*)malloc((n * (n - 1)) * sizeof(Edge)); //maximum possible total no. of edges for an directed (bidrected) graph having 'n' vertices
    all_edges -> noofedges = 0;

    for(i = 0; i < n; i++)
    {
        graph -> head[i] = (Node*)malloc(sizeof(Node));
        graph -> head[i] -> link = NULL;
        graph -> head[i] -> data = i;
        graph -> head[i] -> weight = 0;

        printf("\nFor Node %d:\n", i);
        printf("Enter the number of Edges: ");
        scanf("%d",&links);
        graph -> head[i] -> indv_edge_list.edge_list = (Edge*)malloc(links * sizeof(Edge));     
        graph -> head[i] -> indv_edge_list.noofedges = 0; 

        for(j = 0; j < links; j++)
        {
            printf("Enter edge (format:- dest, weight): ");
            scanf("%d, %d",&to,&weight);

            //a bit too lengthy haha
            graph -> head[i] -> indv_edge_list.edge_list[j].src = i;
            graph -> head[i] -> indv_edge_list.edge_list[j].dest = to;
            graph -> head[i] -> indv_edge_list.edge_list[j].weight = weight;
            graph -> head[i] -> indv_edge_list.noofedges++;

            Node* temp = (Node*)malloc(sizeof(Node));
            temp -> data = to;
            temp -> weight = weight;             
            temp -> link = NULL;

            Node* current = graph -> head[i];   
            while(current -> link != NULL)
                current = current -> link;

            current -> link = temp;
            
            all_edges -> edge_list[all_edges -> noofedges].src = i;     
            all_edges -> edge_list[all_edges -> noofedges].dest = to;
            all_edges -> edge_list[all_edges -> noofedges].weight = weight;
            all_edges -> noofedges++;
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
            printf("[%d] (%d) --> ", p -> data, p -> weight);
        }
        printf("[%d] (%d) --> NULL", p -> data, p -> weight);
        printf("\n");
    }
}

Edge find_min_weight_edge(Edge_list obj1, int* included) //returns minimum edge of a node
{
    int i, s, d;
    Edge min;
    min.weight = 32767;

    for(i = 0; i < obj1.noofedges; i++)
    {
        s = obj1.edge_list[i].src;
        d = obj1.edge_list[i].dest;

        if(!(included[s] == 1 && included[d] == 1))
        {
            if(min.weight > obj1.edge_list[i].weight)
                min = obj1.edge_list[i];
        }
    }
        
   return min;
}

Edge_list Prims(Graph* graph, int noofnodes, Edge_list all_edges)
{
    int i, j, k;
    Edge min_edge;
    Edge_list MST;
    int* included = (int*)malloc(noofnodes * sizeof(int));

    min_edge.weight = 32767;        //set infinite (so that the first one is always considered minimum)
    MST.edge_list = (Edge*)malloc((noofnodes - 1) * sizeof(Edge));
    MST.noofedges = 0;

    for(i = 0; i < noofnodes; i++)              // for excluding already included node (in the MST) checking
        included[i] = 0;

    min_edge = find_min_weight_edge(all_edges, included);
    included[min_edge.src] = 1;                  //marking the first node (node which is the source of minimum weight among all the edges of the graph) as included.
    min_edge.weight = 32767;

    while(MST.noofedges != noofnodes - 1)
    {
        for(i = 0; i < noofnodes; i++)
        {
            if(included[i] == 1) 
                if(find_min_weight_edge(graph -> head[i] -> indv_edge_list, included).weight < min_edge.weight)
                    min_edge = find_min_weight_edge(graph -> head[i] -> indv_edge_list, included);
        }

        MST.edge_list[MST.noofedges] = min_edge;
        included[min_edge.dest] = 1;
        min_edge.weight = 32767;
        MST.noofedges++;
    }
    return MST;
}

void main()
{
    int i, j, noofnodes, final_cost = 0;
    Graph* Main_Graph = NULL;
    Edge_list all_edges, MST;
    Edge_list* p_all_edges = &all_edges;        //a pointer to the Edge_list object has to be made to pass it in the readGraph function and create the whole edgelist without having to return the Edge_list object as readGraph is returning a Graph* already
    system("cls");

    printf("Enter the number of Nodes required in the Graph: ");
    scanf("%d",&noofnodes);

    Main_Graph = readGraph(noofnodes, p_all_edges); 
    printf("\n");

    adj_list(Main_Graph, noofnodes); 
    printf("\n");

    printf("\nAll the Edges: \n");
    for(i = 0; i < all_edges.noofedges; i++)
        printf("(%d, %d, %d) ",all_edges.edge_list[i].src, all_edges.edge_list[i].dest, all_edges.edge_list[i].weight);
    
    MST = Prims(Main_Graph, noofnodes, all_edges);
    printf("\n\nEdges included in the Minimum Spanning Tree:");
    for(i = 0; i < MST.noofedges; i++)
        {
            printf("\n%d <-> %d : %d ", MST.edge_list[i].src, MST.edge_list[i].dest, MST.edge_list[i].weight);
            final_cost += MST.edge_list[i].weight;
        }
    printf("\n\nCost of the Minimum Spanning Tree: \033[1;32m%d units.\033[0m",final_cost);   
}