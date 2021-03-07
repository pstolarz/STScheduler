#include <assert.h>
#include <string.h>     /* memset */
#include "rt_scheduler.h"

/* ratio accuracy: exp2(-M); max 32 */
#ifndef CONFIG_RTS_M
# define CONFIG_RTS_M   8
#endif

/**
 * Factorize n/d fraction (n < d) as:
 * n/d = a1 * exp2(-1) + a2 * exp2(-2) + ... + aMAX_EXP * exp2(-M),
 * where an is (n - 1)-th bit of result.
 */
static uint32_t factorize_2(unsigned n, unsigned d)
{
    int i;
    uint32_t f2 = 0;

    assert(n < d);

    for (i = 0; i < CONFIG_RTS_M && n; i++) {
        n <<= 1;
        if (n >= d) {
            f2 |= (1 << i);
            n -= d;
        }
    }
    return f2;
}

/* exported; see header for details */
size_t rts_proc_tables(
    const unsigned *ts, size_t ts_n, uint32_t *ratios, size_t *inds)
{
    size_t i;
    unsigned sum = 0;

    assert(ts_n > 1);
    memset(inds, 0, (ts_n - 1) * sizeof(inds[0]));

    for (i = 0; i < ts_n; i++)
        sum += ts[i];

    for (i = 0; i < ts_n - 1; i++) {
        ratios[i] = factorize_2(ts[i], sum);
        sum -= ts[i];
    }
    return ts_n - 1;
}

/**
 * Check index for a given ratio.
 *
 * The index is meant to align with the ratio if for some n-th factor of ratio
 * (exp2(-n), n = 1, 2, ...), the index equals exp2(n - 1) - 1 + exp2(n) * i,
 * for some i = 1, 2, ...
 *
 * So, for:
 * n = 1: index = 0 + 2 * i,
 * n = 2: index = 1 + 4 * i,
 * n = 3: index = 3 + 8 * i,
 * n = 4: index = 7 + 16 * i,
 * ...
 */
static bool check_index(uint32_t ratio, size_t ind)
{
    int i;

    for (i = 0; i < CONFIG_RTS_M; ratio >>= 1, i++) {
        if (!(ratio & 1))
            continue;
        else if (!((ind - ((1 << i) - 1)) & ((1 << (i + 1)) - 1)))
            return true;
    }
    return false;
}

/* exported; see header for details */
size_t rts_get_prio_id(const uint32_t *ratios, size_t *inds, size_t ratios_n)
{
    size_t i, prio_i;

    for (i = 0;; i++) {
        if (check_index(ratios[i], inds[i])) {
            prio_i = i;
            do { inds[i]++; } while (i--);
            break;
        } else if (i + 1 >= ratios_n) {
            prio_i = ratios_n;
            do { inds[i]++; } while (i--);
            break;
        }
    }
    return prio_i;
}
