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
		// sched-test and sched-test are good for making sure the scheduler is running, 
		// but to check that is running as intended is not immediately obvious and requires more help. Running sched-test2 with this being printed is helpful

		// In this case the element prints as a number (mem address) and allows us to 
		// see that the tcb objects go round and round as the round robin scheduler demands
		// it also shows in any multithreaded program that the same thread runs multiple times. We know it is the same, because it is never declared stopped in the OS' debug feed on stdout 
		
		/*
		`	proc: thread stopped
			-------queued thread 4102160, time: 12584836-------
			-------queued thread 4102416, time: 38698820-------
			-------queued thread 4103440, time: 4124727596-------
			-------queued thread 4101648, time: 64815628-------
			
			
			-------queued thread 4102416, time: 90933310-------
			-------queued thread 4103440, time: 4124727596-------
			-------queued thread 4101648, time: 64815628-------
			-------queued thread 4102160, time: 12584836-------
			
			
			proc: thread stopped
			-------queued thread 4101648, time: 64815628-------
			-------queued thread 4102160, time: 12584836-------
			-------queued thread 4102416, time: 90933310-------
			
			
			-------queued thread 4102160, time: 117049774-------
			-------queued thread 4102416, time: 90933310-------
			-------queued thread 4101648, time: 64815628-------
		*/
		
		// That shows that there are threads being rotated properly even when some of them are being stopped

		dprintf("-------queued thread %u, time: %u-------\n", tcb_elem, tcb_elem->run_time);
	}
	dprintf("\n\n");
	if (runqueue_.count() != 1) {
		// rotate if there is more than one tcb 
		// same as doing runqueue_.enqueue(runqueue_.dequeue());
		runqueue_.rotate();
	}

	return runqueue_.first();
}
