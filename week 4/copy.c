#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    char *s = get_string("s: ");
    if (s == NULL) // get_string and malloc return NULL if something goes wrong, so we need to be prepared for that as well
    {
        return 1;
    }

    char *t = malloc(strlen(s) + 1); // memory for how many characters the human typed in AND one more byte for NULL character
    if (t == NULL)
    {
        return 1;
    }

    /*for (int i = 0; n = strlen(s) + 1; i < n ; i++)
    {
        t[i] = s[i];
    }*/

    strcpy(t, s);

    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("s: %s\n", s);
    printf("t: %s\n", t);

    free(t);

    return 0;
}