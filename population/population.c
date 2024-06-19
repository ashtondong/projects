#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    float start;
    do
    {
        start = get_float("Start size: \n");
    }
    while (start < 9);

    // TODO: Prompt for end size
    long end;
    do
    {
        end  = get_float("End size: \n");
    }
    while (end < start);
    // TODO: Calculate number of years until we reach threshold
    int years = 0;
    int n = start;
    while (n < end)
    {
        n = n + (n / 3) - (n / 4);
        years++;
    }
    // TODO: Print number of years

    printf("Years: %i \n", years);
}
