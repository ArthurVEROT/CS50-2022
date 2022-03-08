#include <math.h>
#include "helpers.h"
#include <stdio.h>


int main(void)
{
    int height = 3;
    int width = 3;
    RGBTRIPLE image[height][width];

    image[0][0].rgbtRed = 25;
    image[0][0].rgbtGreen = 10;
    image[0][0].rgbtBlue = 0;

    image[0][1].rgbtRed = 30;
    image[0][1].rgbtGreen = 10;
    image[0][1].rgbtBlue = 0;

    image[0][2].rgbtRed = 80;
    image[0][2].rgbtGreen = 60;
    image[0][2].rgbtBlue = 40;

    image[1][0].rgbtRed = 90;
    image[1][0].rgbtGreen = 30;
    image[1][0].rgbtBlue = 20;

    image[1][1].rgbtRed = 100;
    image[1][1].rgbtGreen = 40;
    image[1][1].rgbtBlue = 30;

    image[1][2].rgbtRed = 90;
    image[1][2].rgbtGreen = 70;
    image[1][2].rgbtBlue = 80;

    image[2][0].rgbtRed = 40;
    image[2][0].rgbtGreen = 20;
    image[2][0].rgbtBlue = 20;

    image[2][1].rgbtRed = 30;
    image[2][1].rgbtGreen = 10;
    image[2][1].rgbtBlue = 30;

    image[2][2].rgbtRed = 10;
    image[2][2].rgbtGreen = 40;
    image[2][2].rgbtBlue = 50;

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
            printf("%i %i %i\n", image[i][j].rgbtBlue, image[i][j].rgbtGreen, image[i][j].rgbtRed);
        }
    }

}