#include "nic.h"
#include "nec.h"
#include <stdio.h>

#define nic struct nic_node

nic* nic_create(nic* memo, int v)
{
    nic n = { 0, 0, 1, v };
    nec_push(memo, n);
    return memo + nec_size(memo) - 1;
}

void calc_height(nic* root)
{
    int h = 0;
    if(root->l) h = root->l->h;
    if(root->r) h = h > root->r->h ? h : root->r->h;
    root->h = h + 1;
}

nic* rot(nic* root, nic** chroot, nic** child, nic* a, nic* b)
{
    nic *chr = *chroot, *chi = *child;
    if(chi && chi->h == 1 && chr->h == 2 && a->v < chi->v && chi->v < b->v)
    {
        chi->l = a;
        chi->r = b;
        *child = *chroot = 0;
        root->h = chr->h = 1;
        chi->h = 2;
        return chi;
    }

    *child = root;
    *chroot = chi;
    calc_height(root);
    calc_height(chr);
    return chr;
}

nic* nic_insert(nic* memo, nic* root, int v)
{
    if(!root) return nic_create(memo, v);
    if(v == root->v) return 0;

    nic* temp;
    nic** next = v > root->v ? &root->r : &root->l;
    if(*next) temp = nic_insert(memo, *next, v);
    else temp = nic_create(memo, v);
    if(!temp) return 0;
    *next = temp;

    calc_height(root);

    int a = 0, b = 0;
    if(root->l) a = root->l->h;
    if(root->r) b = root->r->h;

    if(abs(a - b) > 1)
    {
        if(a - b > 0) root = rot(root, &root->l, &root->l->r, root->l, root);
        else          root = rot(root, &root->r, &root->r->l, root, root->r);
    }
    return root;
}

void print(nic* root, char* path)
{
    if(!root) return;
    printf("%s/%d\n", path, root->v);
    nec_push(path, '\0');
    path[nec_size(path)-2] = 'l';
    print(root->l, path);
    path[nec_size(path)-2] = 'r';
    print(root->r, path);
    path[nec_size(path)-2] = '\0';
    nec_size_null(path)--;
}


