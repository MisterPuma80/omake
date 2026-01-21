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

#include "core/object/object.h"
#include "scene/main/node.h"
#include "tests/test_macros.h"
#include "core/math/random_number_generator.h"
//#include <godot_cpp/classes/scene_tree.hpp>

#include "modules/omake/tests/test_omake_helpers.h"
#include "modules/omake/omake.h"

#include <chrono>

namespace TestOmakeFind {

const int GOOD_SEED = 3647666;
const int GOOD_CHILD_COUNT = 34;
const String GOOD_PATH = "da_node_1/da_node_3/da_node_5/da_node_6/da_node_7/da_node_12/da_node_15/da_node_17/da_node_19/da_node_20/da_node_24/da_node_25/da_node_26/da_node_29/da_node_32/da_node_34/da_node_39/da_node_45/da_node_47/da_node_48/da_node_49/da_node_51/da_node_53/da_node_56/da_node_58/da_node_61/da_node_62/da_node_63/da_node_64";

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

TEST_CASE("[OmakeFind] get_children") {
	const int total_child_nodes = 100;
	Node *node = _make_node_tree_flat(total_child_nodes, 42);

	Ref<PackedNodeArray> all = Omake::get_children(node);
	CHECK(all->size() == total_child_nodes);
	CHECK(all->get_node(0)->get_name() == "da_node_12");
	CHECK(all->get_node(1)->get_name() == "da_node_85");

	_delete_node_tree(node);
}

TEST_CASE("[OmakeFind] get_children_by_name") {
	//_find_tree_with_most_direct_children();

	const int total_child_nodes = 100;
	Node *root = _make_node_tree(total_child_nodes, GOOD_SEED);
	//_print_node_tree(root);

	Node *node = root->get_node(NodePath(GOOD_PATH));
	int children_count = node->get_child_count();
	//print_line(vformat("node.name: \"%s\"", node->get_name()));
	CHECK(children_count == GOOD_CHILD_COUNT);

	//Node *first = Object::cast_to<Node>(node->get_children()[0]);
	//print_line(vformat("first.name: \"%s\"", first->get_name()));

	Ref<PackedNodeArray> all = Omake::get_children_by_name(node, "da_node_7?");
	CHECK(all->size() == 10);
	CHECK(all->get_node(0)->get_name() == "da_node_73");
	CHECK(all->get_node(1)->get_name() == "da_node_71");
	CHECK(all->get_node(2)->get_name() == "da_node_72");
	CHECK(all->get_node(3)->get_name() == "da_node_78");

	Ref<PackedNodeArray> none = Omake::get_children_by_name(node, "NotAName");
	CHECK(none->size() == 0);

	_delete_node_tree(root);
}

TEST_CASE("[OmakeFind] get_children_by_group") {
	const int total_child_nodes = 100;
	Node *root = _make_node_tree(total_child_nodes, GOOD_SEED);
	//_print_node_tree(root);

	Node *node = root->get_node(NodePath(GOOD_PATH));
	int children_count = node->get_child_count();
	//print_line(vformat("node.name: \"%s\"", node->get_name()));
	CHECK(children_count == GOOD_CHILD_COUNT);

	//Node *first = Object::cast_to<Node>(node->get_children()[0]);
	//print_line(vformat("first.name: \"%s\"", first->get_name()));

	Ref<PackedNodeArray> all = Omake::get_children_by_group(node, "cat");
	CHECK(all->size() == 11);
	CHECK(all->get_node(0)->get_name() == "da_node_73");
	CHECK(all->get_node(1)->get_name() == "da_node_97");
	CHECK(all->get_node(2)->get_name() == "da_node_67");

	Ref<PackedNodeArray> none = Omake::get_children_by_group(node, "NotAName");
	CHECK(none->size() == 0);

	_delete_node_tree(root);
}

TEST_CASE("[OmakeFind] find_children") {
	const int total_child_nodes = 100;
	Node *node = _make_node_tree(total_child_nodes, GOOD_SEED);

	Ref<PackedNodeArray> all = Omake::find_children(node);
	CHECK(all->size() == total_child_nodes);
	CHECK(all->get_node(0)->get_name() == "da_node_0");
	CHECK(all->get_node(1)->get_name() == "da_node_1");

	_delete_node_tree(node);
}

TEST_CASE("[OmakeFind] find_by_name") {
	const int total_child_nodes = 100;
	Node *node = _make_node_tree(total_child_nodes, GOOD_SEED);

	Ref<PackedNodeArray> all = Omake::find_by_name(node, "da_node_1?");
	CHECK(all->size() == 10);
	CHECK(all->get_node(0)->get_name() == "da_node_12");
	CHECK(all->get_node(1)->get_name() == "da_node_13");

	Ref<PackedNodeArray> none = Omake::find_by_name(node, "NotAName");
	CHECK(none->size() == 0);

	_delete_node_tree(node);
}

TEST_CASE("[OmakeFind] find_by_type") {
	const int total_child_nodes = 100;
	Node *node = _make_node_tree(total_child_nodes, GOOD_SEED);

	Ref<PackedNodeArray> all = Omake::find_by_type(node, "Node");
	CHECK(all->size() == total_child_nodes);
	CHECK(all->get_node(0)->get_name() == "da_node_0");
	CHECK(all->get_node(1)->get_name() == "da_node_1");

	Ref<PackedNodeArray> none = Omake::find_by_type(node, "NotAType");
	CHECK(none->size() == 0);

	_delete_node_tree(node);
}

TEST_CASE("[OmakeFind] find_by_group") {
	const int total_child_nodes = 100;
	Node *node = _make_node_tree(total_child_nodes, GOOD_SEED);
	//_print_node_tree(node);

	Ref<PackedNodeArray> all = Omake::find_by_group(node, "bird");
	CHECK(all->size() == 34);
	CHECK(all->get_node(0)->get_name() == "da_node_0");
	CHECK(all->get_node(1)->get_name() == "da_node_3");

	Ref<PackedNodeArray> none = Omake::find_by_group(node, "NotAGroup");
	CHECK(none->size() == 0);

	_delete_node_tree(node);
}

} // namespace TestOmakeFind
