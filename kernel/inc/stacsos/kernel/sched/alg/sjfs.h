/* SPDX-License-Identifier: MIT */

/* StACSOS - Kernel
 *
 * Copyright (c) University of St Andrews 2024
 * Tom Spink <tcs6@st-andrews.ac.uk>
 */
#pragma once

#include <stacsos/kernel/sched/alg/scheduling-algorithm.h>
#include <stacsos/list.h>

namespace stacsos::kernel::sched::alg {

class shortest_job_first_scheduler : public scheduling_algorithm {
public:
	virtual void add_to_runqueue(tcb &tcb) override;
	virtual void remove_from_runqueue(tcb &tcb) override;
	virtual tcb *select_next_task(tcb *current) override;
	virtual const char *name() const { return "shortest job first"; }
	u64 last_burst;
	u64 last_burst_prediction;

private:
	list<tcb *> runqueue_;
};
} // namespace stacsos::kernel::sched::alg
