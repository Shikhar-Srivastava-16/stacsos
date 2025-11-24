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

int stat_res(size_t ents, off_t offset, bool flag_hidden, bool flag_long, object *file);

int main(const char *cmdline)
{
	if (!cmdline || memops::strlen(cmdline) == 0) {
		console::get().write("error: usage: ls [-l] [-a] <filename>\n");
		return 1;
	}

	// flags for the errors
	bool flag_hidden = false;
	bool flag_long = false;
	
	// while loop for very primitive parsing
	// ideally, this would have a parser like clap but stacsos doesn't have one
	while (*cmdline) {
		if (*cmdline == '-') {
			cmdline++;

			if (*cmdline == 'l') {
				flag_long = true;
				
				if (*(cmdline + 1) == 'a') {
					flag_hidden = true;
					cmdline++;
				}
				cmdline++;
				while (*cmdline && *cmdline != ' ') {
					if (*cmdline == 'a') {
						flag_hidden = true;
					} else if (*cmdline == 'l') {
						flag_long = true;
					} else {
						console::get().write("error: usage: ls [-l] [-a] <filename>\n");
						return 1;
					}
					cmdline++;
				}
				while (*cmdline == ' ') {
					cmdline++;
				}
			} else if (*cmdline == 'a'){
				flag_hidden = true;
				cmdline++;
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

	object *file = object::open(cmdline);
	if (!file) {
		console::get().writef("error: unable to open file '%s' for ls command\n", cmdline);
		return 1;
	}

	off_t stat_offset = 0;
	// get only 8 entries at a time
	// this setup of stacsos is low on memory
	// it doesn't really work anyway, because freeing has not been implemented
	size_t ents = 8;
	size_t err = stat_res(ents, stat_offset, flag_hidden, flag_long, file);

	if (err == 3) {
		console::get().writef("%s is not a directory.\n", cmdline);
		// returning 0 because this is still expected behaviour. If this were allowed to go on, it would cause a segfault later on
		return 0;
	}

	while (err != 0) {
		stat_offset += ents;
		err = stat_res(ents, stat_offset, flag_hidden, flag_long, file);
	}

	return 0;
}

int stat_res(size_t ents, off_t stat_offset, bool flag_hidden, bool flag_long, object *file) {

	size_t buf_size = sizeof(statl) * ents + 1;

	char* stat_buffer = new char[buf_size];
	size_t exit_code = file->dirents(stat_buffer, buf_size, stat_offset);

	statl *st_rec = new statl();
 
	off_t offset = 0;

	while (offset <= buf_size - sizeof(statl) && *(stat_buffer + offset) != '\0') {
		// use offset here instead of incrementing the starting ptr because we want to be able to delete the initial buffer, which was dynamically allocated
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
	return exit_code;
}