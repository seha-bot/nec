#include "nic.h"
#include <stdlib.h>

#define max(a, b) (a > b ? a : b)

nic* nic_create(int v)
{
    nic* n = (nic*)malloc(sizeof(nic));
    n->l = n->r = 0;
    n->h = 1;
    n->v = v;
    return n;
}

void calc_height(nic* root)
{
    int h = 0;
    if(root->l) h = root->l->h;
    if(root->r) h = max(h, root->r->h);
    root->h = h + 1;
}

nic* ror(nic* root)
{
    if(!root || !root->l) return root;
    nic* chroot = root->l;
    nic* child = chroot->r;

    if(child && child->h == 1 && chroot->v < child->v && child->v < root->v)
    {
        child->l = chroot;
        child->r = root;
        root->l = chroot->r = 0;
        root->h = chroot->h = 1;
        child->h = 2;
        return child;
    }

    chroot->r = root;
    root->l = child;
    calc_height(root);
    calc_height(chroot);
    return chroot;
}

//TODO: ror and rol should be 1 function (pass left and right as parameters)
nic* rol(nic* root)
{
    if(!root || !root->r) return root;
    nic* chroot = root->r;
    nic* child = chroot->l;

    if(child && child->h == 1 && root->v < child->v && child->v < chroot->v)
    {
        child->l = root;
        child->r = chroot;
        root->r = chroot->l = 0;
        root->h = chroot->h = 1;
        child->h = 2;
        return child;
    }

    chroot->l = root;
    root->r = child;
    calc_height(root);
    calc_height(chroot);
    return chroot;
}

nic* nic_insert(nic* root, int v)
{
    if(!root) return nic_create(v);
    nic* child = 0;

    if(v > root->v)
    {
        if(root->r) child = nic_insert(root->r, v);
        else
        {
            child = nic_create(v);
            root->r = child;
        }
    }
    else if(v < root->v)
    {
        if(root->l) child = nic_insert(root->l, v);
        else
        {
            child = nic_create(v);
            root->l = child;
        }
    }
    else return 0;

    calc_height(root);

    int a = 0, b = 0;
    if(root->l) a = root->l->h;
    if(root->r) b = root->r->h;

    if(abs(a - b) > 1)
    {
        if(b > 0) root = ror(root);
        else root = rol(root);
    }
    return root;
}

