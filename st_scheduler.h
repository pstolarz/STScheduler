#ifndef __ST_SCHEDULER_H__
#define __ST_SCHEDULER_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * Initialize processing (ratios and indexes) tables basing on the times table.
 * The initialized tables must have at least ts_n - 1 elements.
 *
 * Return number of elements in the initialized tables (that is: ts_n - 1).
 */
size_t sts_init_proc_tables(
    const uint32_t *ts, size_t ts_n, uint32_t *ratios, size_t *inds);

/**
 * Get next priority id: 0 (highest), 1, 2, ...
 *
 * Ratio and indexes tables of size ratios_n as returned by sts_init_proc_tables().
 * Indexes table is updated accordingly for the next routine iteration.
 */
size_t sts_get_prio_id(const uint32_t *ratios, size_t *inds, size_t ratios_n);

#endif /* __ST_SCHEDULER_H__ */
