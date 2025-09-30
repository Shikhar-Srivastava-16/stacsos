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
	runqueue_.enqueue(&tcb);
}

void round_robin::remove_from_runqueue(tcb &tcb) {
	// remove jobs from the runqueue_
	runqueue_.remove(&tcb);
}


tcb *round_robin::select_next_task(tcb *current) { 
	if (runqueue_.empty()) {
		// return nothing if queue empty
		return nullptr;
	}
	
	for (auto *tcb_elem : runqueue_) {
		// basically debug information
		// useful to check if the round robin is actually moving things 'around'
		// this is the easiest way to check if the round robin is working as intended
		// that is, if the round robin process works as intended 
		// or if it works in another way that also happens to work as a scheduler
		// /usr/mandelbrot is a good way to test this, as is typing
		// typing uses only one, so it shows that queueing and dequeueing is working

		// In this case the element prints as a number (mem address) and allows us to 
		// see that the tcb objects go round and round as the round robin scheduler demands
		dprintf("-------queued thread %u-------\n", tcb_elem);
	}
	dprintf("\n\n");
	if (runqueue_.count() != 1) {
		// return first if queue is 1-long
		runqueue_.enqueue(runqueue_.dequeue());
	}

	return runqueue_.first();
}
