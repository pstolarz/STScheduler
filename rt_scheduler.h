#ifndef __RT_SCHEDULER_H__
#define __RT_SCHEDULER_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

/**
 * Initialize processing (ratios and indexes) tables basing on the priority
 * table. The initialized tables must have at least prios_n - 1 elements.
 *
 * Return number of elements in the initialized tables (that is: prios_n - 1).
 */
size_t rts_proc_tables(
    const unsigned *prios, size_t prios_n, uint32_t *ratios, size_t *inds);

/**
 * Get next priority id: 0 (highest), 1, 2, ...
 *
 * Ratio and indexes tables of size ratios_n as returned by rts_proc_tables().
 * Indexes table is updated accordingly after the call for the next routine
 * iteration.
 */
size_t rts_get_prio_id(const uint32_t *ratios, size_t *inds, size_t ratios_n);

#endif /* __RT_SCHEDULER_H__ */
