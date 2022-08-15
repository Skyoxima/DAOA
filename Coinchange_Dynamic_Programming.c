#include<stdio.h>
#include<stdlib.h>

void initializer(int noofcoins, int sum, int soln_matrix[][sum + 1]) //not an n x n matrix therefore two parameters needed, soln_matrix[][total noofcolumns]
{
    int i, j;

    for(i = 0; i <= noofcoins; i++)
    {
        for(j = 0; j <= sum; j++)
        {
            soln_matrix[i][j] = 0;
        }
    }
}

void printer(int noofcoins, int sum, int matrix[][sum + 1]) //! V. IMP.: check how the matrix size is passed
{
    int i, j;

    for(i = 0; i <= noofcoins; i++)
    {
        for(j = 0; j <= sum; j++)
            printf("SM[%d][%d]: \033[1m\033[38;5;225m%d \033[0m", i, j, matrix[i][j]);
        printf("\n");
    }
}

int* coinchange(int noofcoins, int sum, int soln_matrix[][sum + 1], int* coins)
{
    int i = 1, j = 1, k;
    static int* selected_coins;
    selected_coins = (int*)malloc((sum) * sizeof(int));

    for(j = 1; j <= sum; j++)               //j goes from 1 to 8
    {
        for(i = 1; i <= noofcoins; i++)     //i goes from 1 to 3, this is a column-wise traversal, [1,1] [2,1] [3,1]
        {
            if(i == 1 && j < coins[i])
                soln_matrix[i][j] = 999;    // infinity

            else if(j < coins[i])
                soln_matrix[i][j] = soln_matrix[i - 1][j];
            
            else if(i == 1 || i == j)
                soln_matrix[i][j] = 1 + soln_matrix[1][j - coins[i]];
            
            else
            {
                if(soln_matrix[i - 1][j] < (1 + soln_matrix[i][j - coins[i]]))
                    soln_matrix[i][j] = soln_matrix[i - 1][j];
                else
                    soln_matrix[i][j] = 1 + soln_matrix[i][j - coins[i]];
            }
        }
    }
    
    i = noofcoins; 
    j = sum; 
    k = 0;
    selected_coins[k] = 0;
    while(j > 0)
    {
        if(soln_matrix[i][j] == soln_matrix[i - 1][j])
            i--;
        else
        {
            selected_coins[k] = coins[i];
            k++;
            j -= coins[i];
        }
    }

    selected_coins[k] = -1;
    return selected_coins;
}

void main()
{
    int noofcoins = 0, i, j, k, sum;           
    int* coins;
    int* selected_coins;         
    system("cls");

    printf("Enter the number of coins available: ");
    scanf("%d",&noofcoins);
    coins = (int*)malloc((noofcoins) * sizeof(int));

    printf("\n");
    coins[0] = 0;
    for(i = 1; i <= noofcoins; i++)
    {
        printf("Enter Coin %d: ", i);
        scanf("%d",&coins[i]);
    }

    printf("\nNow enter the amount sum to be achieved: ");
    scanf("%d",&sum);

    int soln_matrix[noofcoins + 1][sum + 1];                // +1 because >> for e.g: rows ~ 0, 1, 2, 3 and columns ~ 0, 1, 2, 3, 4, 5, 6, 7, 8         
    initializer(noofcoins, sum, soln_matrix);

    selected_coins = coinchange(noofcoins, sum, soln_matrix, coins);
    printf("\nWork Matrix: \n\n");
    printer(noofcoins, sum, soln_matrix);
    
    printf("\nSelected coins to pay the sum: ");
    for(i = 0; selected_coins[i] != -1; i++)
        printf("%d ", selected_coins[i]);
    printf("\n\n"); 
}