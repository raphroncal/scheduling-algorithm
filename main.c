#include <stdio.h>
#include <stdlib.h>
#include "algorithm.h"

int main()
{
    int X, Y, Z;
    int i;
    char filename[20];
    FILE *fp;

    printf("Enter file name: ");
    scanf("%s", filename);

    if ((fp = fopen(filename, "r")) == NULL)
    {
        printf("%s not found", filename);
        exit(1);
    }

    fscanf(fp, "%d %d %d", &X, &Y, &Z);

    int input[Y][COL];

    for (i = 0; i < Y; i++)
    {
        fscanf(fp, "%d %d %d", &input[i][0], &input[i][1], &input[i][2]);
        input[i][3] = -1;
        input[i][4] = -1;
        input[i][5] = 0;
    }

    fclose(fp);

    switch (X)
    {
    case 0:
        firstComeFirstServe(Y, input);
        break;

    case 1:
        shortestJobFirst(input);
        break;

    case 2:
        shortestRemainingTimeFirst(Y, input);
        break;

    case 3:
        roundRobin(Y, Z, input);
        break;
    }

    return 0;
}