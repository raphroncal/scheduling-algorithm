#include <stdio.h>

const int COL = 3;

void firstComeFirstServe(int num, int input[][COL])
{
    printf("FCFS\n");
    // TODO
}

void shortestJobFirst(int input[][COL])
{
    printf("SJF\n");
    // TODO
}

void shortestRemainingTimeFirst(int num, int input[][COL])
{
    printf("SRTF\n");
    // TODO

    int i, j;
    printf("Input:\n");
    for (i = 0; i < num; i++)
    {
        for (j = 0; j < COL; j++)
        {
            printf("%d ", input[i][j]);
        }
        printf("\n");
    }
}

void roundRobin(int input[][COL])
{
    printf("Round Robin\n");
    // TODO
}