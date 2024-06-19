#include <stdio.h>
#include <cs50.h>
#include <string.h>

typedef struct
{

    string name;
    int votes;

}
candidate;

candidate get_candidate(string prompt);

int main(void)
{
    candidate president = get_candidate("Enter a candidate: ");
    printf("%s\n", president.name);
    printf("%i\n", president.votes);

    //creating an array of candidate types
    candidate candidates_array[3];
    for (int i = 0; i < 3; i++);
    {

        candidates_array[i] = get_candidates("Enter a candidate: ");

    }
    //to call a specific candidate info, you can use candidates[i].name or candidates[i].votes
    








}

candidate get_candidate(string prompt)
{
    printf("%s\n", prompt);

    //to access the attributes in the data type "candidate"
    //create a variable
    candidate c;
    c.name = get_string("Name: ");
    c.votes = get_int("Votes: ");

    return c;




}