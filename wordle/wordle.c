#include <cs50.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

// each of our text files contains 1000 words
#define LISTSIZE 1000

// values for colors and score (EXACT == right letter, right place; CLOSE == right letter, wrong place; WRONG == wrong letter)
#define EXACT 2
#define CLOSE 1
#define WRONG 0

// ANSI color codes for boxed in letters
#define GREEN   "\e[38;2;255;255;255;1m\e[48;2;106;170;100;1m"
#define YELLOW  "\e[38;2;255;255;255;1m\e[48;2;201;180;88;1m"
#define RED     "\e[38;2;255;255;255;1m\e[48;2;220;20;60;1m"
#define RESET   "\e[0;39m"

// user-defined function prototypes
string get_guess(int wordsize);
int check_word(string guess, int wordsize, int status[], string choice);
void print_word(string guess, int wordsize, int status[]);

int main(int argc, string argv[])
{
    // ensure proper usage
    // TODO #1
    if (argc != 2)
    {
        printf("Usage: ./wordle wordsize\n");
        return 1;

    }

    // ensure argv[1] is either 5, 6, 7, or 8 and store that value in wordsize instead
    // TODO #2

    int wordsize = atoi(argv[1]);

    if (wordsize > 8 || wordsize < 5)
    {
        printf("Error: wordsize must be either 5, 6, 7, or 8\n");
        return 1;

    }



    if (9 > wordsize && wordsize > 4)
    {

        // open correct file, each file has exactly LISTSIZE words
        char wl_filename[6];
        sprintf(wl_filename, "%i.txt", wordsize);
        FILE *wordlist = fopen(wl_filename, "r");
        if (wordlist == NULL)
        {
            printf("Error opening file %s.\n", wl_filename);
            return 1;
        }

        // load word file into an array of size LISTSIZE
        char options[LISTSIZE][wordsize + 1];

        for (int i = 0; i < LISTSIZE; i++)
        {
            fscanf(wordlist, "%s", options[i]);
        }

        // pseudorandomly select a word for this game
        srand(time(NULL));
        string choice = options[rand() % LISTSIZE];

        // allow one more guess than the length of the word
        int guesses = wordsize + 1;
        bool won = false;

        // print greeting, using ANSI color codes to demonstrate

        printf(GREEN"This is WORDLE50"RESET"\n");
        printf("You have %i tries to guess the %i-letter word I'm thinking of\n", guesses, wordsize);


        // main game loop, one iteration for each guess
        for (int i = 0; i < guesses; i++)
        {
            // obtain user's guess
            string guess = get_guess(wordsize);

            // array to hold guess status, initially set to zero
            int status[wordsize];

            // set all elements of status array initially to 0, aka WRONG
            // TODO #4

            for (int s = 0; s < wordsize; s++)
            {
                status[s] = 0; //append all elements in array to 0
                //we cannot assign 0s to an array if the size of the array is variable i.e. status[wordsize]=0 does not work.
            }



            // Calculate score for the guess
            int score = check_word(guess, wordsize, status, choice);

            printf("Guess %i: ", i + 1);

            // Print the guess
            print_word(guess, wordsize, status);

            // if they guessed it exactly right, set terminate loop
            if (score == EXACT * wordsize)
            {
                won = true;
                break;
            }
        }

        // Print the game's result
        // TODO #7

        if (won)
        {
            printf("You won!\n");

        }
        else
        {
            printf("The word is %s\n", choice);

        }


        // that's all folks!
        return 0;
    }



}


string get_guess(int wordsize)
{
    // TODO #3
    //use strlen to get the length of the word and compare to the wordsize.
    string guess;
    do
    {
        guess = get_string("Input a %i-letter word:  ", wordsize);
    }
    while (strlen(guess) != wordsize);




    // ensure users actually provide a guess that is the correct length

    return guess;
}

int check_word(string guess, int wordsize, int status[], string choice)
{
    int score = 0;
    int points;

    // compare guess to choice and score points as appropriate, storing points in status
    // TODO #5




    for (int l = 0; l < wordsize; l++) //iterate over each letter of guess
    {
        int j = 0;

        while (j < wordsize) //this will iterate over the length of choice and through the array
        {
            if (guess[l] == choice [j])
            {
                if (l == j) //if guess index is at the same place as choice index
                {
                    points = 2;
                    status[l] = points;
                    score = score + points; //append to status array ** need to revisit as going through for loop again will erase everything in array.
                    break;
                    //if the letter from guess matches the letter from choice at the same position, assign value of 2


                }
                else
                {
                    points = 1;
                    status[l] = points;
                    // if the letter from guess matches the letter from choice at a position not the same, assign value of 1

                }

            }
            j++;


        }

    }



    return score;

}

void print_word(string guess, int wordsize, int status[])
{
    // print word character-for-character with correct color coding, then reset terminal font to normal
    // TODO #6
    for (int k = 0; k < wordsize; k++)
    {
        if (status[k] == 1)
        {
            printf(YELLOW"%c"RESET, guess[k]);


        }
        if (status[k] == 2)
        {
            printf(GREEN"%c"RESET, guess[k]);


        }
        if ((status[k] != 1) && (status[k] != 2))
        {
            printf(RED"%c"RESET, guess[k]);

        }



    }


    printf("\n");
    return;
}
