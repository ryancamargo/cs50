#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // create float variable that stores the average value of red green and blue
    float average;

    // check each column
    for (int i = 0; i < width; i++)
    {
        // check each row
        for (int j = 0; j < height; j++)
        {
            average = (image[j][i].rgbtRed + image[j][i].rgbtGreen + image[j][i].rgbtBlue)/(3.00);

            average = round(average);

            image[j][i].rgbtRed = average;
            image[j][i].rgbtGreen = average;
            image[j][i].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // create float variables to store sepia value for red green and blue
    float sepiaRed, sepiaGreen, sepiaBlue;

    // iterate for each row
    for (int i = 0; i < height; i++)
    {
        // iterate for each column
        for (int j = 0; j < width; j++)
        {
            // get the sepia values for each part of RGB (red, gree, blue)
            sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            // round the sepia float value to the nearest integer
            sepiaRed = round(sepiaRed);
            sepiaGreen = round(sepiaGreen);
            sepiaBlue = round(sepiaBlue);

            // if > 255, it should be 255 so that we stay in 24-bit color map only
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // give the sepia values to the specific equivalent
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;

        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate for rows
    for (int i = 0; i < height; i++)
    {
        // create temp variable to store values that are being swapped
        RGBTRIPLE tmp[1][1];
        int k = width;

        // iterate for left-to-right and right-to-left
        for (int j = 0; j < (width / 2); j++)
        {
            // swap values of red, green and blue
            tmp[0][0] = image[i][j];
            image[i][j] = image[i][k - 1];
            image[i][k - 1] = tmp[0][0];

            k--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create RGBTRIPLE array to copy pixel by pixel of the original image
    RGBTRIPLE copy[height][width];

    // Iterate to copy each pixel from original array to the copy one
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            copy[row][column] = image[row][column];
        }
    }

    // iterate for rows
    for (int i = 0; i < height; i++)
    {
        // iterate for columns
        for (int j = 0; j < width; j++)
        {
            // create float variable to calculate average
            float avrgRed, avrgGreen, avrgBlue;
            avrgRed = 0;
            avrgGreen = 0;
            avrgBlue = 0;

            // divide into sets to simplify
            if ((i == 0 && j == 0) || (i == 0 && (j == width - 1)) || ((i == height - 1) && (j == 0)) || ((i == height - 1) && (j == width - 1)))
            {
                // Calculate 2x2
                // 1st square
                if ((i == height - 1) && (j == 0))
                {
                    avrgRed = (copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed)/4.00;
                    avrgGreen = (copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen)/4.00;
                    avrgBlue = (copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue)/4.00;

                    avrgRed = round(avrgRed);
                    avrgGreen = round(avrgGreen);
                    avrgBlue = round(avrgBlue);

                    image[i][j].rgbtRed = avrgRed;
                    image[i][j].rgbtGreen = avrgGreen;
                    image[i][j].rgbtBlue = avrgBlue;

                    avrgRed = 0;
                    avrgGreen = 0;
                    avrgBlue = 0;
                }

                // 2nd square
                if ((i == height - 1) && (j == width - 1))
                {
                    avrgRed = (copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed)/4.00;
                    avrgGreen = (copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen)/4.00;
                    avrgBlue = (copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue)/4.00;

                    avrgRed = round(avrgRed);
                    avrgGreen = round(avrgGreen);
                    avrgBlue = round(avrgBlue);

                    image[i][j].rgbtRed = avrgRed;
                    image[i][j].rgbtGreen = avrgGreen;
                    image[i][j].rgbtBlue = avrgBlue;

                    avrgRed = 0;
                    avrgGreen = 0;
                    avrgBlue = 0;
                }

                // 3rd square
                if ((i == 0) && (j == 0))
                {
                    avrgRed = (copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed)/4.00;
                    avrgGreen = (copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen)/4.00;
                    avrgBlue = (copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue)/4.00;

                    avrgRed = round(avrgRed);
                    avrgGreen = round(avrgGreen);
                    avrgBlue = round(avrgBlue);

                    image[i][j].rgbtRed = avrgRed;
                    image[i][j].rgbtGreen = avrgGreen;
                    image[i][j].rgbtBlue = avrgBlue;

                    avrgRed = 0;
                    avrgGreen = 0;
                    avrgBlue = 0;
                }

                // 4th square
                if ((i == 0) && (j == width - 1))
                {
                    avrgRed = (copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed)/4.00;
                    avrgGreen = (copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen)/4.00;
                    avrgBlue = (copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue)/4.00;

                    avrgRed = round(avrgRed);
                    avrgGreen = round(avrgGreen);
                    avrgBlue = round(avrgBlue);

                    image[i][j].rgbtRed = avrgRed;
                    image[i][j].rgbtGreen = avrgGreen;
                    image[i][j].rgbtBlue = avrgBlue;

                    avrgRed = 0;
                    avrgGreen = 0;
                    avrgBlue = 0;
                }
            }
            else if ((i == 0) || (j == 0) || (i == height - 1) || (j == width - 1))
            {
                // Calculate rectangle 2x3
                // Divide into four categories: horizontal top rectangles, horizontal bottom rectangles, vertical left rectangles, vertical right rectangles
                // Horizontal Top
                if (i == height - 1)
                {
                    avrgRed = (copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i - 1][j + 1].rgbtRed)/6.00;
                    avrgGreen = (copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j + 1].rgbtGreen)/6.00;
                    avrgBlue = (copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j + 1].rgbtBlue)/6.00;

                    // Round to the nearest integer
                    avrgRed = round(avrgRed);
                    avrgGreen = round(avrgGreen);
                    avrgBlue = round(avrgBlue);

                    // Blur the pixel
                    image[i][j].rgbtRed = avrgRed;
                    image[i][j].rgbtGreen = avrgGreen;
                    image[i][j].rgbtBlue = avrgBlue;

                    avrgRed = 0;
                    avrgGreen = 0;
                    avrgBlue = 0;
                }

                // Horizontal Bottom
                if (i == 0)
                {
                    avrgRed = (copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j + 1].rgbtRed)/6.00;
                    avrgGreen = (copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j + 1].rgbtGreen)/6.00;
                    avrgBlue = (copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j + 1].rgbtBlue)/6.00;

                    // Round to the nearest integer
                    avrgRed = round(avrgRed);
                    avrgGreen = round(avrgGreen);
                    avrgBlue = round(avrgBlue);

                    // Blur the pixel
                    image[i][j].rgbtRed = avrgRed;
                    image[i][j].rgbtGreen = avrgGreen;
                    image[i][j].rgbtBlue = avrgBlue;

                    avrgRed = 0;
                    avrgGreen = 0;
                    avrgBlue = 0;
                }

                // Vertical Left
                if (j == 0)
                {
                    avrgRed = (copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed)/6.00;
                    avrgGreen = (copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen)/6.00;
                    avrgBlue = (copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue)/6.00;

                    // Round to the nearest integer
                    avrgRed = round(avrgRed);
                    avrgGreen = round(avrgGreen);
                    avrgBlue = round(avrgBlue);

                    // Blur the pixel
                    image[i][j].rgbtRed = avrgRed;
                    image[i][j].rgbtGreen = avrgGreen;
                    image[i][j].rgbtBlue = avrgBlue;

                    avrgRed = 0;
                    avrgGreen = 0;
                    avrgBlue = 0;
                }

                // Vertical Right
                if (j == width - 1)
                {
                    avrgRed = (copy[i][j].rgbtRed + copy[i][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed)/6.00;
                    avrgGreen = (copy[i][j].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen)/6.00;
                    avrgBlue = (copy[i][j].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue)/6.00;

                    // Round to the nearest integer
                    avrgRed = round(avrgRed);
                    avrgGreen = round(avrgGreen);
                    avrgBlue = round(avrgBlue);

                    // Blur the pixel
                    image[i][j].rgbtRed = avrgRed;
                    image[i][j].rgbtGreen = avrgGreen;
                    image[i][j].rgbtBlue = avrgBlue;

                    avrgRed = 0;
                    avrgGreen = 0;
                    avrgBlue = 0;
                }
            }
            else
            {
                // Calculate 3x3
                // Calculate the average of Red, Green and Blue
                avrgRed = (copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed)/9.00;
                avrgGreen = (copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen)/9.00;
                avrgBlue = (copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue)/9.00;

                // Round to the nearest integer
                avrgRed = round(avrgRed);
                avrgGreen = round(avrgGreen);
                avrgBlue = round(avrgBlue);

                // Blur the pixel
                image[i][j].rgbtRed = avrgRed;
                image[i][j].rgbtGreen = avrgGreen;
                image[i][j].rgbtBlue = avrgBlue;

                avrgRed = 0;
                avrgGreen = 0;
                avrgBlue = 0;
            }
        }
    }
    return;
}

