#ifndef SEHA_NIC
#define SEHA_NIC

#include "nec.h"

// NO INDEX CONTAINER
//
// Balanced binary tree.
// Made as a base for sets and maps.

struct nicp
{
    size_t l, r, data, hash;
    int h;
};
typedef struct nicp nicp;

typedef struct
{
    void* data;
    nicp *memo;
    size_t root;
} nic;

size_t nic_insert_hash(nicp**, size_t, size_t);
size_t nic_hash(char*);
nicp* nic_find_hash(nicp*, size_t, size_t);
void print(nicp*, size_t, char*);

#define nic_insert(__nic_a, __nic_v) \
({ \
    const size_t __nic_r = nic_insert_hash(&__nic_a.memo, __nic_a.root, __nic_v); \
    __nic_r ? __nic_a.root = __nic_r : 0; \
})

#define nic_imap(__nic_a, __nic_k, __nic_v) \
({ \
    const size_t __nic_r = nic_insert_hash(&__nic_a.memo, __nic_a.root, __nic_k); \
    if(__nic_r) \
    { \
        __nic_a.root = __nic_r; \
        typeof(__nic_v)* __nic_p = __nic_a.data; \
        nec_push(__nic_p, __nic_v); \
        __nic_a.data = __nic_p; \
        (__nic_a.memo + nec_size(__nic_a.memo) - 1)->data = nec_size(__nic_a.data) - 1; \
    } \
})

#define nic_map(__nic_a, __nic_k, __nic_v) nic_imap(__nic_a, nic_hash(__nic_k), __nic_v)

#define nic_imap_find(__nic_t, __nic_a, __nic_k) \
({ \
    nicp* __nic_r = nic_find_hash(__nic_a.memo, __nic_a.root, __nic_k); \
    __nic_r ? (__nic_t*)__nic_a.data + __nic_r->data : 0; \
})

#define nic_map_find(__nic_t, __nic_a, __nic_k) nic_imap_find(__nic_t, __nic_a, nic_hash(__nic_k))

#define nic_free(__nic_a) (nec_free(__nic_a.memo), nec_free(__nic_a.data))

#endif /* SEHA_NIC */

