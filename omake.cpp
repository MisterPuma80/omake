/**************************************************************************/
/*  oamke.cpp                                                             */
/**************************************************************************/
/*                         This file is part of:                          */
/*                                  Omake                                 */
/*                  https://github.com/MisterPuma80/omake                 */
/**************************************************************************/
/* Copyright (c) 2018-2026 MisterPuma80 <MisterPuma80@gmail.com>          */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#include "omake.h"
#include "omake_get_cpu_ticks_nsec.h"

#include "core/object/script_language.h"

#include <cstdint>

const int64_t Omake::_INT64_MIN = INT64_MIN;
const int64_t Omake::_INT64_MAX = INT64_MAX;

Omake::Omake() {
	//print_line("Omake created");
}

Omake::~Omake() {
	//print_line("Omake destroyed");
}

uint64_t Omake::get_cpu_ticks_nsec() {
	return omake_get_cpu_ticks_nsec();
}

int64_t Omake::add_clampedi(int64_t a, int64_t b, int64_t min, int64_t max) {
	// Will overflow so just return max
	if (b > 0 && a > max - b) {
		return max;
	}

	// Will underflow so just return min
	if (b < 0 && a < min - b) {
		return min;
	}

	return CLAMP(a + b, min, max);
}

int64_t Omake::test_func() {
	return 69;
}

void Omake::_bind_methods() {
	ClassDB::bind_integer_constant("Omake", "", "INT64_MIN", Omake::_INT64_MIN);
	ClassDB::bind_integer_constant("Omake", "", "INT64_MAX", Omake::_INT64_MAX);

	ClassDB::bind_static_method("Omake", D_METHOD("get_cpu_ticks_nsec"), &Omake::get_cpu_ticks_nsec);
	ClassDB::bind_static_method("Omake", D_METHOD("add_clampedi", "a", "b", "min", "max"), &Omake::add_clampedi, DEFVAL(Omake::_INT64_MIN), DEFVAL(Omake::_INT64_MAX));
	ClassDB::bind_static_method("Omake", D_METHOD("test_func"), &Omake::test_func);
}
