
#pragma once

#include "tests/test_macros.h"

#include "modules/omake/omake.h"

namespace TestOmakeMisc {

TEST_CASE("[Omake] test_consts") {
	CHECK(Omake::_INT64_MIN == INT64_MIN);
	CHECK(Omake::_INT64_MAX == INT64_MAX);
}

TEST_CASE("[Omake] test_func") {
	CHECK(69 == Omake::test_func());
}

} //namespace TestOmakeMisc
