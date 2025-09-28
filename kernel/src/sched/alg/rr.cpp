/* SPDX-License-Identifier: MIT */

/* StACSOS - Kernel
 *
 * Copyright (c) University of St Andrews 2024
 * Tom Spink <tcs6@st-andrews.ac.uk>
 */
#include <stacsos/kernel/sched/alg/rr.h>
#include <stacsos/kernel/debug.h>
#include <stacsos/kernel/sched/schedulable-entity.h>

// *** COURSEWORK NOTE *** //
// This will be where you are implementing your round-robin scheduling algorithm.
// Please edit this file in any way you see fit.  You may also edit the rr.h
// header file.

using namespace stacsos::kernel::sched;
using namespace stacsos::kernel::sched::alg;

void round_robin::add_to_runqueue(tcb &tcb) { 
	// runqueue_ is a queue full of tcbs. each tcb handles a thread
	// dprintf("-----------------queueing task---------------\n");
	runqueue_.enqueue(&tcb);
}

void round_robin::remove_from_runqueue(tcb &tcb) {
	// remove jobs from the runqueue_
	// dprintf("----------------removing queued task-------------\n");
	runqueue_.remove(&tcb);
}


tcb *round_robin::select_next_task(tcb *current) { 
	// dprintf("rr call \n");

	if (runqueue_.empty()) {
		// return nothing if queue empty
		return nullptr;
	}

	if (runqueue_.count() == 1) {
		// return first if queue is 1-long
		return runqueue_.first();
	}

	// counter, only for doc and test
	u64 counter = 0;
	for (auto *tcb_elem : runqueue_) {
		dprintf("-------queued thread: %u-------\n", counter);
		counter++;
	}
	dprintf("current threads: %u\n", counter);
	
	runqueue_.enqueue(runqueue_.dequeue());

	return runqueue_.first();
}
