#ifndef SEHA_NIC
#define SEHA_NIC

#include "nec.h"

// NO INDEX CONTAINER
//
// Balanced binary tree.
// Made as a base for sets and maps.

struct nicp
{
    size_t l, r, data;
    int h, hash;
};
typedef struct nicp nicp;

typedef struct
{
    void* data;
    nicp *memo;
    size_t root;
} nic;

size_t nic_insert_hash(nicp**, size_t, int);
void print(nicp*, size_t, char*);

#define nic_map(__nic_a, __nic_k, __nic_v) \
({ \
    size_t __nic_r = nic_insert_hash(&__nic_a.memo, __nic_a.root, __nic_k); \
    __nic_r ? ({ \
        __nic_a.root = __nic_r; \
        typeof(__nic_v)* place = __nic_a.data; \
        nec_push(place, __nic_v); \
        __nic_a.data = place; \
        nicp* last = __nic_a.memo + nec_size(__nic_a.memo) - 1; \
        last->data = nec_size(__nic_a.data) - 1; \
    }) : 0; \
})
#define nic_insert(__nic_a, __nic_v) \
({ \
    size_t __nic_r = nic_insert_hash(&__nic_a.memo, __nic_a.root, __nic_v); \
    __nic_r ? __nic_a.root = __nic_r : 0; \
})
#define nic_free(a) nec_free(a.memo)

#endif /* SEHA_NIC */

