#include "json.h"
#include <stdio.h>

json json_init(void)
{
    const nic nop = { 0, 0, 0 };
    return (json){ nop, nop, nop, nop, nop };
}

void json_write(const json* dir, const char* path)
{
    FILE* fp = fopen(path, "w");
    for(int i = 0; i < nec_size(dir->keys.data); i++)
    {
        char* key = ((char**)dir->keys.data)[i];
        printf("HERE\n");
        fprintf(fp, "%s: \n", key);
    }
    fclose(fp);
}

