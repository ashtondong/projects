#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <cs50.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // for each pixel in the image, we want to update that pixel to the average RGB number.
    int avg;

    for (int i = 0; i <= (height - 1); i++) //height
    {
        for (int j = 0; j <= (width - 1); j++) //width
        {

            avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;

        }
    }

    return;
}

float min(float a, float b)
{
    return (a > b) ? b : a;

}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i <= (height - 1); i++)
    {
        for (int j = 0; j <= (width - 1); j++)
        {
            int sepiaRed = round(min(255.0, (.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue)));
            int sepiaGreen = round(min(255.0, (.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue)));
            int sepiaBlue = round(min(255.0, (.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue)));

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;

        }
    }



    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int j = 0;
    while (j < height)
    {
        for (int i = 0; i < (width / 2); i++)
        {
            //starting at first pixel
            RGBTRIPLE swapvar = image[j][i];
            //left pixel
            image[j][i] = image[j][(width - 1) - i];
            //right pixel
            image[j][(width - 1) - i] = swapvar;

        }

        j++;

    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
