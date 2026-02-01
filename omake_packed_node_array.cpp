/**************************************************************************/
/*  omake_packed_node_array.cpp                                           */
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

#include "omake_packed_node_array.h"
#include "scene/main/node.h"

PackedNodeArray::PackedNodeArray() {
	//print_line("PackedNodeArray created");
}

PackedNodeArray::~PackedNodeArray() {
	//print_line("PackedNodeArray destroyed");
	nodes.clear();
}

LocalVector<Node *> *PackedNodeArray::get_node_ptr() {
	return &nodes;
}

const Node **PackedNodeArray::ptrw() const {
	return (const Node **) nodes.ptr();
}

Node **PackedNodeArray::ptr() {
	return nodes.ptr();
}

void PackedNodeArray::push_back(Node *p_node) {
	//	fprintf(stderr, "!!!! called PackedNodeArray::append\n"); fflush(stderr);
	nodes.push_back(p_node);
}

void PackedNodeArray::append(Node *p_node) {
	this->push_back(p_node);
}

Node *PackedNodeArray::get_node(int p_index) const {
	//	fprintf(stderr, "!!!! called PackedNodeArray::get_node\n"); fflush(stderr);
	if (p_index >= 0 && p_index < (int)nodes.size()) {
		return nodes[p_index];
	}
	return nullptr;
}

void PackedNodeArray::set_node(int p_index, Node *p_node) {
	nodes[p_index] = p_node;
}

int PackedNodeArray::size() const {
	return (int)nodes.size();
}

void PackedNodeArray::resize(int p_new_size) {
	nodes.resize(p_new_size);
}

void PackedNodeArray::clear() {
	nodes.resize(0);
}

Node *PackedNodeArray::front() const {
	if (nodes.size() == 0) {
		return nullptr;
	}
	return nodes[0];
}

Node *PackedNodeArray::back() const {
	if (nodes.size() == 0) {
		return nullptr;
	}
	int i = nodes.size() - 1;
	return nodes[i];
}

Node *PackedNodeArray::pick_random() const {
	if (nodes.size() == 0) {
		return nullptr;
	}

	int i = Math::rand() % nodes.size();
	return nodes[i];
}

int PackedNodeArray::find(Node *p_node, int p_from) const {
	int ret = -1;

	const int nc = this->size();
	if (p_from < 0 || nc == 0) {
		return ret;
	}

	for (int i = p_from; i < nc; i++) {
		if (this->nodes[i] == p_node) {
			ret = i;
			break;
		}
	}

	return ret;
}

bool PackedNodeArray::has(Node *p_node) const {
	return this->find(p_node) != -1;
}

TypedArray<Node> PackedNodeArray::to_array() const {
	TypedArray<Node> retval;
	int ic = nodes.size();
	retval.resize(ic); // FIXME: retval.resize_uninitialized(ic);
	//Variant* ptr = retval.ptrw(); // FIXME
	for (int i = 0; i < ic; i++) {
		retval[i] = nodes[i];
	}
	return retval;
}

bool PackedNodeArray::is_empty() const {
	return nodes.size() <= 0;
}

bool PackedNodeArray::_iter_init(const Variant &p_args) {
	//fprintf(stderr, "!!!! called PackedNodeArray::_iter_init\n"); fflush(stderr);
	current_index = 0;
	return nodes.size() > 0;
}

bool PackedNodeArray::_iter_next(const Variant &p_args) {
	//fprintf(stderr, "!!!! called PackedNodeArray::_iter_next: %d\n", current_index); fflush(stderr);
	current_index++;
	return current_index < nodes.size();
}

Node *PackedNodeArray::_iter_get(const Variant &p_args) {
	uint32_t idx = current_index;
	//fprintf(stderr, "!!!! called PackedNodeArray::_iter_get: %d\n", idx); fflush(stderr);
	if (idx < nodes.size()) {
		return nodes[idx];
	}
	return nullptr;
}

void PackedNodeArray::_bind_methods() {
	ClassDB::bind_method(D_METHOD("push_back", "node"), &PackedNodeArray::push_back);
	ClassDB::bind_method(D_METHOD("append", "node"), &PackedNodeArray::append);
	ClassDB::bind_method(D_METHOD("get_node", "index"), &PackedNodeArray::get_node);
	ClassDB::bind_method(D_METHOD("set_node", "index", "node"), &PackedNodeArray::set_node);
	ClassDB::bind_method(D_METHOD("size"), &PackedNodeArray::size);
	//ClassDB::bind_method(D_METHOD("clear"), &PackedNodeArray::clear);

	ClassDB::bind_method(D_METHOD("front"), &PackedNodeArray::front);
	ClassDB::bind_method(D_METHOD("back"), &PackedNodeArray::back);
	ClassDB::bind_method(D_METHOD("pick_random"), &PackedNodeArray::pick_random);
	ClassDB::bind_method(D_METHOD("find", "node", "from"), &PackedNodeArray::find);
	ClassDB::bind_method(D_METHOD("has", "node"), &PackedNodeArray::has);
	ClassDB::bind_method(D_METHOD("to_array"), &PackedNodeArray::to_array);
	ClassDB::bind_method(D_METHOD("is_empty"), &PackedNodeArray::is_empty);

	ClassDB::bind_method(D_METHOD("_iter_init", "args"), &PackedNodeArray::_iter_init);
	ClassDB::bind_method(D_METHOD("_iter_next", "args"), &PackedNodeArray::_iter_next);
	ClassDB::bind_method(D_METHOD("_iter_get", "arg"), &PackedNodeArray::_iter_get);
}
