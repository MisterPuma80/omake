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
#include "modules/omake/tests/test_omake_helpers.h"
#include "modules/omake/omake.h"

namespace TestOmakePackedNodeArray {

TEST_CASE("[Omake] PackedNodeArray test_packed_node_array") {
	Node *node = memnew(Node);
	node->set_name("node_a");

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

TEST_CASE("[Omake] PackedNodeArray test_iteration") {
	// Create test nodes
	PackedNodeArray *nodes_ptr = memnew(PackedNodeArray);
	Ref<PackedNodeArray> nodes = nodes_ptr;
	Dictionary all_nodes;
	for (const String &n : { "a", "b", "c" }) {
		Node *node = memnew(Node);
		node->set_name(vformat("node_%s", n));
		all_nodes[node->get_name()] = node;
		nodes->push_back(node);
	}
	PackedNodeArray *ptr_nodes = *nodes;
	const PackedNodeArray& const_ref_nodes = *reinterpret_cast<const PackedNodeArray*>(ptr_nodes);

	// Iteration with get_node
	{
		int count = 0;
		for (int i = 0; i < nodes->size(); i++) {
			Node *node = nodes->get_node(i);
			CHECK(node->get_name().operator String().match("node_*"));
			count++;
		}
		CHECK(count == 3);
	}

	// Iteration with ptr
	{
		Node **ptr = nodes->ptr();
		CHECK(ptr[0]->get_name() == "node_a");
		ptr++;
		CHECK(ptr[0]->get_name() == "node_b");
		ptr++;
		CHECK(ptr[0]->get_name() == "node_c");
	}

	// Iteration with begin and end
	{
		PackedNodeArray::Iterator E = nodes->begin();
		CHECK(*E != nullptr);
		CHECK((*E)->get_name() == "node_a");
		CHECK(E != nodes->end());

		++E;
		CHECK(*E != nullptr);
		CHECK((*E)->get_name() == "node_b");
		CHECK(E != nodes->end());

		++E;
		CHECK(*E != nullptr);
		CHECK((*E)->get_name() == "node_c");
		CHECK(E != nodes->end());

		++E;
		CHECK(*E != nullptr);
		CHECK(E == nodes->end());
	}

	// Iterator
	{
		int count = 0;
		for (PackedNodeArray::Iterator E = nodes->begin(); E != nodes->end(); ++E) {
			Node *node = *E;
			CHECK(node->get_name().operator String().match("node_*"));
			count++;
		}
		CHECK(count == 3);
	}

	// ConstIterator
	{
		int count = 0;
		for (PackedNodeArray::ConstIterator E = const_ref_nodes.begin(); E != const_ref_nodes.end(); ++E) {
			const Node *node = *E;
			CHECK(node->get_name().operator String().match("node_*"));
			count++;
		}
		CHECK(count == 3);
	}

	// Iterate automatically using range begin and end
	{
		int count = 0;
		for (const Node *node : const_ref_nodes) {
			CHECK(node->get_name().operator String().match("node_*"));
			count++;
		}
		CHECK(count == 3);
	}

	// FIXME: Make it automatically work using range begin and end from Ref<PackedNodeArray>
	/*
	{
		int count = 0;
		for (const Node &node : nodes) {
			CHECK(node.get_name().operator String().match("node_*"));
			count++;
		}
		CHECK(count == 3);
	}
	*/

	// Cleanup nodes
	for (const auto &entry : all_nodes) {
		Node *node = Object::cast_to<Node>(entry.value);
		_delete_node_tree(node);
	}
}

} //namespace TestOmakePackedNodeArray


