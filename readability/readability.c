#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{

    string text = get_string("Text: \n");
    float l = count_letters(text);
    float w = count_words(text);
    float s = count_sentences(text);
    //make sure we're storing the letter, word, and string values as floats so we can access float values in later formula.

    float L = (l / w * 100);
    float S = (s / w * 100);
    //must be float to get an accurate calculation

    // creating the Coleman-Liau index to calculate grade level
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    //rounding the result to get the next highest integer. this produces a float.
    //storing the rounded float as an integer so it doesn't produce a 0.0000 value.
    //we want to truncate after rounding so it doesn't look weird to the user. 


    if (index > 16)
    {
        printf("Grade 16+\n");
    }

    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }



}

//creating funciton to count letters
int count_letters(string text)
{
    int count = 0;
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        if ((65 > text[i] || text[i] > 90) && (97 > text[i] || text[i] > 122))
        {
            count = count + 0;

        }
        else
        {
            count++;
        }

    }
    return count;


}

//creating functions to count words
int count_words(string text)
{
    int count = 0;
    int len = strlen(text);
    for (int i = 0; i <= len; i++)
    {

        if (text[i] == 32 || text[i] == '\0')
        {
            count++;

        }
        else
        {
            count = count + 0;
        }


    }
    return count;
}

//creating functions to count sentences
int count_sentences(string text)

{
    int count = 0;
    int len = strlen(text);
    for (int i = 0; i <= len; i++)
    {

        if (text[i] == 46 || text[i] == 33 || text[i] == 63)
        {
            count++;

        }
        else
        {
            count = count + 0;
        }


    }
    return count;




}






