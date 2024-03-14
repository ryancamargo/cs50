#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int a;
    do
    {
        // Asking the user for the pyramid height 'a'
        a = get_long("Height: ");

        // Number of brics between 1 - 8
        if (a > 0 && a <= 8)
        {
            // Print the bric #
            switch (a)
            {
                case 8:
                    printf("       #  #\n");

                    printf("      ##  ##\n");

                    printf("     ###  ###\n");

                    printf("    ####  ####\n");

                    printf("   #####  #####\n");

                    printf("  ######  ######\n");

                    printf(" #######  #######\n");

                    printf("########  ########\n");
                    break;

                case 7:
                    printf("      #  #\n");

                    printf("     ##  ##\n");

                    printf("    ###  ###\n");

                    printf("   ####  ####\n");

                    printf("  #####  #####\n");

                    printf(" ######  ######\n");

                    printf("#######  #######\n");
                    break;

                case 6:
                    printf("     #  #\n");

                    printf("    ##  ##\n");

                    printf("   ###  ###\n");

                    printf("  ####  ####\n");

                    printf(" #####  #####\n");

                    printf("######  ######\n");
                    break;

                case 5:
                    printf("    #  #\n");

                    printf("   ##  ##\n");

                    printf("  ###  ###\n");

                    printf(" ####  ####\n");

                    printf("#####  #####\n");
                    break;

                case 4:
                    printf("   #  #\n");

                    printf("  ##  ##\n");

                    printf(" ###  ###\n");

                    printf("####  ####\n");
                    break;

                case 3:
                    printf("  #  #\n");

                    printf(" ##  ##\n");

                    printf("###  ###\n");
                    break;

                case 2:
                    printf(" #  #\n");

                    printf("##  ##\n");
                    break;

                case 1:
                    printf("#  #\n");
                    break;
            }
        }
    }
    while (a > 8 || a <= 0);
}