#include <stdio.h>
// #include <string.h>
#include "algorithm.h"

const int COL = 6; // # of columns (3) + appended columns (start, end, & wait times)

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
    const int SENTINEL = 999;
    int i;
    int time = 1;

    // start = input[0][3];
    // end = input[0][4];
    // wait = input[0][5];

    // check if all processes are done
    while (isDone(size, input))
    {
        sortByBurstTime(size, input);
        sortByWaitTime(size, input);

        // check if process has arrived
        if (input[0][1] == 0)
        {
            // check if the process has already ended
            if (input[0][4] == -1)
            {
                // check if process has already started before. if not, note it down.
                if (input[0][3] == -1)
                    input[0][3] = time;

                input[0][2]--;

                // if burst time became zero after decrementing, assign sentinel value of 999 to wait time to push it to the back of the array
                // also take note of the end time
                if (input[0][2] == 0)
                {
                    input[0][1] = SENTINEL;
                    input[0][4] = time;
                }
            }
        }

        // add wait time since this process has not yet arrived
        else
        {
            input[0][5]++;
        }

        // check if the rest of the processes are done except for the current process
        if (input[1][1] != SENTINEL)
            // increment wait times for all unfinished processes while decreasing the arrival time for processes not zero
            for (i = 1; i < size; i++)
            {
                // check if there still are unfinished processes after since there can still be more of them midway
                if (input[i][1] == SENTINEL)
                    input[i][5]++;
            }

        time++;
    }

    output(size, input);
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

void sortByEndTime(int size, int input[][COL])
{
    int temp;
    int step, i, j;

    for (int step = 0; step < size - 1; ++step)
        for (int i = 0; i < size - step - 1; ++i)
            if (input[i][4] > input[i + 1][4])
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

    while (sentinel && i < size)
    {
        if (input[i][1] != 999)
            sentinel = 0;
        else
            i++;
    }

    return sentinel;
}

void output(int size, int input[][COL])
{
    int i;

    sortByEndTime(size, input);

    for (i = 0; i < size; i++)
        printf("P[%d] Start time: %d End time: %d | Waiting time: %d\n", input[i][0], input[i][3], input[i][4], input[i][5]);
}