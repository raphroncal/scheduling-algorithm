#include <stdio.h>
// #include <string.h>
#include "algorithm.h"

const int COL = 6; // # of columns (3) + appended columns (start, end, & wait times)

void firstComeFirstServe(int size, int input[][COL])
{
    printf("FCFS\n");
    // TODO
        int i;
    float avg_wt = 0; // average waiting time
    
    sortByArrivalTime(size, input);
    
    // first process
    input[0][3] = input[0][1]; // start time = arrival time
    input[0][4] = input[0][1] + input[0][2]; // end = arrival + burst
    input[0][5] = (input[0][4] - input[0][1]) - input[0][2]; // wait = (end - arrival) - burst, aka 0
    
    // succeeding processes
    for (i = 1; i < size; i++)
    {
    	input[i][3] = input[i-1][4]; // start = end[i-1]
    	
    	while (input[i][3] < input[i][1]) // for IDLE TIME (if the next process hasn't arrived, increment the start time)
    	{
    		input[i][3]++;
		}
    	
    	input[i][4] = input[i][2] + input[i][3]; 
    	input[i][5] = (input[i][4] - input[i][1]) - input[i][2]; 
    	
    	if (input[i][5] < 0) // if waiting time is < 0
    		input[i][5] = 0;
    		
    	avg_wt += input[i][5];
	}
    
    avg_wt /= size;
    
    output(size, input);
    printf("Average Waiting Time: %.1f\n", avg_wt);
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
    int time = 0;

    // input[0][0] = id
    // input[0][1] = arrival time
    // input[0][2] = burst time
    // input[0][3] = start time
    // input[0][4] = end time
    // input[0][5] = wait time

    // check if all processes are done
    // while (!isDone(size, input) && time < 10)
    while (!isDone(size, input))
    {
        printf("Time: %d\n", time);
        printArray(size, input);

        sortByBurstTime(size, input);
        sortByArrivalTime(size, input);

        // check if process has arrived
        if (input[0][1] == 0)
        {
            // check if process has already started before. if not, note it down.
            if (input[0][3] == -1)
                input[0][3] = time;

            input[0][2]--;

            // if burst time became zero after decrementing, assign sentinel value of 999 to arrival time to push it to the back of the array
            // also take note of the end time
            if (input[0][2] == 0)
            {
                input[0][1] = SENTINEL;
                input[0][4] = time + 1;
            }
        }

        // add wait time and decrease arrival time since this process has not yet arrived
        else
        {
            input[0][1]--;
            input[0][5]++;
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

    int j;

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

void sortByArrivalTime(int size, int input[][COL])
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