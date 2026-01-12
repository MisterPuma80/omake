/**************************************************************************/
/*  test_omake_find.h                                                     */
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

namespace TestOmakeFind {
Node *_make_node_tree_flat(int total_child_nodes) {
	Ref<RandomNumberGenerator> rng = memnew(RandomNumberGenerator);
	rng->set_seed(42);
	Node *root_node = memnew(Node);
	Node *node = root_node;
	for (int i = 0; i < total_child_nodes; i++) {
		Node *new_node = memnew(Node);
		new_node->set_name(vformat("da_node_%d", i));
		new_node->add_to_group("thing");
		node->add_child(new_node);
		int j = rng->randf_range(0, node->get_child_count());
		node->move_child(new_node, j);

		//if (rng->randf() > 0.5) {
		//	node = new_node;
		//}
	}

	return root_node;
}

void _delete_node_tree(Node *root_tree) {
	TypedArray<Node> all = root_tree->find_children("*", "", true, false);

	for (int i = all.size()-1; i >= 0; i--) {
		//print_line(vformat("!!! memdelete i: \"%d\"", i));
		Node *n = Object::cast_to<Node>(all[i]);
		if (n != nullptr) {
			memdelete(n);
			all[i] = Variant(); // FIXME: Isn't there a better way to do Variant null?
		}
	}
	all.clear();
	memdelete(root_tree);
}

TEST_CASE("[OmakeFind] get_groups") {
	Node *node = memnew(Node);
	PackedStringArray groups {"Food", "Enemy", "Weapon"};
	for (String group : groups) {
		node->add_to_group(group);
	}

	PackedStringArray all = Omake::get_groups(node);
	CHECK(all == groups);

	_delete_node_tree(node);
}

} // namespace TestOmakeFind
