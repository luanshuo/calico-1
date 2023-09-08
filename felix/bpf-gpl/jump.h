// Project Calico BPF dataplane programs.
// Copyright (c) 2020-2022 Tigera, Inc. All rights reserved.
// SPDX-License-Identifier: Apache-2.0 OR GPL-2.0-or-later

#ifndef __CALI_BPF_JUMP_H__
#define __CALI_BPF_JUMP_H__

#include "conntrack.h"
#include "policy.h"

CALI_MAP(cali_state, 2,
		BPF_MAP_TYPE_PERCPU_ARRAY,
		__u32, struct cali_tc_state,
		1, 0)

static CALI_BPF_INLINE struct cali_tc_state *state_get(void)
{
	__u32 key = 0;
	return cali_state_lookup_elem(&key);
}

CALI_MAP(cali_jump, 3, BPF_MAP_TYPE_PROG_ARRAY, __u32, __u32, 32, 0)

#define CALI_JUMP_TO(ctx, index) bpf_tail_call(ctx, &map_symbol(cali_jump, 3), index)

/* Add new values to the end as these are program indices */
enum cali_jump_index {
	PROG_INDEX_NO_DEBUG,
	PROG_INDEX_DEBUG,
	PROG_INDEX_POLICY,
	PROG_INDEX_ALLOWED,
	PROG_INDEX_ICMP,
	PROG_INDEX_DROP,
	PROG_INDEX_HOST_CT_CONFLICT,
	PROG_INDEX_V6_PROLOGUE,
	PROG_INDEX_V6_POLICY,
	PROG_INDEX_V6_ALLOWED,
	PROG_INDEX_V6_ICMP,
	PROG_INDEX_V6_DROP,
};

#endif /* __CALI_BPF_JUMP_H__ */
