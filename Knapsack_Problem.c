#include<stdio.h>
#include<stdlib.h>

typedef struct Item
{
    int item_no, value, weight;
    float VW_ratio, fraction;
}Item;

typedef struct Knapsack
{
    int max_capacity, curr_no_items;
    float  total_weight, curr_capacity, total_profit;
    Item* included_item_list; 
}Sack;

Item* take_items(int n)
{
    Item* item_list = (Item*)malloc(n * sizeof(Item));
    int i, value, weight;
    //when you use the object (array) itself to traverse / fill the data in, use '.', if you use a pointer to that object, use ' -> '
    for(i = 0; i < n; i++)
    {
        printf("For Item %d, enter it's Profit(Vi) & Weight(Wi): ", i + 1);
        scanf("%d, %d", &value, &weight);
        item_list[i].item_no = i + 1;
        item_list[i].value = value;
        item_list[i].weight = weight;
        item_list[i].VW_ratio = (float)value / weight;
        item_list[i].fraction = 1.0;
    }

    return item_list;
}

void sort_wrt_VW_ratio_descendingly(Item* item_list, int noofitems)
{
    int i, j;
    Item temp;

    for(i = 1; i < noofitems; i++)
    {
        for(j = 0; j < noofitems - i; j++)
        {   
            if(item_list[j].VW_ratio < item_list[j + 1].VW_ratio)
            {
                temp = item_list[j];
                item_list[j] = item_list[j + 1];
                item_list[j + 1] = temp;
            }
        }
    }
}

Sack fill_sack(Item* item_list, int noofitems)
{
    int i, is_full = 0;
    float fraction = 1.0;
    Sack sack;  //making a direct Knapsack object

    printf("\nEnter the Maximum Capacity of the Knapsack: ");
    scanf("%d",&sack.max_capacity);
    sack.curr_capacity = sack.max_capacity;
    sack.total_profit = 0.0;
    sack.total_weight = 0.0;
    sack.curr_no_items = 0;
    sack.included_item_list = (Item*)calloc(noofitems, sizeof(Item));

    for(i = 0; i < noofitems; i++)
    {
        if(is_full == 0)
        {
            if((item_list[i].weight > sack.curr_capacity))
            {
                fraction = (float)(sack.max_capacity - sack.total_weight)/item_list[i].weight;
                item_list[i].fraction = fraction;
                is_full = 1;
            }

            sack.included_item_list[sack.curr_no_items] = item_list[i];
            sack.curr_no_items++;
            sack.curr_capacity -= item_list[i].weight * fraction; //if the whole item is being added to the sack then multiplying the fraction (which would be 1.0) won't change anything, otherwise it will change the values as required
            sack.total_profit += item_list[i].value * fraction;
            sack.total_weight += item_list[i].weight * fraction; //should be equal to max_capacity ideally at the end of all iterations, can be less but not greater
        }
        
    }
    return sack;
}

void main()
{
    int n, i, j, k, value, weight;
    Item* item_list = NULL;
    Sack sack;
    // Item** test;  //if you really want to use '->' operator, pointer to a pointer(first index of a dynamically allocated array)
    system("cls");

    printf("\nEnter the number of items: ");
    scanf("%d",&n);

    item_list = take_items(n);
    // test = item_list;

    printf("\nInitial Table: ");
    printf("\nItem No.   Values   Weights       V/W");
    for(i = 0; i < n; i++)
        printf("\n  %d          %d         %d        %.2f", item_list[i].item_no, 
                                                            item_list[i].value, 
                                                            item_list[i].weight, 
                                                            item_list[i].VW_ratio);
    
    sort_wrt_VW_ratio_descendingly(item_list, n);
    printf("\n\nSorted Table (w.r.t V/W): ");
    printf("\nItem No.   Values   Weights       V/W");
    for(i = 0; i < n; i++)
        printf("\n  %d          %d         %d        %.2f", item_list[i].item_no, 
                                                            item_list[i].value, 
                                                            item_list[i].weight, 
                                                            item_list[i].VW_ratio);
    
    sack = fill_sack(item_list, n);
    printf("\n\nKnapsack Table (Items added to the knapsack): ");
    printf("\nItem No.     Values        Weights     Fractions");
    for(i = 0; i < sack.curr_no_items; i++)
    {
        if(sack.included_item_list[i].fraction != 1.0)
            printf("\033[1;31m");               //ANSI escape sequence for formatted text, format (color) should only apply if the last item is not whole
        
        printf("\n  %d          %.2f         %.2f        %.2f", sack.included_item_list[i].item_no, 
                                                              (float)sack.included_item_list[i].value * sack.included_item_list[i].fraction, 
                                                              (float)sack.included_item_list[i].weight * sack.included_item_list[i].fraction, 
                                                              sack.included_item_list[i].fraction);
        printf("\033[0m");
    }
        
    printf("\n\nCurrent weight of the Knapsack: %.2f\nProfit earned from the selected items: \033[1;32m %.2f \033[0m\n\n", sack.total_weight, sack.total_profit);
}