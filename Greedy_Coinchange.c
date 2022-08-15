#include<stdio.h>
#include<stdlib.h>

void main()
{
    int i, j, k = 0, noofcoins, temp, sum;
    system("cls");
    printf("Enter the number of coins: ");
    scanf("%d",&noofcoins);
    int* coins = (int*)malloc(noofcoins * sizeof(int));

    printf("Enter the coins: (preferably descending order): ");
    for(i = 0; i < noofcoins; i++)
        scanf("%d",&coins[i]);
    
    for(i = 1; i < noofcoins; i++)
        for(j = 0; j < noofcoins - i; j++)
            if(coins[j + 1] > coins[j])
            {
                temp = coins[j + 1];
                coins[j + 1] = coins[j];
                coins[j] = temp;
            }

    printf("\nEnter the Sum to be repaid: ");
    scanf("%d",&sum);

    int* selected_coins = (int*)malloc(sum * sizeof(int));
    while(sum > 0)
    {
        for(i = 0; i < noofcoins; i++)
            if(coins[i] <= sum)
            {
                sum -= coins[i];
                selected_coins[k++] = coins[i];
                break;
            }    
    }
    printf("\nSelected Coins: ");
    for(i = 0; i < k; i++)
        printf("%d ",selected_coins[i]);
}