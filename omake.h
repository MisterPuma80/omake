
#pragma once

#include "core/object/ref_counted.h"

class Omake : public RefCounted {
	GDCLASS(Omake, RefCounted);

protected:
	static void _bind_methods();

public:
	Omake();
	~Omake();

	static int64_t test_func();
};
