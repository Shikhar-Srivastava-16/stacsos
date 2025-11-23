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
		console::get().write("error: usage: ls [-l] [-a] <filename>\n");
		return 1;
	}

	bool flag_hidden = false;
	bool flag_long = false;
	
	while (*cmdline) {
		if (*cmdline == '-') {
			cmdline++;

			if (*cmdline == 'l') {
				console::get().write("foo\n");
				flag_long = true;
				
				if (*(cmdline + 1) == 'a') {
					flag_hidden = true;
				}

			} else if (*cmdline == 'a'){
				console::get().write("foo2\n");
				flag_hidden = true;
			} else {
				console::get().write("error: usage: ls [-l] [-a] <filename>\n");
				return 1;
			}
			

		} else {
			break;
		}
	}

	while (*cmdline == ' ') {
		cmdline++;
	};

	console::get().writef("%u %u\n", flag_hidden, flag_long);

	object *file = object::open(cmdline);
	if (!file) {
		console:get().writef("error: unable to open file '%s' for ls command\n", cmdline);
		return 1;
	}

	size_t buf_size = 48 * 32 + 1;

	char* stat_buffer = new char[buf_size];
	size_t err = file->stat(stat_buffer, 4, 0);

	// console::get().writef("[ %u ]\n", sizeof( statl));		==		48

	statl *st_rec = new statl();
 
	off_t offset = 0;

	while (offset <= buf_size - sizeof(statl) && *(stat_buffer + offset) != '\0') {
		memops::memcpy(st_rec, stat_buffer + offset, sizeof(statl));
		if (!flag_hidden && st_rec->name[0] == '.') {
			offset += sizeof(statl);
			continue; 
		}

		if (flag_long)  {
			char type_marker = st_rec->type == 1 ? 'D' : st_rec->type == 0 ? 'F' : '?';
     		
			if (type_marker == 'D') {
				console::get().writef("[ %c ] %s\n", type_marker, st_rec->name);
			} else {
				console::get().writef("[ %c ] %s    %u\n", type_marker, st_rec->name, st_rec->size);
			}
		} else {
			console::get().writef("%s\n", st_rec->name);
		}
		offset += sizeof(statl);
     
		if (err == 0) {
			console::get().writef("DONE\n");
		}
	}

	delete st_rec;
	delete stat_buffer;
	delete file;
	return 0;
}
