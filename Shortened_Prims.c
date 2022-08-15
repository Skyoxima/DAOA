#include<stdio.h>
#include<stdlib.h>

typedef struct Edge
{
    int src, dest, weight;
}Edge;

typedef struct Graph_Node
{
    Edge* IEL;    //indv_edge_list
    int noofedges;
}Node;

Edge find_MWE(Node* graphnodes, int* included, int noofnodes)
{
    int i, j, s, d, w;
    Edge MWE;
    MWE.weight = 32767;

    for(i = 0; i < noofnodes; i++)
    {
        if(included[i] == 1)
        {
            for(j = 0; j < graphnodes[i].noofedges; j++)
            {
                s = graphnodes[i].IEL[j].src;
                d = graphnodes[i].IEL[j].dest;
                w = graphnodes[i].IEL[j].weight;
                if(included[d] != 1)
                {
                    if(w < MWE.weight)
                    {
                        MWE.src = s;
                        MWE.dest = d;
                        MWE.weight = w;
                    }
                }
            }
        }
    }

    return MWE;
}

void Prims(Node* graphnodes, int noofnodes, Edge MWE)
{
    int i, j, k = 0, MST_cost = 0;
    int* included = (int*)calloc(noofnodes, sizeof(int));
    Edge* MST = (Edge*)malloc((noofnodes - 1)*sizeof(Edge));

    MST[k++] = MWE;
    included[MWE.src] = 1;
    included[MWE.dest] = 1;
    MST_cost += MWE.weight;

    while(k != noofnodes - 1)
    {
        MWE = find_MWE(graphnodes, included, noofnodes);
        MST[k++] = MWE;
        MST_cost += MWE.weight;
        included[MWE.dest] = 1;   
    }
    printf("\n\nThe Minimum Spanning Tree: \n");
    for(i = 0; i < noofnodes - 1; i++)
        printf("(%d, %d, %d) ", MST[i].src, MST[i].dest, MST[i].weight);
    printf("\nThe Minimum Cost: \033[1m\033[38;5;225m%d units.\033[0m", MST_cost);
}

void main()
{
    int i, j, k = 0, noofnodes;
    Edge MWE;
    MWE.weight = 32767;
    system("cls");

    printf("\nEnter the number of nodes in the graph: ");
    scanf("%d",&noofnodes);

    int adj_matrix[noofnodes][noofnodes];
    Node graphnodes[noofnodes];

    printf("\nEnter the graph in form of its adjacency matrix (Enter 0 for no connection): \n");
    for(i = 0; i < noofnodes; i++)
    {
        graphnodes[i].IEL = (Edge*)malloc((noofnodes*(noofnodes - 1)) * sizeof(Edge));
        graphnodes[i].noofedges = 0;

        for(j = 0; j < noofnodes; j++)
        {
            scanf("%d",&adj_matrix[i][j]);    
            if(adj_matrix[i][j] != 0)
            {
                graphnodes[i].IEL[graphnodes[i].noofedges].src = i;
                graphnodes[i].IEL[graphnodes[i].noofedges].dest = j;
                graphnodes[i].IEL[graphnodes[i].noofedges].weight = adj_matrix[i][j];
                
                if(adj_matrix[i][j] < MWE.weight)
                {
                    MWE.src = i;
                    MWE.dest = j;
                    MWE.weight = adj_matrix[i][j];
                }
                graphnodes[i].noofedges++;
            }
        }
    }

    Prims(graphnodes, noofnodes, MWE);
}