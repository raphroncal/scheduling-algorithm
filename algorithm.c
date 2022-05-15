#include <stdio.h>
#include "algorithm.h"

const int COL = 6; // # of columns (3) + appended columns (start, end, & wait times)

// input[0][0] = id
// input[0][1] = arrival time
// input[0][2] = burst time
// input[0][3] = start time
// input[0][4] = end time
// input[0][5] = wait time

/**
 * @brief implements the FCFS CPU scheduling algorithm
 *
 * @param size - number of parameters
 * @param input - input file in the form of 2d array
 */
void firstComeFirstServe(int size, int input[][COL])
{
    int i;

    sortByArrivalTime(size, input);

    // first process
    input[0][3] = input[0][1];                               // start time = arrival time
    input[0][4] = input[0][1] + input[0][2];                 // end = arrival + burst
    input[0][5] = (input[0][4] - input[0][1]) - input[0][2]; // wait = (end - arrival) - burst, aka 0

    // succeeding processes
    for (i = 1; i < size; i++)
    {
        input[i][3] = input[i - 1][4]; // start = end[i-1]

        while (input[i][3] < input[i][1]) // for IDLE TIME (if the next process hasn't arrived, increment the start time)
            input[i][3]++;

        input[i][4] = input[i][2] + input[i][3];
        input[i][5] = (input[i][4] - input[i][1]) - input[i][2];

        if (input[i][5] < 0) // if waiting time is < 0
            input[i][5] = 0;
    }

    output(size, input);
}

/**
 * @brief implements the SJF CPU scheduling algorithm
 *
 * @param size - number of parameters
 * @param input - input file in the form of 2d array
 */
void shortestJobFirst(int size, int input[][COL])
{
    int i; // loop ctr

    sortByBurstTime(size, input);
    sortByArrivalTime(size, input);

    // first process
    input[0][3] = input[0][1];                               // start time = arrival time
    input[0][4] = input[0][1] + input[0][2];                 // end = arrival + burst
    input[0][5] = (input[0][4] - input[0][1]) - input[0][2]; // wait = (end - arrival) - burst, aka 0

    // succeeding processes
    for (i = 1; i < size; i++)
    {
        input[i][3] = input[i - 1][4]; // start = end[i-1]

        while (input[i][3] < input[i][1]) // for IDLE TIME (if the next process hasn't arrived, increment the start time)
        {
            input[i][3]++;
        }

        input[i][4] = input[i][2] + input[i][3];
        input[i][5] = (input[i][4] - input[i][1]) - input[i][2];

        if (input[i][5] < 0) // if waiting time is < 0
            input[i][5] = 0;
    }

    output(size, input);
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
    int time = 0;

    // check if all processes are done
    while (!isDone(size, input))
    {
        sortByBurstTime(size, input);
        sortByArrivalTime(size, input);

        // check if process has arrived
        if (input[0][1] == 0)
        {
            // check if process has already started before. if not, note it down.
            if (input[0][3] == -1)
                input[0][3] = time;

            // decrement burst time
            input[0][2]--;

            // if burst time became zero after decrementing, assign sentinel value of 999 to arrival time to push it to the back of the array
            // also take note of the end time
            if (input[0][2] == 0)
            {
                input[0][1] = SENTINEL;
                input[0][4] = time + 1;
            }
        }
        // decrease arrival time since this process has not yet arrived
        else
        {
            input[0][1]--;
        }

        // arrival and wait time adjustments for unfinished processes
        for (i = 1; i < size; i++)
            if (input[i][1] != SENTINEL)
            {
                // decrease arrival time unless the arrival time is already zero
                if (input[i][1] > 0)
                    input[i][1]--;
                // increase waiting time for those with arrival time zero
                else
                    input[i][5]++;
            }

        time++;
    }

    output(size, input);
}

/**
 * @brief implements the round robin CPU scheduling algorithm
 *
 * @param size - number of processes
 * @param q - time quantum
 * @param input - input file in the form of 2d array
 */
