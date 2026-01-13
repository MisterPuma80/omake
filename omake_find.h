/**************************************************************************/
/*  omake_find.h                                                          */
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

#include "core/object/ref_counted.h"
#include "core/variant/typed_array.h"

#include "modules/omake/omake_packed_node_array.h"

class Node;

class OmakeFind {
private:
	static Node *const *_get_children_ptr(const Node *p_node, int *p_count, bool p_include_internal = false);

public:
	static Ref<PackedNodeArray> get_children(const Node *p_node, const bool p_include_internal = true);

	static Ref<PackedNodeArray> find_all(const Node *p_node);
	static Ref<PackedNodeArray> find_by(const Node *p_node, const String &p_pattern, const String &p_type, const bool p_recursive = true, const bool p_owned = true);
	static Ref<PackedNodeArray> find_by_name(const Node *p_node, const String &p_node_name);
	static Ref<PackedNodeArray> find_by_type(const Node *p_node, const String &p_type_name);
	static Ref<PackedNodeArray> find_by_group(const Node *p_node, const String &p_group_name);
	static Ref<PackedNodeArray> find_by_groups(const Node *p_node, const TypedArray<String> &p_group_names);

	static PackedStringArray get_groups(const Node *p_node);
};
