#include <stdio.h>
#include <stdlib.h>
void decompress(char *path)
{
    char curr = 0;
    int count = 0;
    FILE *fp = fopen(path, "r");
    if(fp == NULL)
    {
        printf("[%s] file does not exist, exiting program ..\n", path);
        exit(1);
    }
    while(1)
    {
        int bytes = fread(&count, 1, 4, fp);
        if(bytes != 4)
        {
            break;
        }
        fread(&curr, 1, 1, fp);
        {
            int i = 0;
            for(i = 0; i < count; i++)
            {
                fwrite(&curr, 1, 1, stdout);
            }
        }
    }
    fclose(fp);
}
int main(int argc, char **argv)
{
    int i = 0;
    if(argc < 2)
    {
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }
    for(i = 1; i < argc; i++)
    {
        decompress(argv[i]);
    }
    return 0;
}

