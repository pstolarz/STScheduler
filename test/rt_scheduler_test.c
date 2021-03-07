#include <stdio.h>
#include "rt_scheduler.h"

#define ARR_SZ(__a) (sizeof(__a)/sizeof(__a[0]))

int main()
{
    const unsigned ts[] = {256, 128, 64, 32, 16, 8, 4, 2, 1, 1};

    size_t inds[ARR_SZ(ts) - 1];
    uint32_t ratios[ARR_SZ(ts) - 1];

    size_t ratios_n = rts_init_proc_tables(ts, ARR_SZ(ts), ratios, inds);

    for (int i = 0; i < 512; i++)
        printf("%d\n", (int)rts_get_prio_id(ratios, inds, ratios_n));

    return 0;
}
