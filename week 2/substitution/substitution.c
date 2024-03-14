#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void assign_elements();
void adjust_letters(char position, string key);

int main(int argc, string argv[])
{
    // Check if key contain one command-line argument
    if (argc == 2)
    {
        // Define length as the int variable of strlen(argv[1])
        int length = strlen(argv[1]);

        // Check if key has 26-digit characters
        if (length == 26)
        {
            // Loop to check each element of the array
            for (int j = 0; j < length; j++)
            {
                // If key is non-alphabetical, it will be discovered here
                if (! isalpha(argv[1][j]))
                {
                    printf("Key must only contain alphabetic characters.\n");
                    return 1;
                }
                // Check for repeated characters
                for (int k = j + 1; k < length; k++)
                {
                    if (toupper(argv[1][k]) == toupper(argv[1][j]))
                    {
                        printf("Key must not contain repeated characters.\n");
                        return 1;
                    }
                }
            }
            // Assign elements from key to plaintext
            assign_elements(argv[1]);

        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }

    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    return 0;
}

// Function to combine key and plaintext
void assign_elements(string element)
{
    string p = get_string("plaintext: ");

    printf("ciphertext: ");

    for (int i = 0; i < strlen(p); i++)
    {
        // Check if plaintext if only alphabetical characters
        if (isalpha(p[i]))
        {
            char a = p[i];
            if (islower(p[i]))
            {
                // If plaintext element is lowercase -> adjust the output element to lower
                adjust_letters(tolower(a), element);
            }
            else
            {
                // If plaintext elemnt is uppercase -> adjust the output element to upper
                adjust_letters(toupper(a), element);
            }
        }
        // If plaintext non-alphabetical -> print exaclty as it is
        else
        {
            printf("%c", p[i]);
        }

    }
    // Line-space after for loop
    printf("\n");
}


// Function to adjust alphabet letters to key characters
void adjust_letters(char position, string key)
{
    // Alphabet array of characters
    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < strlen(letters); i++)
    {
        // Check if plaintext 'i' element is lowercase
        if (islower(position))
        {
            // If true -> convert the ciphertext to lowercase
            if (position == tolower(letters[i]))
            {
                // Print the 'i' element of key to lowercase
                printf("%c", tolower(key[i]));
            }
        }
        // If UPPERCASE
        else
        {
            if (position == toupper(letters[i]))
            {
                // Print the 'i' element of key to UPPERCASE
                printf("%c", toupper(key[i]));
            }
        }
    }
}