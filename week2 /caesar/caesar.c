#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string s);
char rotate(char p, int key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    bool ok = only_digits(argv[1]);
    if (ok == 1)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int key = atoi(argv[1]);

    // Get input text
    string text = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0, len = strlen(text); i < len; i++)
    {
        char ch = text[i];
        char chr = rotate(ch, key);

        printf("%c", chr);
    }
    printf("\n");
}

// Function : To check if input is all integer
bool only_digits(string s)
{
    // for loop to check every character of the string
    for (int i = 0, len = strlen(s); i < len; i++)
    {
        char ch = s[i];
        if (isdigit(ch))
        {
        }
        else
        {
            return 1; // if not digit, return FALSE
        }
    }
    return 0;
}

// Function : To translate de character into de cipher character
char rotate(char p, int key)
{
    if (isalpha(p))                              // if the character is in the alphabe
    {
        if (isupper(p))                          // if the character is a upper letter
        {
            p = ((((p - 65) + key) % 26) + 65);
            return p;
        }
        else                                     // if the character is a lower letter
        {
            p = ((((p - 97) + key) % 26) + 97);
            return p;
        }
    }
    else
    {
        return p;
    }
}