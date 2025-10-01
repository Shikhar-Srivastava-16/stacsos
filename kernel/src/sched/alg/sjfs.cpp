/* SPDX-License-Identifier: MIT */

/* StACSOS - Kernel
 *
 * Copyright (c) University of St Andrews 2024
 * Tom Spink <tcs6@st-andrews.ac.uk>
 */
#include <stacsos/kernel/debug.h>
#include <stacsos/kernel/sched/alg/sjfs.h>
#include <stacsos/kernel/sched/schedulable-entity.h>

using namespace stacsos::kernel::sched;
using namespace stacsos::kernel::sched::alg;


// here, the queue will be ordered by the length of the runtime
// this means that the the 'collection' of tcb objects must be ordered by runtime in ascending order
// this will ensure that the first element is also the shortest job.
// the scheduler task is called periodically, not just when the tasks are finished. 
// This means that there is a primitive form of preempting. The kernel interrupts the thread periodically
// What this means is that this is not shortest job first, it is actually shortest remaining time first. 
// What does this mean? The only thing whch needs to be controlled is the order in which the 

// The queueing method has to actually maintain an order because the runqueue is not actually a proper queue. In effect, what it needs to do is to calculate a burst time and assign it to the heap. Then, put it into the right place in the queue

// MORE complicated than the others. The problem is that we need to maintain burst time predictions and actual burst times

void shortest_job_first_scheduler::add_to_runqueue(tcb &tcb) 
{
// 	for (int i = 0; i < runqueue_.count(); i++) 
// 	{
// 		tcb tcb = runqueue_.at(i);
// 		tcb tcb2 = runqueue_.at(i+1);
// 		// if tcb burst is less than AND tcb2 burst is more than, add to i + 1 
// 		
// 	}	
	runqueue_.enqueue(&tcb);
}


// TODO: DRAWING FROM QUEUE SETS THE LATEST BURST TIME
// TODO ADDING TO QUEUE: CALC BURST TIME AND SET IT IN THE TCB

// u64 shortest_job_first_scheduler::predict_burst()
// {
// 	u64 alpha = 0.5;	// prediction
// 	u64 tau_n = last_burst_prediction;
// 	u64 t_n = last_burst;
// 	// tau_n+1 = alpha.t_n + (1 - alpha).tau_n
// 	u64 prediction = alpha * t_n + (1-alpha) * tau_n;
// 	
// 	// now, we have a prediction.
// 	// next order of business: reset the prediction
// 	// TODO: find a way to set the latest burst time. could be by recording the old runtime and new runtime. difference is the last burst. if the thread has changed, then IDK. Then set the new runtime to the old runtime.
// 	last_burst_prediction = prediction;
// }

void shortest_job_first_scheduler::remove_from_runqueue(tcb &tcb)
{
	runqueue.remove(&tcb);
}
tcb *shortest_job_first_scheduler::select_next_task(tcb *current)
{
	if (runqueue_.empty()) {
		return nullptr;
	}
	
	u64 time = 0;
	tcb *thread = nullptr;
	for (auto *thread : runqueue_)
	{
		// if burst time if less, change time to newest burst time, then change thread to this thread ptr
		u64 burst =
	}
}

