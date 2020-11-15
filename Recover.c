#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //If there are not exactly two command line arguments - print error to stderr
    if(argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    //Open new file and check if file is not null
    FILE *file = fopen(argv[1], "r"); //File is first command line argument - for reading
    if(file == NULL)
    {
        fprintf(stderr, "Could not open file %s.\n", argv[1]); //If null then print out error
        return 1;
    }

    FILE *img; //Open img file to write the contents of the jpeg
    char filename[7]; //buffer for sprintf
    unsigned char *bf = malloc(512); //allocate one "Block" of memory
    int counter = 0;

    while (fread(bf, 512, 1, file))
    {
        // checks jpeg file format
        if (bf[0] == 0xff && bf[1] == 0xd8 && bf[2] == 0xff && (bf[3] & 0xf0) == 0xe0)
        {
            // close previous jpg file if it exists
            if (counter > 0)
            {
                fclose(img);
            }

            // create filename
            sprintf(filename, "%03d.jpg", counter);
            // open new image file
            img = fopen(filename, "w");

            // check if jpg file is successfully created
            if (img == NULL)
            {
                fclose(file);
                free(bf);
                fprintf(stderr, "Could not create output JPG %s", filename);
                return 3;
            }

            counter++;
        }

        //if any jpeg file exists writes on the file currently opened
        if (counter > 0)
        {
            fwrite(bf, 512, 1, img);
        }
    }

    //frees memory and closes files
    fclose(img);
    fclose(file);
    free(bf);
    return 0;
}
