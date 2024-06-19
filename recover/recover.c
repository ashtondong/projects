#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // if argument count is not 1, return error
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }
    // open file in read mode
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("File could not be opened.\n");
        return 1;
    }
    // declare constant for jpeg block size
    const int JPG_BLOCK = 512;
    // declare file buffer array to read the file into
    uint8_t file_buffer[JPG_BLOCK];

    // declare constant jpeg title size
    const int JPG_TITLE = 9;
    // declare title buffer array to hold the string names printed into memory using sprintf()
    char title_output[JPG_TITLE];
    // print a string onto the memory into the buffer array that can hold the string on the memory

    FILE *jpg; // declare this global FILE* variable. that way it will hold the updated pointers from the while loop below and you'll be able to use it globally.
    int i = 0;
    bool found_first = NULL;


    while (fread(file_buffer, 1, JPG_BLOCK, input) == JPG_BLOCK)
    {

        if (file_buffer[0] == 0xff && file_buffer[1] == 0xd8 && file_buffer[2] == 0xff && (file_buffer[3] & 0xf0) == 0xe0)
        {
            if (i == 0) // for the first jpg
            {
                sprintf(title_output, "%03i.jpg", i);
                jpg = fopen(title_output, "w");
                fwrite(file_buffer, 1, JPG_BLOCK, jpg); //title_output should be holding "000.JPEG"
                found_first = true;
                i++;

            }

            else // for subsequent jpgs
            {
                fclose(jpg);
                sprintf(title_output, "%03i.jpg", i);
                jpg = fopen(title_output, "w");
                fwrite(file_buffer, 1, JPG_BLOCK, jpg);
                i++;
            }



        }

        else if (found_first == true)
        {

            fwrite(file_buffer, 1, JPG_BLOCK, jpg); // keep writing to current jpeg file if header not found for new file.
        }

    }




    fclose(jpg);
    fclose(input);

}