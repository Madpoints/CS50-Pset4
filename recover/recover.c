#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover memory_card\n");
        return 1;
    }

    // open memory card file
    FILE* memCard = fopen(argv[1], "r");
    if (memCard == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    // counter for JPEG files
    int counter = 0;

    // buffer for memory block (512 bytes)
    unsigned char buffer[512];

    // string to store file names
    char name[10];

    // file pointer for JPEGs
    FILE* jpeg = NULL;

    // while not at the end of the memory card file
    while(!feof(memCard))
    {
        // if not at the last block of memory
        // store block of memory in buffer
        if (fread(buffer, 1, sizeof(buffer), memCard) != 0)
        {
            // if the first four bytes correspond to a JPEG header
            if (buffer[0] == 0xff &&
                buffer[1] == 0xd8 &&
                buffer[2] == 0xff &&
                (buffer[3] & 0xf0) == 0xe0)
            {
                // if the file pointer is not NULL close it
                // it is the start of a new jpeg
                if (jpeg != NULL)
                {
                    fclose(jpeg);
                }

                // create a new file name using the counter
                sprintf(name, "%03i.jpg", counter);

                // open the new file
                jpeg = fopen(name, "w");

                // write to the new file from the buffer
                fwrite(buffer, 1, sizeof(buffer), jpeg);

                // count the number of JPEGS in memory card file
                // printf("%d JPEG\n", counter);

                // update counter for next file name
                counter++;
            }
            // else if it is still a JPEG
            else if (counter > 0)
            {
                // write to the new file from the buffer
                fwrite(buffer, 1, sizeof(buffer), jpeg);
            }
        }
    }

    // cloes memory card file process complete
    fclose(memCard);

    return 0;
}