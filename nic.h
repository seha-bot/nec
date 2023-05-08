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
    int h;
    int v;
};

#define nic_push(m, a, v) ({ nic* temp = nic_insert(m, a, v); temp ? a = temp : 0; })

nic* nic_insert(nic*, nic*, int);
void print(nic* root, char* path);

#endif /* SEHA_NIC */

