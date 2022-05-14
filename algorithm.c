#include <stdio.h>
#include "algorithm.h"

const int COL = 3;

void firstComeFirstServe(int size, int input[][COL])
{
    printf("FCFS\n");
    // TODO
}

void shortestJobFirst(int input[][COL])
{
    printf("SJF\n");
    // TODO
}

void shortestRemainingTimeFirst(int size, int input[][COL])
{
    printf("SRTF\n");
    // TODO

    // int i, j;
    // int endtime[size];

    sortByBurstTime(size, input);
}

void roundRobin(int size, int queue, int input[][COL])
{
    printf("Round Robin\n%d\n%d", size, queue);
    // TODO
    // int endtime[size];
    // int i, j;
}

void sortByBurstTime(int size, int input[][COL])
{
    int temp;
    int step, i, j;

    for (int step = 0; step < size - 1; ++step)
        for (int i = 0; i < size - step - 1; ++i)
            if (input[i][2] > input[i + 1][2])
                for (j = 0; j < COL; j++)
                {
                    temp = input[i][j];
                    input[i][j] = input[i + 1][j];
                    input[i + 1][j] = temp;
                }
}

void sortByWaitTime(int size, int input[][COL])
{
    int temp;
    int step, i, j;

    for (int step = 0; step < size - 1; ++step)
        for (int i = 0; i < size - step - 1; ++i)
            if (input[i][1] > input[i + 1][1])
                for (j = 0; j < COL; j++)
                {
                    temp = input[i][j];
                    input[i][j] = input[i + 1][j];
                    input[i + 1][j] = temp;
                }
}

void printArray(int size, int input[][COL])
{
    int i;

    for (i = 0; i < size; i++)
        printf("%d %d %d\n", input[i][0], input[i][1], input[i][2]);
}