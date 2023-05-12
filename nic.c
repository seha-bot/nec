#include "nic.h"
#include "nec.h"
#include <stdio.h>

size_t create(nicp** memo, int hash)
{
    nicp n = { 0, 0, 0, 1, hash };
    nec_push(*memo, n);
    return nec_size(*memo);
}

void calc_height(nicp** memo, nicp* root)
{
    int h = 0;
    root->h = (*memo + root->r - 1)->h;
    if(root->l) h = (*memo + root->l - 1)->h;
    if(root->r) h = h > root->h ? h : root->h;
    root->h = h + 1;
}

size_t rot(nicp** memo, nicp* root, size_t* chroot, size_t* child, nicp* a, nicp* b)
{
    nicp *chr = *memo + *chroot - 1, *chi = *memo + *child - 1;
    if(chi && chi->h == 1 && chr->h == 2 && a->hash < chi->hash && chi->hash < b->hash)
    {
        chi->l = a - *memo + 1;
        chi->r = b - *memo + 1;
        *child = *chroot = 0;
        root->h = chr->h = 1;
        chi->h = 2;
        return chi - *memo + 1;
    }

    *child = root - *memo + 1;
    *chroot = chi - *memo + 1;
    calc_height(memo, root);
    calc_height(memo, chr);
    return chr - *memo + 1;
}

size_t nic_insert_hash(nicp** memo, size_t root, int hash)
{
    if(!root) return create(memo, hash);
    nicp* rp = *memo + root - 1;

    if(hash > rp->hash)
    {
        hash = nic_insert_hash(memo, rp->r, hash);
        if(!hash) return 0;
        rp = *memo + root - 1;
        rp->r = hash;
    }
    else if(hash < rp->hash)
    {
        hash = nic_insert_hash(memo, rp->l, hash);
        if(!hash) return 0;
        rp = *memo + root - 1;
        rp->l = hash;
    }
    else return 0;

    calc_height(memo, rp);

    nicp *l = *memo + rp->l - 1, *r = *memo + rp->r - 1;
    hash = rp->l ? l->h : 0;
    if(rp->r) hash -= r->h;
    if(abs(hash) < 2) return root;
    if(hash > 0) return rot(memo, rp, &rp->l, &l->r, l, rp);
    return rot(memo, rp, &rp->r, &r->l, rp, r);
}

void print(nicp* memo, size_t root, char* path)
{
    if(!root) return;
    nicp* rpa = memo + root - 1;
    nec_push(path, '\0');
    printf("%s/%d\n", path, rpa->hash);
    path[nec_size(path)-1] = 'l';
    print(memo, rpa->l, path);
    path[nec_size(path)-1] = 'r';
    print(memo, rpa->r, path);
    nec_pop(path);
}

