/* SPDX-License-Identifier: MIT */

/* StACSOS - Kernel
 *
 * Copyright (c) University of St Andrews 2024
 * Tom Spink <tcs6@st-andrews.ac.uk>
 */
#include <stacsos/kernel/sched/alg/rr.h>

// *** COURSEWORK NOTE *** //
// This will be where you are implementing your round-robin scheduling algorithm.
// Please edit this file in any way you see fit.  You may also edit the rr.h
// header file.

using namespace stacsos::kernel::sched;
using namespace stacsos::kernel::sched::alg;

// fwd decl

// this type will later turn into an actual float type. for now, only int
using float_t = size_t;

float_t add(float_t op1, float_t op2);
float_t sub(float_t op1, float_t op2);
float_t mul(float_t op1, float_t op2);
float_t div(float_t op1, float_t op2);

void round_robin::add_to_runqueue(tcb &tcb) { runqueue_.enqueue(&tcb); }

void round_robin::remove_from_runqueue(tcb &tcb) { runqueue_.remove(&tcb); }

tcb *round_robin::select_next_task(tcb *current) { 
    if (runqueue_.empty()) {
        return nullptr;
    }

    if (runqueue_.count() > 1) {
        runqueue_.rotate();
    }

    dprintf("adder: %d", add(1,3));

    return runqueue_.first();
}

// function stubs for later methods
float_t add(float_t op1, float_t op2) {
    return op1+op2;
}
