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

#include "modules/omake/omake.h"

#include <chrono>

namespace TestOmakeFind {

Node *_make_node_tree(int total_child_nodes) {
	Ref<RandomNumberGenerator> rng = memnew(RandomNumberGenerator);
	rng->set_seed(69);
	Node *root_node = memnew(Node);
	Node *node = root_node;
	int k = 0;
	String groups[] { "bird", "cat", "dog" };
	for (int i = 0; i < total_child_nodes; i++) {
		Node *new_node = memnew(Node);
		new_node->set_name(vformat("da_node_%d", i));
		new_node->add_to_group(groups[k]);
		node->add_child(new_node);
		int j = rng->randf_range(0, node->get_child_count());
		node->move_child(new_node, j);

		if (rng->randf() > 0.5) {
			node = new_node;
		}
		k = k < 2 ? k + 1 : 0;
	}

	return root_node;
}

Node *_make_node_tree_flat(int total_child_nodes) {
	Ref<RandomNumberGenerator> rng = memnew(RandomNumberGenerator);
	rng->set_seed(42);
	Node *root_node = memnew(Node);
	Node *node = root_node;
	int k = 0;
	String groups[] { "bird", "cat", "dog" };
	for (int i = 0; i < total_child_nodes; i++) {
		Node *new_node = memnew(Node);
		new_node->set_name(vformat("da_node_%d", i));
		new_node->add_to_group(groups[k]);
		node->add_child(new_node);
		int j = rng->randf_range(0, node->get_child_count());
		node->move_child(new_node, j);
		k = k < 2 ? k + 1 : 0;
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

void _print_node_tree(Node* p_node, int p_level = 0) {
	if (!p_node) return;

	// Add indent
	String indent = "";
	for (int i = 0; i < p_level; i++) {
		indent += "    ";
	}

	// Get node groups
	List<Node::GroupInfo> groups;
	p_node->get_groups(&groups);
	String g = "";
	for (const auto &group : groups) {
		g += group.name;
	}

	// Print node name and groups
	print_line(vformat("%s%s %s", indent, p_node->get_name(), g));

	// Recursively print all children
	for (const auto &entry : p_node->get_children()) {
		Node* child = Object::cast_to<Node>(entry);
		_print_node_tree(child, p_level + 1);
	}
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

TEST_CASE("[OmakeFind] get_children") {
	const int total_child_nodes = 100;
	Node *node = _make_node_tree_flat(total_child_nodes);

	Ref<PackedNodeArray> all = Omake::get_children(node);
	CHECK(all->size() == total_child_nodes);
	CHECK(all->get_node(0)->get_name() == "da_node_12");
	CHECK(all->get_node(1)->get_name() == "da_node_85");

	_delete_node_tree(node);
}

TEST_CASE("[OmakeFind] get_children_by_name") {
	const int total_child_nodes = 100;
	Node *root = _make_node_tree(total_child_nodes);
	//_print_node_tree(root);

	Node *node = root->get_node(NodePath("da_node_0/da_node_1/da_node_2/da_node_3/da_node_4/da_node_6"));
	int children_count = node->get_child_count();
	//print_line(vformat("node.name: \"%s\"", node->get_name()));
	CHECK(children_count == 7);

	//Node *first = Object::cast_to<Node>(node->get_children()[0]);
	//print_line(vformat("first.name: \"%s\"", first->get_name()));

	Ref<PackedNodeArray> all = Omake::get_children_by_name(node, "da_node_1?");
	CHECK(all->size() == 4);
	CHECK(all->get_node(0)->get_name() == "da_node_12");
	CHECK(all->get_node(1)->get_name() == "da_node_10");
	CHECK(all->get_node(2)->get_name() == "da_node_11");
	CHECK(all->get_node(3)->get_name() == "da_node_13");

	Ref<PackedNodeArray> none = Omake::get_children_by_name(node, "NotAName");
	CHECK(none->size() == 0);

	_delete_node_tree(root);
}

TEST_CASE("[OmakeFind] get_children_by_group") {
	const int total_child_nodes = 100;
	Node *root = _make_node_tree(total_child_nodes);
	//_print_node_tree(root);

	Node *node = root->get_node(NodePath("da_node_0/da_node_1/da_node_2/da_node_3/da_node_4/da_node_6"));
	int children_count = node->get_child_count();
	//print_line(vformat("node.name: \"%s\"", node->get_name()));
	CHECK(children_count == 7);

	//Node *first = Object::cast_to<Node>(node->get_children()[0]);
	//print_line(vformat("first.name: \"%s\"", first->get_name()));

	Ref<PackedNodeArray> all = Omake::get_children_by_group(node, "cat");
	CHECK(all->size() == 3);
	CHECK(all->get_node(0)->get_name() == "da_node_10");
	CHECK(all->get_node(1)->get_name() == "da_node_7");
	CHECK(all->get_node(2)->get_name() == "da_node_13");

	Ref<PackedNodeArray> none = Omake::get_children_by_group(node, "NotAName");
	CHECK(none->size() == 0);

	_delete_node_tree(root);
}

TEST_CASE("[OmakeFind] find_all") {
	const int total_child_nodes = 100;
	Node *node = _make_node_tree(total_child_nodes);

	Ref<PackedNodeArray> all = Omake::find_all(node);
	CHECK(all->size() == total_child_nodes);
	CHECK(all->get_node(0)->get_name() == "da_node_0");
	CHECK(all->get_node(1)->get_name() == "da_node_1");

	_delete_node_tree(node);
}

TEST_CASE("[OmakeFind] find_by_name") {
	const int total_child_nodes = 100;
	Node *node = _make_node_tree(total_child_nodes);

	Ref<PackedNodeArray> all = Omake::find_by_name(node, "da_node_1?");
	CHECK(all->size() == 10);
	CHECK(all->get_node(0)->get_name() == "da_node_13");
	CHECK(all->get_node(1)->get_name() == "da_node_11");

	Ref<PackedNodeArray> none = Omake::find_by_name(node, "NotAName");
	CHECK(none->size() == 0);

	_delete_node_tree(node);
}

TEST_CASE("[OmakeFind] find_by_type") {
	const int total_child_nodes = 100;
	Node *node = _make_node_tree(total_child_nodes);

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
	Node *node = _make_node_tree(total_child_nodes);
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
