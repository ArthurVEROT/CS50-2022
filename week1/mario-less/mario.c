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
    for (int column = 0; column < height; column++)
    {
        count++;
        for (int space = 0; space < height - count; space++)
        {
            printf(" ");
        }
        for (int row = 0; row < count; row++)
        {
            printf("#");
        }
        printf("\n");
    }
}