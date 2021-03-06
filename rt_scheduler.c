#include <assert.h>
#include <string.h>     /* memset */
#include "rt_scheduler.h"

/* ratio accuracy: exp2(-MAX_EXP); max 32 */
#define MAX_EXP     8

/**
 * Factorize n/d fraction (n < d) as:
 * n/d = b0 * exp2(-1) + b1 * exp2(-2) + ... + bMAX_EXP-1 * exp2(-MAX_EXP),
 * where bn is n-th bit of result.
 */
static uint32_t factorize_2(unsigned n, unsigned d)
{
    int i;
    uint32_t f2 = 0;

    assert(n < d);

    for (i = 0; i < MAX_EXP && n; i++) {
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
    const unsigned *prios, size_t prios_n, uint32_t *ratios, size_t *inds)
{
    size_t i;
    unsigned sum = 0;

    assert(prios_n > 1);
    memset(inds, 0, (prios_n - 1) * sizeof(inds[0]));

    for (i = 0; i < prios_n; i++)
        sum += prios[i];

    for (i = 0; i < prios_n - 1; i++) {
        ratios[i] = factorize_2(prios[i], sum);
        sum -= prios[i];
    }
    return prios_n - 1;
}

/**
 * Check index for a given ratio.
 *
 * The index is meant to align with the ratio if for some n-th factor of ratio
 * (exp2(-n), n = 1, 2, ...), the index equals exp2(n - 1) - 1 + exp2(n) * M,
 * for some M = 1, 2, ...
 *
 * So, for:
 * n = 1: index = 0 + 2 * M,
 * n = 2: index = 1 + 4 * M,
 * n = 3: index = 3 + 8 * M,
 * n = 4: index = 7 + 16 * M,
 * ...
 */
static bool check_index(uint32_t ratio, size_t ind)
{
    int i;

    for (i = 0; i < MAX_EXP; ratio >>= 1, i++) {
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
