#include "json.h"
#include "nec.h"
#include "nic.h"
#include <stdio.h>

json json_init(void)
{
    const nic nop = { 0, 0, 0 };
    return (json){ nop, nop, nop, nop, nop };
}

#define json_set(__json_n, __json_d, __json_k, __json_v) \
( \
    nic_map(__json_d->keys, __json_k, (char*)__json_k), \
    nic_map(__json_d->__json_n, __json_k, __json_v) \
)

void json_set_int(json* dir, const char* key, int value)
{
    json_set(ints, dir, key, value);
}
void json_set_double(json* dir, const char* key, double value)
{
    json_set(doubles, dir, key, value);
}

void json_set_string(json* dir, const char* key, const char* value)
{
    json_set(strings, dir, key, value);
}

void json_set_object(json* dir, const char* key, json value)
{
    json_set(objects, dir, key, value);
}

int* json_get_int(const json* dir, const char* key)
{
    return nic_map_find(int, dir->ints, key);
}

double* json_get_double(const json* dir, const char* key)
{
    return nic_map_find(double, dir->doubles, key);
}

char** json_get_string(const json* dir, const char* key)
{
    return nic_map_find(char*, dir->strings, key);
}

json* json_get_object(const json* dir, const char* key)
{
    return nic_map_find(json, dir->objects, key);
}

void add_tab(FILE* fp, int n)
{
    while(n--) fprintf(fp, "    ");
}

void deep_write(FILE* fp, const json* dir, int dent)
{
    add_tab(fp, dent++);
    fprintf(fp, "{\n");
    for(int i = 0; i < nec_size(dir->keys.data); i++)
    {
        const char* key = ((char**)dir->keys.data)[i];
        int* ival = json_get_int(dir, key);
        double* dval = json_get_double(dir, key);
        char** sval = json_get_string(dir, key);
        json* oval = json_get_object(dir, key);
        add_tab(fp, dent);
        if(ival) fprintf(fp, "\"%s\": %d,\n", key, *ival);
        else if(dval) fprintf(fp, "\"%s\": %f,\n", key, *dval);
        else if(sval) fprintf(fp, "\"%s\": %s,\n", key, *sval);
    }
    add_tab(fp, dent - 1);
    fprintf(fp, "}\n");
}

void json_write(const json* dir, const char* path)
{
    FILE* fp = fopen(path, "w");
    deep_write(fp, dir, 0);
    fclose(fp);
}

