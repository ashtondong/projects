#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
bool makes_cycle(int loser, int winner);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int k = 0; k < candidate_count; k++)
    {
        if (strcmp(candidates[k], name) == 0)
        {
            ranks[rank] = k;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int k = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[k].winner = i;
                pairs[k].loser = j;
                k++;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    pair switchvar;
    for (int k = 0; k < pair_count - 1; k++)
    {
        if ((preferences[pairs[k].winner][pairs[k].loser] - preferences[pairs[k].loser][pairs[k].winner]) < (preferences[pairs[k + 1].winner][pairs[k + 1].loser] - preferences[pairs[k + 1].loser][pairs[k + 1].winner]))
        {
            switchvar = pairs[k];
            pairs[k] = pairs[k + 1];
            pairs[k + 1] = switchvar;

        }
    }
    return;
}

//recurisve function checking for cycle with adding each edge
bool makes_cycle(int winner, int loser)
{
    //base case, if the loser equals to and loops back to the winner, then it creates a cycle
    if (locked[loser][winner] == true)
    {
        return true;
    }

    //now we're going to check each loser and see if the loser has previously been a winner.
    //if that loser previously beat someone who is beating their winner, then that's a loop.
    for (int i = 0; i < candidate_count; i++) //we're going to toggle through all of the candidates and see if the loser has previously beaten someone
    {
        if (locked[loser][i]) //if the loser has previously beaten someone, we have to see if that someone is creating a loop by beating their winner.
        {
            if (makes_cycle(winner, i)) //now we have to see if the person that the loser beat presviously, i, is beating the current winner.
            {
                return true;
            }
        }

    }

    return false; //need a global return, if none of the above are true, then there is no cycle (false)

}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    //for each pair
    for (int i = 0; i < pair_count; i++)
    {
        if (!makes_cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;

        }

    }

    return;
}


// Print the winner of the election
void print_winner(void)
{
    //feedback from discord:
    //i'd give the description of the source a re-read or the reason why charlie wins and not alice in the example given also think carefully about your loop conditions there, why pair_count + 1?
    // TODO
    int highestscore = 0;
    int winner[MAX] = {}; //array to store winning candidates

    //loop through the locked 2D array, to tally up candidates with "true"
    for (int i = 0; i < pair_count + 1; i++)
    {
        int keepscore = 0;
        for (int j = 0; j < pair_count + 1; j++)
        {
            if (locked[i][j] == true)
            {
                //candidates with the most "true" values win
                keepscore++;
                winner[i] = keepscore;

                //if the current score of the candidate is greater than the highest recorded score, highestscore updates with the new score.
                if (keepscore > highestscore)
                {
                    highestscore = keepscore;
                }

            }
        }

    }

    //print out all candidates with the same highestscores, including candidates that tie.
    for (int k = 0; k < pair_count + 1; k++)
    {
        if (winner[k] == highestscore)
        {
            printf("%s\n", candidates[k]);
        }
    }

    return;
}