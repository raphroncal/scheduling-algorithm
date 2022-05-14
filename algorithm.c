#include <stdio.h>
#include <string.h>
#include "algorithm.h"

const int COL = 6;

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

/**
 * @brief implements the SRTF CPU scheduling algorithm
 *
 * @param size - number of parameters
 * @param input - input file in the form of 2d array
 */
void shortestRemainingTimeFirst(int size, int input[][COL])
{
    int i;
    int time = 1;
    int startTimes[size];
    int endTimes[size];
    int waitTimes[size];

    // initialize all elements to zero
    memset(startTimes, -1, size * sizeof(startTimes[0]));
    memset(endTimes, -1, size * sizeof(endTimes[0]));
    memset(waitTimes, 0, size * sizeof(waitTimes[0]));

    // check if all processes are done
    while (isDone(size, input))
    {
        sortByBurstTime(size, input);
        sortByWaitTime(size, input);
        // check if process has arrived
        if (input[0][1] = 0)
        {
            // check if the process has already ended
            if (endTimes[0] == -1)
            {
                // check if process has already started before. if not, note it down.
                if (startTimes[0] == -1)
                    startTimes[0] = time;

                input[0][2]--;

                // if burst time became zero after decrementing, assign sentinel value of 999 to wait time to push it to the back of the array
                // also take note of the end time
                if (input[0][2] == 0)
                {
                    input[0][1] = 999;
                    endTimes[0] = time;
                }
            }
        }

        // add wait time since this process has not yet arrived
        else
        {
            waitTimes[0]++;
        }

        // check if the rest of the processes are done
        if (input[1][1] != 999)
            // increment wait times for all unfinished processes while decreasing the arrival time for processes not zero
            for (i = 1; i < size; i++)
            {
                waitTimes[i]++;
            }

        time++;
    }
}

// TODO
void roundRobin(int size, int queue, int input[][COL])
{
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

int isDone(int size, int input[][COL])
{
    int sentinel = 1;
    int i = 0;

    while (sentinel)
    {
        if (input[i][1] != 999)
            ;
    }
}

void printArray(int size, int input[][COL])
{
    int i;

    for (i = 0; i < size; i++)
        printf("%d %d %d\n", input[i][0], input[i][1], input[i][2]);
}