#include <cs50.h>
#include <stdio.h>
#include <string.h>

// check if a lowercase string's characters are in alpha order.
// if yes, print "Yes", if no, print "No".
int main(void)
{
    // get string input from user

    string input = get_string("Input string: ");

    int count = 1;

    // need 2x for loop to check each letter in string
    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (input[i] < input[i+1])
        {
            count++;
        }

    }

    if (count == strlen(input))
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }






}


// check order of letters, a < b in ascii
// print Yes if true, No if not true.

//WORDLE CODE

   if (9 > num_input && num_input > 4)
    {
        printf(GREEN"This is WORDLE50"RESET"\n");
        printf("You have 6 tries to guess the %i-letter word I'm thinking of\n", num_input);
        get_guess (num_input);
        return 0;
    }

    else