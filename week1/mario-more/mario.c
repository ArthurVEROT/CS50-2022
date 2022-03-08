#include <cs50.h>
#include <stdio.h>

int main(void)
{

    // Get the wanted height
    int height;

    // do-while loop to get a number between 1 & 8
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height >= 9);

    // for loop to get the pyramid
    int count = 0;
    // first for loop to get the column
    for (int column = 0; column < height; column++)
    {
        count++;
        // second for loop to get the space before the bricks
        for (int space1 = 0; space1 < height - count; space1++)
        {
            printf(" ");
        }
        // third for loop to get the bricks of the first pyramid
        for (int row = 0; row < count; row++)
        {
            printf("#");
        }
        // spaces between the 2 pyramids
        printf("  ");

        // fourth for loop to get the bricks of the second pyramid
        for (int row2 = 0; row2 < count; row2++)
        {
            printf("#");
        }
        printf("\n");
    }
}
