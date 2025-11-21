/* SPDX-License-Identifier: MIT */

/* StACSOS - Utility Library
 *
 * Copyright (c) University of St Andrews 2024
 * Tom Spink <tcs6@st-andrews.ac.uk>
 */
#pragma once

#include <stacsos/helpers.h>

namespace stacsos {
class statl {
public:
	// file name
	char name[32];
	// file type (1 = file, 0 = dir)
	size_t type;
	// file size
	size_t size;

	statl()
		: name("")
		, type(0)
		, size(0)
	{
	}
};
} // namespace stacsos
