
#pragma once

#include "tests/test_macros.h"

#include "modules/omake/omake.h"

namespace TestOmakeMisc {

TEST_CASE("[Omake] test_func") {
	CHECK(69 == Omake::test_func());
}

} //namespace TestOmakeMisc
