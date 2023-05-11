#ifndef SEHA_NIC
#define SEHA_NIC

#include "nec.h"

// NO INDEX CONTAINER
//
// Balanced binary tree.
// Made as a base for sets and maps.

#define nic_use(n, t) \
struct nicp##n { int l, r, h, hash; t* data; }; \
typedef struct nicp##n nicp##n; \
typedef struct { t* data; nicp##n *memo; int root; } nic##n;

nic_use(,void);

int nic_insert_hash(nicp**, int, int);
int nic_find_impl(nicp*, int);
void print(nicp*, int, char*);

#define nic_insert(__nic_a, __nic_v) \
({ \
    int __nic_r = nic_insert_hash((nicp**)&__nic_a.memo, __nic_a.root, __nic_v); \
    __nic_r ? (__nic_a.root = __nic_r, 1) : 0; \
})
#define nic_find(a, v) nic_find_impl(a.root, v)
#define nic_free(a) nec_free(a.memo)

#endif /* SEHA_NIC */

