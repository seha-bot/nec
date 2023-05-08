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

#define nic_push(a, v) ({ nic* temp = nic_insert(a, v); temp ? a = temp : 0; })

nic* nic_create(int v);
nic* nic_insert(nic*, int);
nic* ror(nic*);
nic* rol(nic*);
void print(nic* root, char* path);

#endif /* SEHA_NIC */

