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

    // while not at the end of the file
    while(!feof(memCard))
    {
        // buffer for 512 bytes
        unsigned char buffer[512];

        // read file 1 byte at a time, 512 times
        fread(&buffer, 1, 512, memCard);

        // if the bytes correspond to a JPEG header
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            printf("%d JPEG\n", counter);
            counter++;
        }

    }

    fclose(memCard);

    return 0;
}