void roundRobin(int size, int quantum, int input[][COL])
{
    const int SENTINEL = 999;
    int i, j, k;
    int q;
    int time = 0;

    sortByArrivalTime(size, input);

    // check if all processes are finished
    while (!isDone(size, input))
    {
        // check if there is at least one process with arrival time zero
        if (hasAnyArrived(size, input))
        {
            for (i = 0; i < size; i++)
            {
                q = 0;
                // check if the current process has arrived
                if (input[i][1] == 0)
                {
                    // check if start time has been noted before
                    if (input[i][3] == -1)
                        input[i][3] = time;

                    // decrease burst time by time quantum until burst time becomes zero or time quantum has been fulfilled
                    while (input[i][2] != 0 && q < quantum)
                    {
                        input[i][2]--;
                        q++;
                        time++;
                    }

                    // check if burst time has been depleted
                    if (input[i][2] == 0)
                    {
                        input[i][1] = SENTINEL;
                        input[i][4] = time;
                    }

                    // decrease arrival time for unfinished processes and increase wait time for waiting processes
                    for (j = 0; j < size; j++)
                        // skip the current process
                        if (j != i && input[j][1] != SENTINEL)
                            // adjust time values depending on value of q
                            for (k = 0; k < q; k++)
                            {
                                // decrease arrival time unless the arrival time is already zero
                                if (input[j][1] > 0)
                                    input[j][1]--;
                                // increase waiting time for those with arrival time zero
                                else
                                    input[j][5]++;
                            }
                }
                // else, increment i and move to next process
            }
        }
        // if there are none, increase time and decrease arrival time for all processes except for those who are finished
        else
        {
            for (i = 0; i < size; i++)
                if (input[i][1] != SENTINEL)
                    input[i][1]--;

            time++;
        }
    }

    output(size, input);
}

/**
 * @brief sorts the processes by their burst times in ascending order
 *
 * @param size - number of processes
 * @param input - input file in the form of 2d array
 */
void sortByBurstTime(int size, int input[][COL])
{
    int temp;
    int step, i, j;

    for (step = 0; step < size - 1; ++step)
        for (i = 0; i < size - step - 1; ++i)
            if (input[i][2] > input[i + 1][2])
                for (j = 0; j < COL; j++)
                {
                    temp = input[i][j];
                    input[i][j] = input[i + 1][j];
                    input[i + 1][j] = temp;
                }
}

/**
 * @brief sorts the processes by their arrival times in ascending order
 *
 * @param size - number of processes
 * @param input - input file in the form of 2d array
 */
void sortByArrivalTime(int size, int input[][COL])
{
    int temp;
    int step, i, j;

    for (step = 0; step < size - 1; ++step)
        for (i = 0; i < size - step - 1; ++i)
            if (input[i][1] > input[i + 1][1])
                for (j = 0; j < COL; j++)
                {
                    temp = input[i][j];
                    input[i][j] = input[i + 1][j];
                    input[i + 1][j] = temp;
                }
}

/**
 * @brief sorts the processes by their end times in ascending order for output purposes
 *
 * @param size - number of processes
 * @param input - input file in the form of 2d array
 */
void sortByEndTime(int size, int input[][COL])
{
    int temp;
    int step, i, j;

    for (step = 0; step < size - 1; ++step)
        for (i = 0; i < size - step - 1; ++i)
            if (input[i][4] > input[i + 1][4])
                for (j = 0; j < COL; j++)
                {
                    temp = input[i][j];
                    input[i][j] = input[i + 1][j];
                    input[i + 1][j] = temp;
                }
}

/**
 * @brief checks all processes if they are finished by checking the arrival time
 *
 * @param size - number of processes
 * @param input - input file in the form of 2d array
 * @return int - 1 if all processes are done, 0 otherwise
 */
int isDone(int size, int input[][COL])
{
    int sentinel = 1;
    int i = 0;

    while (sentinel && i < size)
    {
        if (input[i][1] != 999)
            sentinel = 0;

        i++;
    }

    return sentinel;
}

/**
 * @brief checks all processes if at least one has an arrival time of zero
 *
 * @param size - number of processes
 * @param input - input file in the form of 2d array
 * @return int - 1 if there is a process that has arrived, 0 otherwise
 */
int hasAnyArrived(int size, int input[][COL])
{
    int sentinel = 0;
    int i = 0;

    while (!sentinel && i < size)
    {
        if (input[i][1] == 0)
            sentinel = 1;

        i++;
    }

    return sentinel;
}

/**
 * @brief displays each process' start, end, and waiting times
 *
 * @param size - number of processes
 * @param input  - input file in the form of 2d array
 */
void output(int size, int input[][COL])
{
    int i;
    float avg_wt = 0;

    sortByEndTime(size, input);

    for (i = 0; i < size; i++)
    {
        printf("P[%d] Start time: %d End time: %d | Waiting time: %d\n", input[i][0], input[i][3], input[i][4], input[i][5]);
        avg_wt += input[i][5];
    }

    printf("Average waiting time: %.1f", avg_wt / size);
}

/**
 * @brief displays the 2d array for testing purposes and has no effect on the final output
 *
 * @param size - number of processes
 * @param input - input file in the form of 2d array
 */
void printArray(int size, int input[][COL])
{
    int i, j;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < COL; j++)
            printf("%d ", input[i][j]);

        printf("\n");
    }

    printf("\n\n");
}