
#include "omake.h"
#include "core/object/script_language.h"

#include <cstdint>

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
	ClassDB::bind_static_method("Omake", D_METHOD("test_func"), &Omake::test_func);
}
