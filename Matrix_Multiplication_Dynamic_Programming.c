#include<stdio.h>
#include<stdlib.h>
//TBR - Towards Bottom Right (Diagonal Direction)

void initializer(int n, int matrix[][n]) //C99 allows this, column size should be passed before the matrix
{
    int i, j;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            if(j >= i)
                matrix[i][j] = 0;
            else
                matrix[i][j] = -1;
    }
}

void printer(int n, int matrix[][n])
{
    int i, j;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
            if(j >= i)
                printf("%d ", matrix[i][j]);
            else
                printf("  ");
        printf("\n");
    }
}

void print_parenthesis(int n, int matrix[][n], int i, int j)
{
    if(i == j)
        printf(" M%d ", i);
    else
    {
        printf("(");
        print_parenthesis(n, matrix, i, matrix[i][j]);
        print_parenthesis(n, matrix, matrix[i][j] + 1, j);
        printf(")");
    }
}

void main()
{
    int n = 0, i, j, k, min = 32767, temp, min_k, count, gap = 1;           //setting min to effective inf., this will be resetted after each cell gets it's min
    int* dims;                                                              //gap is the difference between i and j for each diagonal
    system("cls");

    //take input, asking for number of matrices.
    printf("Enter the number of matrices in the sequence: ");
    scanf("%d",&n);
    dims = (int*)malloc((n + 1) * sizeof(int));
    //UP: number of dimensions will be +1 of number of matrices needed

    printf("\n");
    for(i = 0; i <= n; i++)
    {
        printf("Enter P%d: ", i);
        scanf("%d",&dims[i]);
    }

    //substructure preparation
    int substructure[n][n];         //C99 allows this
    initializer(n, substructure);
 
    //parenthesization preparation
    int parenthesis[n][n];          
    initializer(n, parenthesis);

    //optimization, indexing starts from zero hence a slight change in the formula
    count = n - 1; // number of TBR diagonals to be traversed
    while(count > 0)
    {
        for(i = 0, j = gap; j < n; i++, j++)
        {
            for(k = i; k < j; k++)
                {
                    temp = substructure[i][k] + substructure[k + 1][j] + (dims[i] * dims[k + 1] * dims[j + 1]);
                    printf("\ni = %d, j = %d, k = %d, %d",i, j, k, temp); //clarification purpose
                    if(temp < min)            //of all values for all k, choosing the minimum one
                    {
                        min = temp;
                        min_k = k;
                    }
                }
                substructure[i][j] = min;
                parenthesis[i][j] = min_k;
                printf("\nFor cell [%d, %d], chosen value: \033[0;32m %d units. \033[0m\n", i, j, min);
                min = 32767;
        }
        gap++;
        count--;
    }

    printf("\n\nOptimal Substructure: \n");
    printer(n, substructure);
    printf("\nTherefore the optimum cost for matrix chain multiplication is: \033[1;32m %d units.\033[0m", substructure[0][n - 1]);

    printf("\n\nParenthesization Matrix (index-based): \n");
    printer(n, parenthesis);
    printf("\nTherefore, the optimal parenthesization (index-based) is: \n");

    print_parenthesis(n, parenthesis, 0, n - 1);
}
