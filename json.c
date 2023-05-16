#include "json.h"
#include "nec.h"
#include "nic.h"
#include <stdarg.h>
#include <stdio.h>

json json_init(void)
{
    const nic nop = { 0, 0, 0 };
    return (json){ nop, nop, nop, nop, nop };
}

char* json_truncate(const char* src)
{
    char* buff = 0;
    char safe = 1, c;
    while(*src++)
    {
        c = *(src - 1);
        if(safe && (c == ' ' || c == '\n' || c == '\r')) continue;
        if(c == '"' && (safe || *(src - 2) != '\\')) safe = !safe;
        nec_push(buff, c);
    }
    return buff;
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

// TODO this doesn't belong here
void nec_printf(char** buff, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    int n = vsnprintf(0, 0, format, args);
    int start = nec_size(*buff);
    if(!start) n++;
    else start--;
    while(n--) nec_push(*buff, 0);
    vsprintf(*buff + start, format, args);
    va_end(args);
}

void add_tab(char** buff, int n)
{
    while(n--) nec_printf(buff, "    ");
}

void safe_quotes(char** buff, const char* src)
{
    (*buff)[nec_size(*buff) - 1] = '"';
    while(*src)
    {
        if(*src == '"') nec_push(*buff, '\\');
        nec_push(*buff, *src);
        src++;
    }
    nec_push(*buff, '"');
    nec_push(*buff, '\0');
}

void deep_write(char** buff, const json* dir, int dent)
{
    nec_printf(buff, "{\n");
    for(int i = 0; i < nec_size(dir->keys.data); i++)
    {
        const char* key = ((char**)dir->keys.data)[i];
        int* ival = json_get_int(dir, key);
        double* dval = json_get_double(dir, key);
        char** sval = json_get_string(dir, key);
        json* oval = json_get_object(dir, key);
        add_tab(buff, dent);
        nec_printf(buff, "\"%s\": ", key);
        if(ival) nec_printf(buff, "%d", *ival);
        else if(dval) nec_printf(buff, "%f", *dval);
        else if(sval) safe_quotes(buff, *sval);
        else if(oval) deep_write(buff, oval, dent + 1);

        if(i != nec_size(dir->keys.data) - 1) nec_printf(buff, ",");
        nec_printf(buff, "\n");
    }
    add_tab(buff, dent - 1);
    nec_printf(buff, "}");
}

char* json_write(const json* dir)
{
    char* buff = 0;
    deep_write(&buff, dir, 1);
    return buff;
}

json json_read(const char* buff)
{
    json dir = json_init();
    return dir;
}

