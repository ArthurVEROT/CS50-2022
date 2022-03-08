#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool only_alpha(string s);
bool duplicate(string argv);
void substitution(string plaintext, string argv);
char all_lower(char ch);
char all_upper(char ch);


int main(int argc, string argv[])
{
    // handles lack of key
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // handles invalid key length
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // handles invalid characters in key
    if (only_alpha(argv[1]) == 0)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // handles duplicate or multiple duplicate characters in key
    if (duplicate(argv[1]) == 1)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // ask for the plaintext
    string plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    // print ciphertext
    substitution(plaintext, argv[1]);
}


// Check for alphanumerical characters only
bool only_alpha(string s)
{
    for (int i = 0; i < 26; i++)
    {
        char ch = s[i];
        if (isalpha(ch))
        {
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

// Check for duplicate or multiple duplicate characters
bool duplicate(string argv)
{
    for (int i = 0; i < 26; i++)
    {
        char ch = all_lower(argv[i]);
        int count = 0;
        for (int j = 0; j < 26 ; j++)
        {
            if (ch == all_lower(argv[j]))
            {
                count++;
            }
            if (count > 1)
            {
                return 1;
            }
        }
    }
    return 0;
}

// Substitute the character according to the key
void substitution(string plaintext, string argv)
{
    char ch;        // variable that will be overwritten
    char old_ch;    // varibale to remember if char was upper or lower case
    char letter;    // variable that save the cipher letter

    // first loop to initialize the character to its traditional position in the alphabet
    for (int i = 0, len_plain = strlen(plaintext); i < len_plain; i++)
    {
        ch = plaintext[i];
        old_ch = plaintext[i];
        if (isalpha(ch))
        {
            if (islower(ch))
            {
                ch = ch - 97;
            }
            else
            {
                ch = ch - 65;
            }

            // second loop to allocate the right character according to the key
            for (int j = 0; j < 26 ; j++)
            {
                if (islower(old_ch))
                {
                    letter = all_lower(argv[j]);
                }
                else
                {
                    letter = all_upper(argv[j]);
                }

                if (ch == j)
                {
                    ch = letter;
                    break;
                }
            }
        }
        printf("%c", ch);
    }
    printf("\n");
}

// Convert character to lower
char all_lower(char ch)
{
    if (isupper(ch))
    {
        ch = tolower(ch);
        return ch;
    }
    return ch;
}

// Convert character to upper
char all_upper(char ch)
{
    if (islower(ch))
    {
        ch = toupper(ch);
        return ch;
    }
    return ch;
}