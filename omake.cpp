/**************************************************************************/
/*  oamke.cpp                                                             */
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

#include "omake.h"

#include "core/object/script_language.h"

#include "omake_find.h"
#include "omake_get_ticks_nsec.h"
#include "omake_packed_node_array.h"
#include <cstdint>

Omake::Omake() {
	//print_line("Omake created");
}

Omake::~Omake() {
	//print_line("Omake destroyed");
}

uint64_t Omake::get_ticks_nsec() {
	return omake_get_ticks_nsec();
}

Ref<PackedNodeArray> Omake::get_children(const Node *p_node, const bool p_include_internal) {
	return OmakeFind::get_children(p_node, p_include_internal);
}

Ref<PackedNodeArray> Omake::get_children_by_name(const Node *p_node, const String p_node_name) {
	return OmakeFind::get_children_by_name(p_node, p_node_name);
}

Ref<PackedNodeArray> Omake::get_children_by_group(const Node *p_node, const StringName p_group_name) {
	return OmakeFind::get_children_by_group(p_node, p_group_name);
}

Ref<PackedNodeArray> Omake::find_all(const Node *p_node) {
	return OmakeFind::find_all(p_node);
}

Ref<PackedNodeArray> Omake::find_by_name(const Node *p_node, const String &p_node_name) {
	return OmakeFind::find_by_name(p_node, p_node_name);
}

Ref<PackedNodeArray> Omake::find_by_type(const Node *p_node, const StringName &p_type_name) {
	return OmakeFind::find_by_type(p_node, p_type_name);
}

Ref<PackedNodeArray> Omake::find_by_group(const Node *p_node, const StringName &p_group_name) {
	return OmakeFind::find_by_group(p_node, p_group_name);
}

Ref<PackedNodeArray> Omake::find_by_groups(const Node *p_node, const TypedArray<StringName> &p_group_names) {
	return OmakeFind::find_by_groups(p_node, p_group_names);
}

Ref<PackedNodeArray> Omake::find_by(const Node *p_node, const String &p_pattern, const StringName &p_type, const bool p_recursive, const bool p_owned) {
	return OmakeFind::find_by(p_node, p_pattern, p_type, p_recursive, p_owned);
}

PackedStringArray Omake::get_groups(const Node *p_node) {
	return OmakeFind::get_groups(p_node);
}

void Omake::_bind_methods() {
	ClassDB::bind_static_method("Omake", D_METHOD("get_ticks_nsec"), &Omake::get_ticks_nsec);

	ClassDB::bind_static_method("Omake", D_METHOD("get_children", "node", "include_internal"), &Omake::get_children, DEFVAL(true));
	ClassDB::bind_static_method("Omake", D_METHOD("get_children_by_name", "node", "node_name"), &Omake::get_children_by_name);
	ClassDB::bind_static_method("Omake", D_METHOD("get_children_by_group", "node", "group_name"), &Omake::get_children_by_group);

	ClassDB::bind_static_method("Omake", D_METHOD("find_all", "node"), &Omake::find_all);
	ClassDB::bind_static_method("Omake", D_METHOD("find_by", "node", "pattern", "type", "recursive", "owned"), &Omake::find_by, DEFVAL(""), DEFVAL(true), DEFVAL(true));
	ClassDB::bind_static_method("Omake", D_METHOD("find_by_name", "node", "node_name"), &Omake::find_by_name);
	ClassDB::bind_static_method("Omake", D_METHOD("find_by_type", "node", "type_name"), &Omake::find_by_type);
	ClassDB::bind_static_method("Omake", D_METHOD("find_by_group", "node", "group_name"), &Omake::find_by_group);
	ClassDB::bind_static_method("Omake", D_METHOD("find_by_groups", "node", "group_names"), &Omake::find_by_groups);

	ClassDB::bind_static_method("Omake", D_METHOD("get_groups", "node"), &Omake::get_groups);
}
