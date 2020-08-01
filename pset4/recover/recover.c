#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (file == NULL) {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    unsigned char block[512];
    int counter = 0;

    FILE *img = NULL;

    while (fread(block, 512, 1, file)){
        char filename[7];

        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && (block[3] & 0xf0) == 0xe0) {
            if (counter > 0) fclose(img);

            sprintf(filename, "%03i.jpg", counter);
            img = fopen(filename, "w");
            counter++;
            fwrite(block, 512, 1, img);
        } else if (counter > 0) {
            fwrite(block, 512, 1, img);
        }
    }

    fclose(img);

    return 0;
}
