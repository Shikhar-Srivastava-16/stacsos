/* SPDX-License-Identifier: MIT */

/* StACSOS - Kernel
 *
 * Copyright (c) University of St Andrews 2024
 * Tom Spink <tcs6@st-andrews.ac.uk>
 */
#include <stacsos/kernel/debug.h>
#include <stacsos/kernel/sched/alg/sfs.h>
#include <stacsos/kernel/sched/schedulable-entity.h>

using namespace stacsos::kernel::sched;
using namespace stacsos::kernel::sched::alg;

tcb *simple_fair_scheduler::select_next_task(tcb *current)
{
	if (runqueue_.empty()) {
		return nullptr;
	}

	if (runqueue_.count() == 1) {
		return runqueue_.first();
	}

	for (auto *tcb_elem : runqueue_) {
		// basically debug information
		// useful to check if the round robin is actually moving things 'around'
		// this is the easiest way to check if the round robin is working as intended
		// that is, if the round robin process works as intended 
		// or if it works in another way that also happens to work as a scheduler
		// /usr/mandelbrot is a good way to test this, as is typing
		// typing uses only one, so it shows that queueing and dequeueing is working
		// sched-test and sched-test are good for making sure the scheduler is running, 
		// but to check that is running as intended is not immediately obvious and requires more help. Running sched-test2 with this being printed is helpful

		// In this case the element prints as a number (mem address) and allows us to 
		// see that the tcb objects go round and round as the round robin scheduler demands
		// it also shows in any multithreaded program that the same thread runs multiple times. We know it is the same, because it is never declared stopped in the OS' debug feed on stdout 
		dprintf("-------queued thread %u, time: %u-------\n", tcb_elem, tcb_elem->run_time);
	}
	dprintf("\n\n");
	
	u64 min_runtime = 0;
	tcb *candidate = nullptr;

	for (auto *thread : runqueue_) {
		if (candidate == nullptr || (thread->run_time < min_runtime)) {
			min_runtime = thread->run_time;
			candidate = thread;
		}
	}

	return candidate;
}

