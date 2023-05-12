#ifndef SEHA_NEC
#define SEHA_NEC

#include <stdlib.h>

#define nec_size_null(__nec_a) (*((int*)__nec_a - 1))
#define nec_size(__nec_a) (__nec_a ? nec_size_null(__nec_a) : 0)

#define nec_add(__nec_a) \
({ \
    int __nec_s = nec_size(__nec_a) + 1; \
    __nec_a = (void*)((int*)realloc((int*)__nec_a - (__nec_a != 0), sizeof(int) + sizeof(*__nec_a) * __nec_s) + 1); \
    nec_size_null(__nec_a) = __nec_s; \
})

#define nec_push(__nec_a, __nec_v) (nec_add(__nec_a), (__nec_a)[nec_size(__nec_a) - 1] = __nec_v)
#define nec_free(__nic_a) (free((int*)__nic_a - (__nic_a != 0)), __nic_a = 0)

#endif /* SEHA_NEC */

