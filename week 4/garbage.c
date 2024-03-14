#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int score[1024];
    for (int i = 0; i < 1024; i++)
    {
        printf("%i\n", score[i]);    // garbage values - random values of variables that were not initialized
    }
}