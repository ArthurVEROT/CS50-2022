#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // If more than 1 argument, print this message
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 2;
    }

    typedef uint8_t BYTE;
    BYTE buffer[512];
    int count;
    char *filename = malloc(8);
    FILE *img = NULL;

    // Repeat until the end of card
    while (fread(buffer, 1, 512, card) == 512)
    {
        // If first four bytes are equal to a .jpg header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If it is the first .jpg of the memory card
            if (img == NULL) // first jpeg
            {
                count = 0;
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
                count++;

            }
            // If not first .jpg, close previous .jpg and write a new one
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", count);
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
                count ++;
            }
        }
        // If no header, continue writing
        else if (img != NULL)
        {
            fwrite(buffer, 1, 512, img);
        }
    }
    free(filename);
    // Close files
    fclose(img);
    fclose(card);
}