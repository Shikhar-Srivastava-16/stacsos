/* SPDX-License-Identifier: MIT */

/* StACSOS - Kernel
 *
 * Copyright (c) University of St Andrews 2024
 * Tom Spink <tcs6@st-andrews.ac.uk>
 */
#include <stacsos/kernel/debug.h>
#include <stacsos/kernel/sched/alg/fcfs.h>
#include <stacsos/kernel/sched/schedulable-entity.h>

using namespace stacsos::kernel::sched;
using namespace stacsos::kernel::sched::alg;

tcb *first_come_first_serve_scheduler::select_next_task(tcb *current)
{
	if (runqueue_.empty()) {
		return nullptr;
	}
	
	return runqueue_.first();
}

