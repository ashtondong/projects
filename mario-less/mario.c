#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // create a # pyramid mimicking mario world 1-1

    // asking user for height input
    int height;
    do
    {

    height = get_int("Height: \n");

    }
    while (height <= 0);

    // writing for loop to create pyramid

    int n = 1;

    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < height - n; k++)
        {
            printf(" ");
        }
            for (int j = 0; j < height - (height - n); j++)
            {
                printf("#");
            }
            printf("\n");

        n++;

    }
}