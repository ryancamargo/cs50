// Declaring the libraries that will be used
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// Declaring the functions I created
float count_letters(string text);
float count_words(string word);
float count_sentences(string sentence);

int main(void)
{
    string text = get_string("Text: ");

    // Count number of letters - any lowercase from a to z or any uppercase character from A to Z
    float x = count_letters(text);
    //printf("%i letters\n", x);


    // Count number of words - any sequence of characters separeted by spaces should count as a word
    float y = count_words(text);
    //printf("%i words\n", y);


    // Count number of sentences - any occurence of a period (.), exclamation point (!), or question mark (?) indicates end of a sentence
    float z = count_sentences(text);
    //printf("%i sentences\n", z);


    // Print the Grade
    float L = (x * 100) / y;
    float S = (z * 100) / y;

    float grade = 0.0588 * L - 0.296 * S - 15.8;

    // If grade is less than 1, print Before Grade 1
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    // If grade is less than 16, print the grade
    else if (grade < 16)
    {
        printf("Grade %i\n", (int) round(grade));
    }
    // Else = if grade is bigger than 16, print 16+
    else
    {
        printf("Grade 16+\n");
    }
}




// Creating function to count letters
float count_letters(string text)
{
    int x = strlen(text);
    int j = 0;

    for (int i = 0; i < x; i++)
    {
        if (isupper(text[i]))
        {
            j++;
        }
        else if (islower(text[i]))
        {
            j++;
        }
    }

    return j;

}


// Creating function to count words
float count_words(string word)
{
    int x = strlen(word);
    int i = 0;
    int j = 0;

    for (j = 0, i = 0; j < x; j++)
    {
        if (word[j] == ' ')
        {
            i = i + 1;
        }
    }

    return i + 1;
}


// Creating function to count sentences
float count_sentences(string sentence)
{
    int x = strlen(sentence);
    float i = 0;
    int j = 0;

    if (count_words(sentence) == 0)
    {
        i = 0;
    }
    else
    {
        i++;
    }

    for (j = 0, i = 0; j < x; j++)
    {
        if (sentence[j] == '.')
        {
            i++;
        }
        else if (sentence[j] == '!')
        {
            i++;
        }
        else if (sentence[j] == '?')
        {
            i++;
        }
    }

    return i;

}