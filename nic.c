#include "nic.h"
#include "nec.h"
#include <stdio.h>

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
    nic* chroot = root->l;
    nic* child = chroot->r;

    if(child && child->h == 1 && chroot->h == 2 && chroot->v < child->v && child->v < root->v)
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
    nic* chroot = root->r;
    nic* child = chroot->l;

    if(child && child->h == 1 && chroot->h == 2 && root->v < child->v && child->v < chroot->v)
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
    nic* temp;

    if(v > root->v)
    {
        if(root->r) temp = nic_insert(root->r, v);
        else temp = nic_create(v);
        if(!temp) return 0;
        root->r = temp;
    }
    else if(v < root->v)
    {
        if(root->l) temp = nic_insert(root->l, v);
        else temp = nic_create(v);
        if(!temp) return 0;
        root->l = temp;
    }
    else return 0;

    calc_height(root);

    int a = 0, b = 0;
    if(root->l) a = root->l->h;
    if(root->r) b = root->r->h;

    if(abs(a - b) > 1)
    {
        if(a - b > 0) root = ror(root);
        else root = rol(root);
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


