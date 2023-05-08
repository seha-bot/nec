#ifndef SEHA_NIC
#define SEHA_NIC

// NO INDEX CONTAINER
//
// Balanced binary tree.
// Made as a base for maps.

struct nic_node
{
    struct nic_node* l;
    struct nic_node* r;
    int h;
    int v;
};

typedef struct nic nic;
struct nic
{
    struct nic_node* memo;
    struct nic_node* root;
};

#define nic_push(a, v) ({ struct nic_node* temp = nic_insert(a.memo, a.root, v); temp ? a.root = temp : 0; })

struct nic_node* nic_insert(struct nic_node*, struct nic_node*, int);
void print(struct nic_node* root, char* path);

#endif /* SEHA_NIC */

