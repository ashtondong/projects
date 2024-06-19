// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // first create an array the size of the header and the data type will be uint8_t, this will be used to store the header.
    uint8_t header_buffer[HEADER_SIZE];
    // fread finds the starting location on memory of the first point in header and reading by 1 for the entire header size from the input file.
    fread(header_buffer, HEADER_SIZE, 1, input);
    // we need to write it onto the output file
    fwrite(header_buffer, HEADER_SIZE, 1, output);

    // TODO: Read samples from input file and write updated data to output file
    //we need to create a buffer to temporarily store the data before putting it onto the output file
    //two bytes each using the int16_t data type
    int16_t sample_buffer;

    while (fread(&sample_buffer, sizeof(int16_t), 1, input))
    {
        sample_buffer = sample_buffer * factor;
        fwrite(&sample_buffer, sizeof(int16_t), 1, output);
    }



    // Close files
    fclose(input);
    fclose(output);
}
