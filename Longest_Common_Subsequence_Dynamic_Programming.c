#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void printer(int n1, int n2, int matrix[][n2 + 1]) //! check how the matrix size is passed 
{
    int i, j;

    for(i = 0; i <= n1; i++)
    {
        for(j = 0; j <= n2; j++)
            printf("SM[%d][%d]: \033[1m\033[38;5;225m%d \033[0m", i, j, matrix[i][j]);
        printf("\n");
    }
}


void longest_common_subsequence(int n1, int n2, char X[n1], char Y[n2], int sol_mx[][n2 + 1], int LCS[n2])
{
    int i, j, temp1, temp2, s_index = n2;

    for(i = 0; i < n2; i++)
        LCS[i] = -1;

    for(i = 1; i <= n1; i++)
    {
        for(j = 1; j <= n2; j++)
        {
            if(X[i - 1] == Y[j - 1])    //* since the indexing starts from zero for the char arrays
                sol_mx[i][j] = 1 + sol_mx[i - 1][j - 1];
            else
            {
                temp1 = sol_mx[i - 1][j];   //upper element
                temp2 = sol_mx[i][j - 1];    //left element
                
                if(temp1 > temp2)
                    sol_mx[i][j] = temp1;
                else
                    sol_mx[i][j] = temp2;
            }        
        }
    }

    //solution, the actual subsequence.. backtracking usage is necessary incase of multiple answers (although this program will not give multiple answers)
    i = n1; j = n2;
    while(i != 0)
    {
        if(X[i - 1] == Y[j - 1])
        {
            LCS[j - 1] = j - 1;
            i--;
            j--;
        }
        
        else
        {
            temp1 = sol_mx[i - 1][j];
            temp2 = sol_mx[i][j - 1];

            if(temp1 > temp2)
                i--;
            else
                j--;
        }
    }
}

void main()
{
    system("cls");

    int i, j, k, n1, n2;

    printf("\nEnter the number of characters in String 1: ");
    scanf("%d", &n1);
    char X[n1];
    getchar();
    printf("Enter String 1: ");
    fgets(X, n1 + 1, stdin);                //simple gets is risky, it doesn't check for bounds set and can cause an overflow, hence using fgets
    getchar();

    printf("\nEnter the number of characters in String 2: ");
    scanf("%d", &n2);
    char Y[n2];
    int LCS[n2];
    getchar();
    printf("Enter String 2: ");
    fgets(Y, n2 + 1, stdin);
    getchar();

    int soln_mx[n1 + 1][n2 + 1]; //here you give the size of the matrix so that is why +1, 0 indexing is disregarded
    for(i = 0; i <= n1; i++)
        for(j = 0; j <= n2; j++)
            soln_mx[i][j] = 0;

    longest_common_subsequence(n1, n2, X, Y, soln_mx, LCS);
    printf("\n\n\033[4m\033[38;5;207mFinal Matrix:\n\033[0m");
    printer(n1, n2, soln_mx);

    printf("\n\033[1m\033[4m\033[38;5;210mCharacters of the subsequence:\033[0m ");
    for(i = 0; i < n2; i++)
        if(LCS[i] != -1)
            printf("%c ", Y[LCS[i]]);
}

//! Index Glossary
// X - 0 to n1 - 1
// Y - 0 to n2 - 1
// soln_mx 0 to n1 and 0 to n2
// LCS - 0 to n2 - 1, same as Y 