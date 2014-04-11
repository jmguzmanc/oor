/*
 * lispd_map_cache.h
 *
 * This file is part of LISP Mobile Node Implementation.
 * Send registration messages for each database mapping to
 * configured map-servers.
 *
 * Copyright (C) 2011 Cisco Systems, Inc, 2011. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Please send any bug reports or fixes you make to the email address(es):
 *    LISP-MN developers <devel@lispmob.org>
 *
 * Written or modified by:
 *    Albert Lopez      <alopez@ac.upc.edu>
 */

#ifndef LISPD_MAP_CACHE_H_
#define LISPD_MAP_CACHE_H_

#include <lispd_types.h>
#include <lispd_timers.h>
//#include "lispd_afi.h"
//#include "lispd_address.h"

/*
 *  map-cache entry types (how_learned)
 */

#define STATIC_MAP_CACHE_ENTRY          0
#define DYNAMIC_MAP_CACHE_ENTRY         1

/*
 *  map-cache entry activated  (received map reply)
 */
#define NO_ACTIVE                       0
#define ACTIVE                          1

typedef struct lispd_map_cache_entry_ {
    mapping_t *mapping;
    uint8_t how_learned :2;
    uint8_t actions :2;
    uint8_t active :1; /* TRUE if we have received a map reply for this entry */
    uint8_t active_witin_period :1;
    uint32_t ttl;
    time_t timestamp;
    timer *expiry_cache_timer;
    timer *request_retry_timer;
    timer *smr_inv_timer;
    nonces_list *nonces;
} map_cache_entry_t;

map_cache_entry_t *mcache_entry_new();
void mcache_entry_init(map_cache_entry_t *mce, mapping_t *mapping);
void mcache_entry_init_static(map_cache_entry_t *mce, mapping_t *mapping);


map_cache_entry_t *new_map_cache_entry(lisp_addr_t eid_prefix,
        int eid_prefix_length, int how_learned, uint16_t ttl);


map_cache_entry_t *new_map_cache_entry_no_db(lisp_addr_t eid_prefix,
        int eid_prefix_length, int how_learned, uint16_t ttl);
void map_cache_entry_del(map_cache_entry_t *entry);
void map_cache_entry_dump(map_cache_entry_t *entry, int log_level);

static inline void mcache_entry_set_eid_addr(map_cache_entry_t *, lisp_addr_t *);
static inline void mcache_entry_set_eid_plen(map_cache_entry_t *, uint8_t);
static inline mapping_t *mcache_entry_mapping(map_cache_entry_t*);
static inline lisp_addr_t *mcache_entry_get_eid_addr(map_cache_entry_t*);
static inline nonces_list *mcache_entry_nonces_list(map_cache_entry_t *);
static inline uint8_t mcache_entry_active(map_cache_entry_t *);

static inline void mcache_entry_set_eid_addr(map_cache_entry_t *mce,
        lisp_addr_t *addr) {
    mapping_set_eid_addr(mcache_entry_mapping(mce), addr);
}

static inline mapping_t *mcache_entry_mapping(map_cache_entry_t* mce) {
    return (mce->mapping);
}

static inline nonces_list *mcache_entry_nonces_list(map_cache_entry_t *mce) {
    return (mce->nonces);
}

static inline uint8_t mcache_entry_active(map_cache_entry_t *mce) {
    return (mce->active);
}
#endif /* LISPD_MAP_CACHE_H_ */
