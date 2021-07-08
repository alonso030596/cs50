/*
First three bytes of a JPEG [0xff][0xd8][0xff]
The fourth byte could vary from [0xe0, 0xef]

Each JPEG file comes in a block of 512 bytes
back to back, namely, the start of a new file
demarks the end of another. 


The files you generate should each be named ###.jpg, 
where ### is a three-digit decimal number, 
starting with 000 for the first image and counting up.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define JPEG_SIZE 512

typedef uint8_t  BYTE;

int isJPEG(BYTE*);

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./recover filename");
        return 1;
    }

    FILE* fp = fopen(argv[1], "r");

    if (fp == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
    }

    BYTE buffer[JPEG_SIZE];
    int nfiles = 0;
    char filename[8]; // ###.jpg
    size_t READ;

    while(fread(buffer, sizeof(BYTE), JPEG_SIZE, fp) == JPEG_SIZE) //READ 512 BYTES FROM FILE INTO BUFFER WHILE POSSIBLE
    {
        if(!isJPEG(buffer)) //IF JPEG SIGNATURE
        {
            nfiles++; //INCREMENT THE NUMBER OF FILES
            sprintf(filename, "%03i.jpg", nfiles);
            FILE* img = fopen(filename, "w"); //OPEN A NEW FILE

            if(img == NULL)
            {
                printf("Could not open %s.\n", filename);
            } 

            do
            {
                fwrite(buffer, sizeof(BYTE), JPEG_SIZE, img);
                READ = fread(buffer, sizeof(BYTE), JPEG_SIZE, fp);
            }
            while(READ == JPEG_SIZE && isJPEG(buffer));

            fseek(fp, -READ, SEEK_CUR);

            fclose(img);
        }
    } 
    fclose(fp);
}

int isJPEG(BYTE *buff)
{
    const BYTE signature[] = {0xff, 0xd8, 0xff};

    for (int i = 0; i < 3; i++)
    {
        if(*(buff + i) != *(signature + i))
            return 1;
    }
 
    if((*(buff + 3) & 0xf0) == 0xe0)
        return 0;
}