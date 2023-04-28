#ifndef SEHA_NIC
#define SEHA_NIC

// NO INDEX CONTAINER
//
// Balanced binary tree.
// Made as a base for maps.

typedef struct nic nic;
struct nic
{
    nic* l;
    nic* r;
    int v;
    int h;
};

#define nic_push(a, v) ( a = nic_insert(a,v) )

nic* nic_create(int v);
nic* nic_insert(nic*, int);

#endif /* SEHA_NIC */

