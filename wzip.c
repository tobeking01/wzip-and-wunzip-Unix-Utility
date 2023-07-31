#include <stdio.h>
#include <stdlib.h>

void compress(char *path)
{
    FILE *fp = fopen(path, "rb");
    char prev = 0, curr = 0;
    int count = 0;

    if(fp == NULL)
    {
        printf("[%s] file does not exist, exiting program ..\n", path);
        exit(1);
    }
    while(1)
    {
        // fgetc reads single character at a time and moves the
        // file pointer position to the next address/location
        // to read the next character
        curr = fgetc(fp);
        // EOF indicates the end of input
        if(curr == EOF)
        {
            // Write when end-of-file reached
            if(count > 0)
            {
            //  stdout is a pointer to a FILE stream that represents
            // the default output device for the application
                fwrite(&count, 1, 4, stdout);
                fwrite(&prev, 1, 1, stdout);
            }
            break;
        }
        if(curr != prev)
        {
            // We got a new character, so first write the count of previous *character
            if(count > 0)
            {
                fwrite(&count, 1, 4, stdout);
                fwrite(&prev, 1, 1, stdout);
            }
            count = 0;
        }
        count++;
        prev = curr;
    }
    fclose(fp);
}
int main(int argc, char **argv)
{
    int i = 0;
    if(argc < 2)
    {
        printf("wzip: file...\n");
        exit(1);
    }
    for(i = 1; i < argc; i++)
    {
        compress(argv[i]);
    }
    return 0;
}

