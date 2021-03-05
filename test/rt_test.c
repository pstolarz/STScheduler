#include <stdio.h>
#include "rt_sched.h"

#define ARR_SZ(__a) (sizeof(__a)/sizeof(__a[0]))

int main()
{
    const unsigned prios[] = {256, 128, 64, 32, 16, 8, 4, 2, 1, 1};
//    const unsigned prios[] = {30, 28, 20, 14, 8};
//    const unsigned prios[] = {64, 56, 48, 40, 32, 16};

    size_t inds[ARR_SZ(prios) - 1];
    uint32_t ratios[ARR_SZ(prios) - 1];

    size_t ratios_n = rts_init_tables(prios, ARR_SZ(prios), ratios, inds);

    for (int i = 0; i < 512; i++)
        printf("%d\n", (int)rts_get_prio_id(ratios, inds, ratios_n));

    return 0;
}
