#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *load_file(const char *path)
{
    FILE *file = fopen(path, "rb");

    if (file == NULL)
    {
        printf("Could not open file: %s\n", path);
        return 0;
    }

    fseek(file, 0, SEEK_END);
    unsigned long length = ftell(file);
    char *data = (char *)malloc(sizeof(char) * (length + 1));
    memset(data, 0, length + 1);
    fseek(file, 0, SEEK_SET);
    fread(data, 1, length, file);
    fclose(file);

    return data;
}