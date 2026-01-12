/**************************************************************************/
/*  test_omake.h                                                          */
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

#pragma once

#include "tests/test_macros.h"
#include "core/math/random_number_generator.h"
//#include <godot_cpp/classes/scene_tree.hpp>

#include "modules/omake/omake.h"

#include <chrono>

namespace TestOmakeMisc {

TEST_CASE("[Omake] test_consts") {
	CHECK(Omake::_INT64_MIN == INT64_MIN);
	CHECK(Omake::_INT64_MAX == INT64_MAX);
}

TEST_CASE("[Omake] test_get_ticks_nsec") {
	uint64_t ticks_a = Omake::get_ticks_nsec();
	uint64_t ticks_b = Omake::get_ticks_nsec();
	CHECK(ticks_a > 0);
	CHECK(ticks_b > 0);
	CHECK(ticks_a < ticks_b);
}

TEST_CASE("[Omake] add_clampedi") {
	CHECK(6 == Omake::add_clampedi(1, 5, 0, 100)); // Normal add
	CHECK(-4 == Omake::add_clampedi(1, -5, -100, 100)); // Normal add
	CHECK(0 == Omake::add_clampedi(6, -900, 0, 100)); // Clamp Underflow
	CHECK(100 == Omake::add_clampedi(6, 900, 0, 100)); // Clamp Overflow

	CHECK(INT64_MAX == Omake::add_clampedi(7, INT64_MAX)); // Clamp Overflow
	CHECK(INT64_MIN == Omake::add_clampedi(-8, INT64_MIN)); // Clamp Underflow
	CHECK(0 == Omake::add_clampedi(0, INT64_MIN, 0, INT64_MAX)); // Clamp Underflow
}

TEST_CASE("[Omake] test_func") {
	CHECK(69 == Omake::test_func());
}

} //namespace TestOmakeMisc


