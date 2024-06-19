#include <cs50.h>
#include <stdio.h>
#include <stdint.h>

int main(int argc, string argv[])
{
    if (argc !=2)
    {
        printf("improper usage");
        return 1;
    }

    //open file
    string filename = argv[1];
    FILE *file= fopen(filename, "r");

    if (file == NULL)
    {
        printf("No such file found.\n");
        return 1;
    }


    //unsigned integer 8 bits _ it's own type
    uint8_t buffer[4];
    uint8_t signature[] = {37, 80, 68, 70}; //starting numbers in PDF file types

    fread(buffer, 1, 4, file);

    //checking if the buffer signature match PDF's
    for (int i = 0; i < 4; i++)
    {
        //if any number doesn't match, it's probably not a pdf.
        if (buffer[i] != signature[i])
        {
            printf("likely not a pdf.");
            return 0; //terminates the program
        }
    }
    //if it makes it through the above loop, then it's likely a pdf.
    printf("Likely a pdf.\n");
    return 0;

}