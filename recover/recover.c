#include <stdio.h>
#include <stdlib.h>

typedef unsigned char BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover infile\n");
        return 1;
    }

    // open input file
    FILE* memCard = fopen(argv[1], "r");
    if (memCard == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    int counter = 1;

    while(!feof(memCard))
    {

        BYTE buffer[512];
        fread(&buffer, 1, 512, memCard);

        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            printf("%d JPEG\n", counter);
            counter++;
        }

    }

    return 0;
}