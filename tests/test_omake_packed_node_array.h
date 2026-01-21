/**************************************************************************/
/*  test_omake_packed_node_array.h                                        */
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
#include "core/variant/variant_utility.h"
#include "modules/omake/omake.h"

namespace TestOmakePackedNodeArray {

void _delete_node_tree(Node *root_tree) {
	if (root_tree == nullptr || !VariantUtilityFunctions::is_instance_valid(root_tree)) return;

	TypedArray<Node> all = root_tree->find_children("*", "", true, true);

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

TEST_CASE("[Omake] test_packed_node_array") {
	Node *node = memnew(Node);

	// Check is empty
	Ref<PackedNodeArray> nodes = memnew(PackedNodeArray);
	CHECK(nodes->size() == 0);
	CHECK(nodes->is_empty() == true);
	CHECK(nodes->has(node) == false);
	CHECK(nodes->front() == nullptr);
	CHECK(nodes->back() == nullptr);
	CHECK(nodes->get_node(0) == nullptr);
	CHECK(nodes->pick_random() == nullptr);

	// Check has 1
	node->set_name("a_node");
	nodes->push_back(node);
	CHECK(nodes->size() == 1);
	CHECK(nodes->is_empty() == false);
	CHECK(nodes->has(node) == true);
	CHECK(nodes->front() == node);
	CHECK(nodes->back() == node);
	CHECK(nodes->get_node(0) == node);
	CHECK(nodes->pick_random() == node);

	// Check empty after removed
	nodes->clear();
	CHECK(nodes->size() == 0);
	CHECK(nodes->is_empty() == true);
	CHECK(nodes->has(node) == false);
	CHECK(nodes->front() == nullptr);
	CHECK(nodes->back() == nullptr);
	CHECK(nodes->get_node(0) == nullptr);
	CHECK(nodes->pick_random() == nullptr);

	_delete_node_tree(node);
}

} //namespace TestOmakePackedNodeArray


