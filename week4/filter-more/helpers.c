#include "helpers.h"
#include <math.h>

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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, n = width / 2; j < n; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - (j + 1)];
            image[i][width - (j + 1)] = tmp;
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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

    // Gx & Gy
    int Gx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};
    double R, G, B;
    R = G = B = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double Gx_sum_r, Gx_sum_g, Gx_sum_b, Gy_sum_r, Gy_sum_g, Gy_sum_b;
            Gx_sum_r = Gx_sum_g = Gx_sum_b = Gy_sum_r = Gy_sum_g = Gy_sum_b = 0;
            int count = - 1;

            //iterate through the column, from -1 to +1
            for (int h = -1; h < 2; h++)
            {
                //iterate similarly through rows
                for (int w = -1; w < 2; w++)
                {
                    count++;
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
                    Gx_sum_r += (tmp[i + h][j + w].rgbtRed * Gx[count]);
                    Gx_sum_g += (tmp[i + h][j + w].rgbtGreen * Gx[count]);
                    Gx_sum_b += (tmp[i + h][j + w].rgbtBlue * Gx[count]);

                    Gy_sum_r += (tmp[i + h][j + w].rgbtRed * Gy[count]);
                    Gy_sum_g += (tmp[i + h][j + w].rgbtGreen * Gy[count]);
                    Gy_sum_b += (tmp[i + h][j + w].rgbtBlue * Gy[count]);
                }
            }
            //Gx & Gy value
            R = round(sqrt((Gx_sum_r * Gx_sum_r) + (Gy_sum_r * Gy_sum_r)));
            G = round(sqrt((Gx_sum_g * Gx_sum_g) + (Gy_sum_g * Gy_sum_g)));
            B = round(sqrt((Gx_sum_b * Gx_sum_b) + (Gy_sum_b * Gy_sum_b)));

            if (R > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = R;
            }
            if (G > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = G;
            }
            if (B > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = B;
            }
        }
    }
    return;
}