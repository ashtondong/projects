#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Get array size
    int size;
    do
    {
        size = get_int("Declare array size: ");
    }
    while (size < 1);

    // declare array
    int array[size];

    // first array integer starts at 1
    array[0] = 1;
    printf("%i\n", array[0]);

    // as long as the index of the array is less than array size, double the integer
    for (int i = 1; i < size; i++)
    {
        //we want the current element to multiply 2 to the previous element of the array.
        array[i] = 2 * array[i-1];
        printf("%i\n", array[i]);

    }




    // Print array

}



