#include "helpers.h"
#include <math.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg_color;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avg_color = round((float)(image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed) / 3);
            image[i][j].rgbtBlue = avg_color;
            image[i][j].rgbtGreen = avg_color;
            image[i][j].rgbtRed = avg_color;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = round(.393 * (float)image[i][j].rgbtRed + .769 * (float)image[i][j].rgbtGreen + .189 * (float)image[i][j].rgbtBlue);
            sepiaGreen = round(.349 * (float)image[i][j].rgbtRed + .686 * (float)image[i][j].rgbtGreen + .168 * (float)image[i][j].rgbtBlue);
            sepiaBlue = round(.272 * (float)image[i][j].rgbtRed + .534 * (float)image[i][j].rgbtGreen + .131 * (float)image[i][j].rgbtBlue);

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
    int tmp_b, tmp_g, tmp_r;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, n = width / 2; j < n; j++)
        {
            tmp_b = image[i][j].rgbtBlue;
            tmp_g = image[i][j].rgbtGreen;
            tmp_r = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][j + (width - 1 - (2 * j))].rgbtBlue;
            image[i][j].rgbtGreen = image[i][j + (width - 1 - (2 * j))].rgbtGreen;
            image[i][j].rgbtRed = image[i][j + (width - 1 - (2 * j))].rgbtRed;

            image[i][j + (width - 1 - (2 * j))].rgbtBlue = tmp_b;
            image[i][j + (width - 1 - (2 * j))].rgbtGreen = tmp_g;
            image[i][j + (width - 1 - (2 * j))].rgbtRed = tmp_r;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //create a temporary image to be blurred
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    // Update the temporary image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_b, sum_g, sum_r;
            float count;
            sum_b = sum_g = sum_r = count = 0;

            //iterate through the column, from -1 to +1
            for (int h = -1; h < 2; h++)
            {
                //iterate similarly through rows
                for (int w = -1; w < 2; w++)
                {
                    //if pixel is outside the image (column)
                    if (i + h < 0 || i + h > (height - 1))
                    {
                        continue; //skip
                    }
                    //if pixel is outside the image (row)
                    if (j + w  < 0 || j + w > (width - 1))
                    {
                        continue; //skip
                    }
                    //sum up the values of all the pixels
                    sum_r += tmp[i + h][j + w].rgbtRed;
                    sum_g += tmp[i + h][j + w].rgbtGreen;
                    sum_b += tmp[i + h][j + w].rgbtBlue;
                    count++;
                }
            }
            //find average colour value
            image[i][j].rgbtRed = round(sum_r / count);
            image[i][j].rgbtGreen = round(sum_g / count);
            image[i][j].rgbtBlue = round(sum_b / count);
        }
    }
    return;
}