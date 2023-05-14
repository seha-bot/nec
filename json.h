#ifndef SEHA_JSON
#define SEHA_JSON

#include "nic.h"

typedef struct
{
    nic keys;
    nic ints;
    nic doubles;
    nic strings;
    nic objects;
} json;

json json_init(void);
void json_write(const json*, const char*);

#define json_set(__json_t, __json_d, __json_k, __json_v) \
( \
    nic_map(__json_d.keys, __json_k, (char*)__json_k), \
    nic_map(__json_d.__json_t##s, __json_k, (__json_t)__json_v) \
)
#define json_get(__json_t, __json_d, __json_k) nic_map_find(__json_t, __json_d.__json_t##s, __json_k)

#define json_free(__json_d) \
( \
    nic_free(__json_d.keys), \
    nic_free(__json_d.ints), \
    nic_free(__json_d.doubles), \
    nic_free(__json_d.strings), \
    nic_free(__json_d.objects) \
)

#endif /* SEHA_JSON */

