#include<stdio.h>
#include<stdlib.h>

typedef struct Graph_Edge
{
    int src, dest, weight;
}Edge;

void prepare(Edge* edgelist, Edge* newlist, int TEC)
{
    int i, j, k = 0;
    Edge temp;

    //bubble sorting w.r.t weight
    for(i = 1; i < TEC; i++)
    {
        for(j = 0; j < TEC - i; j++)
        {
            if(edgelist[j].weight > edgelist[j + 1].weight)
            {
                temp = edgelist[j];
                edgelist[j] = edgelist[j + 1];
                edgelist[j + 1] = temp;
            }
        }
    }

    //removing repeats
    for(i = 0; i < TEC; i++)
    {
        for(j = i + 1; j < TEC; j++)
        {
            if((edgelist[j].weight == edgelist[i].weight) && 
               (edgelist[j].src == edgelist[i].dest && edgelist[j].dest == edgelist[i].src))
            {
                newlist[k] = edgelist[i];
                k++;
                break;
            }
        }
    }
}

void update_parents(int psrc, int pdest, int* parents, int noofnodes)
{
    int i = 0;
    for(i = 0; i < noofnodes; i++)
    {
        if(parents[i] == pdest)
            parents[i] = psrc;
    }
}

void Kruskals(Edge* newlist, int noofnodes, int TEC)
{
    Edge* MST = (Edge*)malloc((noofnodes - 1) * sizeof(Edge));
    int* parents = (int*)calloc(noofnodes, sizeof(int));
    int i, j, k = 0, p1, p2, MST_cost = 0;

    for(i = 0; i < noofnodes; i++)
        parents[i] = i;
    
    for(i = 0; i < TEC/2; i++)
    {
        if(k != noofnodes - 1)
        {
            p1 = parents[newlist[i].src];
            p2 = parents[newlist[i].dest];
            if(p1 != p2)
            {
                MST[k++] = newlist[i];
                update_parents(p1, p2, parents, noofnodes);
                MST_cost += newlist[i].weight;
            }
        }
    }

    printf("\n\nThe Minimum Spanning Tree is: \n");
    for(i = 0; i < noofnodes - 1; i++)
        printf("(%d, %d, %d) ", MST[i].src, MST[i].dest, MST[i].weight);
    printf("\n\nCost of the Minimum Spanning Tree: \033[1m\033[38;5;205m%d units.\033[0m", MST_cost);
}

void main()
{
    int i, j, k = 0, noofnodes, TEC = 0; //total edge count
    system("cls");

    printf("\nEnter the number of nodes in the required graph: ");
    scanf("%d",&noofnodes);

    int adj_matrix[noofnodes][noofnodes];        //if turbo c, then you will have to declare a static matrix before hand and fill it according to noofnodes, space wastage is inevitable
    Edge edgelist[noofnodes*(noofnodes - 1)];   //same here
    Edge newlist[noofnodes*(noofnodes - 1)/2];
    Edge MST[noofnodes - 1];

    printf("\nEnter the adjacency matrix (Enter 0 for no connection): \n");
    for(i = 0; i < noofnodes; i++)
        for(j = 0; j < noofnodes; j++)
        {
            scanf("%d",&adj_matrix[i][j]);
            if(adj_matrix[i][j] != 0)
            {
                edgelist[TEC].src = i;
                edgelist[TEC].dest = j;
                edgelist[TEC].weight = adj_matrix[i][j];
                TEC++;
            }    
        }

    prepare(edgelist, newlist, TEC); //sorting wrt weight first then removing repeats
    Kruskals(newlist, noofnodes, TEC);
}