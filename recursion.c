#include <cs50.h>
#include <stdio.h>

void draw(int height);

int main(void)
{
    int height = get_int("Height: ");
    draw(height);


}

void draw(int height)
{
    //this is the base case to stop the recrusion
    if (height <= 0)
    {
        return;
    }
    //this is the recursion to construct the height needed
    //once this recursion hits the base case, it will stop and then execute by order of received in call stack.
    //use debug50 to see the recursion
    draw(height-1);

    //this is used to print the "mario blocks" per row
    for (int i = 0; i < height; i++)
    {
        printf("#");
    }
    printf("\n");



}