/* SPDX-License-Identifier: MIT */

/* StACSOS - Utility Library
 *
 */
#pragma once

#include <stacsos/helpers.h>

namespace stacsos {
class statl {
public:
	// file name
	char name[32];
	// file type (1 = file, 0 = dir, others treated as unknown)
	size_t type;
	// file size
	size_t size;

	// constructor
	statl()
		: name("")
		, type(0)
		, size(0)
	{
	}
};
} // namespace stacsos
