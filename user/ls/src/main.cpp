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

			if (*cmdline++ == 'l') {
				flag_long = true;
			} 
			// else if (*cmdline++ == 'a'){
			// 	flag_hidden = true;
			// } 
			else {
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

	object *file = object::open(cmdline);
	if (!file) {
		console::get().writef("error: unable to open file '%s' for ls command\n", cmdline);
		return 1;
	}

	size_t buf_size = 512;

	char* stat_buffer = new char[buf_size];
	auto foo = file->stat(stat_buffer, 0, 4);

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
	}

	delete st_rec;
	delete stat_buffer;
	delete file;
	return 0;
}
