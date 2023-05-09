#include "nic.h"
#include "nec.h"
#include <stdio.h>

nicp* create(nicp* memo, void* data, int v)
{
    nicp n = { 0, 0, 1, v, 0 };
    nec_push(memo, n);
    return memo + nec_size(memo) - 1;
}

void calc_height(nicp* root)
{
    int h = 0;
    if(root->l) h = root->l->h;
    if(root->r) h = h > root->r->h ? h : root->r->h;
    root->h = h + 1;
}

nicp* rot(nicp* root, nicp** chroot, nicp** child, nicp* a, nicp* b)
{
    nicp *chr = *chroot, *chi = *child;
    if(chi && chi->h == 1 && chr->h == 2 && a->hash < chi->hash && chi->hash < b->hash)
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

nicp* insert(nicp* memo, nicp* root, void* data, int v)
{
    if(!root) return create(memo, data, v);
    if(v == root->hash) return 0;

    nicp** next = v > root->hash ? &root->r : &root->l;
    nicp* temp = insert(memo, *next, data, v);
    if(!temp) return 0;
    *next = temp;

    calc_height(root);

    v = root->l ? root->l->h : 0;
    if(root->r) v -= root->r->h;

    if(abs(v) > 1)
    {
        if(v > 0) root = rot(root, &root->l, &root->l->r, root->l, root);
        else      root = rot(root, &root->r, &root->r->l, root, root->r);
    }
    return root;
}

int nic_insert(nic* tree, int v)
{
    nicp* status = insert(tree->memo, tree->root, tree->data, v);
    if(status)
    {
        tree->root = status;
        return 1;
    }
    return 0;
}

int nic_find_impl(nicp* root, int v)
{
    if(!root) return 0;

    if(v < root->hash) return nic_find_impl(root->l, v);
    else if(v > root->hash) return nic_find_impl(root->r, v);
    else return 1;

    return 0;
}

void print(nicp* root, char* path)
{
    if(!root) return;
    printf("%s/%d\n", path, root->hash);
    nec_push(path, '\0');
    path[nec_size(path)-2] = 'l';
    print(root->l, path);
    path[nec_size(path)-2] = 'r';
    print(root->r, path);
    path[nec_size(path)-2] = '\0';
    nec_size_null(path)--;
}

