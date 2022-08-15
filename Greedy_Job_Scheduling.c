#include<stdio.h>
#include<stdlib.h>

typedef struct Job
{
    int jobno, deadline, profit;
}Job;

void main()
{
    int i, j, k, noofjobs, MDL = -1, INDL, total_profit = 0, isnc = 0;
    Job temp;
    printf("\nEnter the number of jobs: ");
    scanf("%d",&noofjobs);
    Job jobs[noofjobs];

    printf("Enter the profits for each job: ");
    for(i = 0; i < noofjobs; i++)
        scanf("%d",&jobs[i].profit);
    
    printf("Enter the deadline for each job: ");
    for(i = 0; i < noofjobs; i++)
    {
        scanf("%d",&jobs[i].deadline);
        if(jobs[i].deadline > MDL)
            MDL = jobs[i].deadline;
        jobs[i].jobno = i + 1;
    }

    for(i = 1; i < noofjobs; i++)
        for(j = 0; j < noofjobs - i; j++)
        {
            if(jobs[j + 1].profit > jobs[j].profit)
            {
                temp = jobs[j + 1];
                jobs[j + 1] = jobs[j];
                jobs[j] = temp;
            }
        }

    Job schedule[MDL];
    Job not_completed[MDL];
    for(i = 0; i < MDL; i++)
        schedule[i].jobno = 0;
    
    for(i = 0; i < noofjobs; i++)
    {
        INDL = jobs[i].deadline;
        for(j = INDL - 1; j >= 0; j--)
        {
            if(schedule[j].jobno == 0)
            {
                schedule[j] = jobs[i];
                total_profit += schedule[j].profit;
                break;
            } 
            if(j == 0)
                not_completed[isnc++] = jobs[i];
        }
    }  

    printf("\n\nOptimal Job Sequence: \n");
    for(i = 0; i < MDL; i++)
        if(schedule[i].jobno != 0)
            printf("J%d - Completed at %d\n",schedule[i].jobno, i + 1);
    
    printf("Jobs not scheduled: ");
    for(i = 0; i < isnc; i++)
        printf("J%d ",not_completed[i].jobno);
    
    printf("\n\nMaximum profit: \033[1m\033[38;5;223m%d units.\033[0m", total_profit);
}