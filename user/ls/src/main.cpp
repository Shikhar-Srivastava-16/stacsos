/* SPDX-License-Identifier: MIT */

/* StACSOS - cat utility, with extremely basic formatting utility.
 *
 * Copyright (c) University of St Andrews 2024, 2025
 * Tom Spink <tcs6@st-andrews.ac.uk>
 */
#include <stacsos/console.h>
#include <stacsos/memops.h>
#include <stacsos/objects.h>
#include <stacsos/statl.h>

using namespace stacsos;

int main(const char *cmdline)
{
	if (!cmdline || memops::strlen(cmdline) == 0) {
		console::get().write("error: usage: ls [-f] <filename>\n");
		return 1;
	}

	object *file = object::open(cmdline);
	if (!file) {
		console::get().writef("error: unable to open file '%s' for ls command\n", cmdline);
		return 1;
	}

	char* stat_buffer = new char[4096];
	auto foo = file->stat(stat_buffer, 0);

	// char* temp = new char[64];
	// statl *st_rec = new statl;

	

	delete file;
	return 0;
}
