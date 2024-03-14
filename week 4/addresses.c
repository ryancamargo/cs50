#include <stdio.h>

int main(void)
{
    int n = 50;
    int *p = &n;
    printf("%p\n", p);

    char *s = "HI!";  // CS50 library ----- typedef char *string;
    printf("%s\n", s);
    printf("%p\n", &s[0]);
    printf("%p\n", &s[1]);
    printf("%p\n", &s[2]);
    printf("%p\n", &s[3]);

    int m = 20;
    int *q = &m;
    printf("%i\n", *q);

    printf("%c\n", *s);
    printf("%c\n", *(s+1));
    printf("%c\n", *(s+2));
    //printf("%c\n", *(s+500000)); // Segmentation fault (core dumped)

    printf("%s\n", s);
    printf("%s\n", s+1);
    printf("%s\n", s+2);

}