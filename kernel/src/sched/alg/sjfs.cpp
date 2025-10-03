/* SPDX-License-Identifier: MIT */

/* StACSOS - Kernel
 *
 * Copyright (c) University of St Andrews 2024
 * Tom Spink <tcs6@st-andrews.ac.uk>
 */
#include <stacsos/kernel/debug.h>
#include <stacsos/kernel/sched/alg/sjfs.h>
#include <stacsos/kernel/sched/schedulable-entity.h>
#include <stacsos/kernel/arch/core.h>

using namespace stacsos::kernel::sched;
using namespace stacsos::kernel::sched::alg;


// MORE complicated than the others. The problem is that we need to maintain burst time predictions and actual burst times, so it requires modifying other classes and structs
// Preemptive form of shortest job first scheduling.
// This means that a shorter, newly arrived task will be given priorty over a running, previously selected task 

u64 shortest_job_first_scheduler::predict_next_burst(tcb &tcb)
{
	dprintf("predict call --------------------");
	// exponential averaging for estimating next burst time. 
	// source: https://www.scribd.com/document/524597322/8-Predicting-Burst-Time
	// not a 'good' source academically, but exponential averaging is a decent way to predict. The main pitfall is that this does not account for a randomly overlong burst.
	//
	// other heuristics/formulae exist, and the nice thing is that becaue the calculation is so compartmetalized, they an be changed easily. 

	if (last_burst_ == 0)
	{
		dprintf("last_burst is 0---------------\n");
		last_burst_ = 1000; // 1 timer cycle
	}
	if (last_burst_prediction_ == 0)
	{
		dprintf("last_burst_prediction is 0---------------\n");
		last_burst_prediction_ = 1000; // 1 timer cycle
	}
	u64 alpha = 0.5;	// prediction constant
	u64 t_n = last_burst_;
	u64 tau_n = last_burst_prediction_;


	// tau_(n+1) = alpha.t_n + (1 - alpha).tau_n
	u64 prediction = alpha * t_n + (1-alpha) * tau_n;

	dprintf("%u \n", prediction);
	return prediction;
} 

void shortest_job_first_scheduler::add_to_runqueue(tcb &tcb) 
{
	tcb.burst_estimate = predict_next_burst(tcb);
	runqueue_.enqueue(&tcb);
}

void shortest_job_first_scheduler::remove_from_runqueue(tcb &tcb)
{
	// last_burst = tcb.run_time;
	runqueue_.remove(&tcb);
}

tcb *shortest_job_first_scheduler::select_next_task(tcb *current)
{
	if (runqueue_.empty()) {
		return nullptr;
	}

	u64 time = 0;
	tcb *returner = nullptr;
	for (auto *thread : runqueue_)
	{
		// if burst time if less, change time to newest burst time, then change thread to this thread
		if (returner == nullptr || thread->burst_estimate < returner->burst_estimate)
		{
			last_burst_ = thread->run_time;
			returner = thread;
		}
	}
	return returner;
}

