#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
int inc[50], w[50], sum, n;

int promising(int i, int wt, int total)
{
    return (((wt + total) >= sum) && ((wt == sum) || (wt + w[i + 1] <= sum)));
}

void sumset(int i, int wt, int total)
{
    int j;
    if (promising(i, wt, total))
    {
        if (wt == sum)
        {
            printf("{ ");
            for (j = 0; j <= i; j++)
                if (inc[j])
                    printf("%d ", w[j]);
            printf("} ");
        }
        else
        {
            inc[i + 1] = TRUE;
            sumset(i + 1, wt + w[i + 1], total - w[i + 1]);
            inc[i + 1] = FALSE;
            sumset(i + 1, wt, total - w[i + 1]);
        }
    }
}

void main()
{
    int i, j, n, temp, total = 0;
    system("cls");
    printf("\nEnter Count of Nos. in Set: ");
    scanf("%d", &n);
    printf("Enter the %d Numbers in the set: ", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &w[i]);
        total += w[i];
    }

    printf("\nEnter the sum to create subset: ");
    scanf("%d", &sum);
    for (i = 0; i <= n; i++)
        for (j = 0; j < n - 1; j++)
            if (w[j] > w[j + 1])
            {
                temp = w[j];
                w[j] = w[j + 1];
                w[j + 1] = temp;
            }

    printf("The given %d numbers of whole set in ascending order: ", n);
    for (i = 0; i < n; i++)
        printf("%d ", w[i]);
    
    if ((total < sum))
        printf("\n Subset is not possible");
    else
    {

        for (i = 0; i < n; i++)
            inc[i] = 0;
        printf("\n\n\033[1m\033[38;5;205mThe solution using backtracking is: \033[0m");
        sumset(-1, 0, total);
    }
}
