#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int Coleman_Liau_index(int l, int w, int s);

int main(void)
{
    // Get input text
    string text = get_string("Your text: ");

    // Count letters
    int l = count_letters(text);

    // Count words
    int w = count_words(text);

    // Count sentences
    int s = count_sentences(text);

    //Grade level of the text
    int grade = Coleman_Liau_index(l, w, s);

    // Display the grade level of the text
    if (grade >= 1 && grade < 16)
    {
        printf("Grade %i\n", grade);
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade 16+\n");
    }
}

// Function to count the letters
int count_letters(string text)
{
    int count = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        char ch = text[i];
        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        {
            count++;
        }
    }
    return count;
}

// Function to count the words
int count_words(string text)
{
    int count = 0;
    int len = strlen(text);
    for (int i = 0; i < len; i++)
    {
        char ch = text[i];
        if (ch == ' ')
        {
            count++;
        }
    }
    return count + 1;
}

// Function to count the sentences
int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, len = strlen(text); i < len; i++)
    {
        char ch = text[i];
        if (ch == '.' || ch == '?' || ch == '!')
        {
            count++;
        }
    }
    return count;
}

// Function to calculate the Coleman Liau Index
int Coleman_Liau_index(int l, int w, int s)
{
    float L = ((float)l / (float)w) * 100;
    float S = ((float)s / (float)w) * 100;
    float index = (0.0588 * L) - (0.296 * S) - 15.8;
    int index_round = roundf(index);

    return index_round;
}