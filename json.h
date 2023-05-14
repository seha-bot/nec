#ifndef SEHA_JSON
#define SEHA_JSON

#include "nic.h"

typedef struct
{
    nic ints;
    nic doubles;
    nic strings;
    nic objects;
} json;

json json_init(void);
void json_insert_int(json*, char*, int);
void json_insert_double(json*, char*, double);
void json_insert_string(json*, char*, char*);
void json_insert_object(json*, char*, json);

int json_get_int(json*, char*);
double json_get_double(json*, char*);
char* json_get_string(json*, char*);
json json_get_object(json*, char*);

#endif /* SEHA_JSON */

