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
	runqueue_.enqueue(tcb);
}

void round_robin::remove_from_runqueue(tcb &tcb) { panic("TODO: rr_rem_runqueue"); }


// tcb is the thread control block
tcb *round_robin::select_next_task(tcb *current) { panic("TODO: rr_select"); }
