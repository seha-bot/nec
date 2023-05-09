#ifndef SEHA_NIC
#define SEHA_NIC

// NO INDEX CONTAINER
//
// Balanced binary tree.
// Made as a base for sets and maps.

struct nicp
{
    struct nicp* l;
    struct nicp* r;
    int h;
    int hash;
    void* data;
};
typedef struct nicp nicp;

typedef struct
{
    void* data;
    nicp* memo;
    nicp* root;
} nic;

#define nic_find(a, v) nic_find_impl(a.root, v)
#define nic_free(a) nec_free(a.memo)

int nic_insert(nic*, int);
int nic_find_impl(nicp*, int);
void print(nicp*, char*);

#endif /* SEHA_NIC */

