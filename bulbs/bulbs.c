#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{

    string word = get_string("Message: \n");

    int len = strlen(word);

    for (int w = 0; w < len; w++)
        // looping through each letter of the word
    {
        int arr[8] = {0};
        int j = word[w];
        int i = 0; // array index
        while (j > 0 && i < 8)
            //finding the binary code for each letter and appending to array
        {
            if (j % 2 != 0)
            {
                arr[i] = 1;

            }
            else
            {
                arr[i] = 0;
            }
            j = j / 2;
            i++;

        }
        //before losing data stored in arr, using a for loop to print items of array for one letter
        //lesson on a variable 'a' overriding another 'i' after the variable is finished executing
        for (int a = 7; a > -1; a--)
        {
            print_bulb(arr[a]);

        }
        printf("\n");



    }


}


void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
