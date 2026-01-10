
#include "omake.h"
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

int64_t Omake::test_func() {
	return 69;
}

void Omake::_bind_methods() {
	ClassDB::bind_integer_constant("Omake", "", "INT64_MIN", Omake::_INT64_MIN);
	ClassDB::bind_integer_constant("Omake", "", "INT64_MAX", Omake::_INT64_MAX);

	ClassDB::bind_static_method("Omake", D_METHOD("test_func"), &Omake::test_func);
}
