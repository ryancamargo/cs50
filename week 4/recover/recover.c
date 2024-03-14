#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    else
    {
        // Open the card.raw file (memory card)
        char *input_file_name = argv[1];
        FILE *input_pointer = fopen(input_file_name, "r");

        if (input_pointer == NULL)
        {
            printf("Error: cannot open %s\n", input_file_name);
            return 1;
        }

        // Create variables
        BYTE buffer[512];
        int count = 0;
        FILE *image_pointer = NULL;
        char filename[8];

        // Repeat til the end of the memory card
        while (fread(&buffer, 512, 1, input_pointer) == 1)
        {

            // Check start of a new JPEG == 0xff 0xd8 0xff 0xe*
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                // Closes previous file if not a JPEG
                if (!(count == 0))
                {
                    fclose(image_pointer);
                }

                // Parse file
                sprintf(filename, "%03i.jpg", count);
                image_pointer = fopen(filename, "w");
                count++;
            }

            // Write to file if its JPEG
            if (!(count == 0))
            {
                fwrite(&buffer, 512, 1, image_pointer);
            }
        }
        fclose(input_pointer);
        fclose(image_pointer);
        return 0;
    }
}
