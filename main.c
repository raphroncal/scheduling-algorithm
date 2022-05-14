#include <stdio.h>
#include <stdlib.h>

int main()
{
    int X, Y, Z;
    int i;
    char filename[20];
    FILE *fptr;

    printf("Enter file name: ");
    scanf("%s", filename);

    if ((fptr = fopen(filename, "r")) == NULL)
    {
        printf("%s not found", filename);
        exit(1);
    }

    fscanf(fptr, "%d %d %d", &X, &Y, &Z);

    int input[Y][3];

    for (i = 0; i < Y; i++)
    {
        fscanf(fptr, "%d %d %d", &input[i][0], &input[i][1], &input[i][2]);
    }

    fclose(fptr);

    printf("X = %d\nY = %d\nZ = %d\n\n", X, Y, Z);

    int j;
    printf("Input:\n");
    for (i = 0; i < Y; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%d ", input[i][j]);
        }
        printf("\n");
    }

    return 0;
}