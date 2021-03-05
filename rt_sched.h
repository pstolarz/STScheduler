#ifndef __RT_SCHED_H__
#define __RT_SCHED_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

size_t rts_init_tables(
    const unsigned *prios, size_t prios_n, uint32_t *ratios, size_t *inds);

size_t rts_get_prio_id(const uint32_t *ratios, size_t *inds, size_t ratios_n);

#endif /* __RT_SCHED_H__ */
