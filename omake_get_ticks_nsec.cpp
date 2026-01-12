/**************************************************************************/
/*  omake_get_ticks_nsec.cpp                                          */
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

#include "omake_get_ticks_nsec.h"
#include <chrono>
#include <cstdint>

void omake_init_get_ticks_nsec() {
    _start_time = omake_get_ticks_nsec();
}

uint64_t omake_get_ticks_nsec() {
	auto now = std::chrono::high_resolution_clock::now();
	auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();
	return static_cast<uint64_t>(ns) - _start_time;
}
