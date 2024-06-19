//recursion coding practice
//collatz
#include <stdio.h>
#include <cs50.h>

//prototype collatz function

int collatz(int n);

int main(void)
{
    int n = get_int("Enter a number: ");
    collatz(n);
    printf("%i\n", collatz(n));


}

int collatz(int n)
{
    //base case
    if (n == 1)
    {
        return 0;
    }
    //for even numbers
    else if ((n % 2) == 0)
    {
        return 1 + collatz(n/2);

    }
    else
    {
        return 1 + collatz(3*n + 1);
    }

}