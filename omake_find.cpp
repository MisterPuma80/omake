/**************************************************************************/
/*  omake_find.cpp                                                        */
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

#include "omake_find.h"
#include "core/object/script_language.h"
#include "scene/main/node.h"

Node *const *OmakeFind::_get_children_ptr(const Node *p_node, int *p_count, bool p_include_internal) {
	*p_count = p_node->get_child_count();
	int offset = p_include_internal ? 0 : p_node->data.internal_children_front_count_cache;
	Node *const *cptr = p_node->data.children_cache.ptr();
	return cptr + offset;
}

Ref<PackedNodeArray> OmakeFind::get_children(const Node *p_node, const bool p_include_internal) {
	//ERR_THREAD_GUARD_V(nullptr); // FIXME

	int cc;
	Node *const *from_ptr = _get_children_ptr(p_node, &cc, p_include_internal);

	Ref<PackedNodeArray> nodes = memnew(PackedNodeArray);
	nodes->resize(cc);
	Node **to_ptr = nodes->get_node_ptr()->ptr();
	for (int i = 0; i < cc; i++) {
		to_ptr[i] = from_ptr[i];
	}
	//memcpy(to_ptr, from_ptr, cc * sizeof(Node *));

	return nodes;
}

Ref<PackedNodeArray> OmakeFind::get_children_by_name(const Node *p_node, const String p_node_name) {
	//ERR_THREAD_GUARD_V(nullptr); // FIXME

	int cc;
	Node *const *from_ptr = _get_children_ptr(p_node, &cc, true);

	Ref<PackedNodeArray> nodes = memnew(PackedNodeArray);
	nodes->resize(cc);
	Node **to_ptr = nodes->get_node_ptr()->ptr();
	int j = 0;
	for (int i = 0; i < cc; i++) {
		if (from_ptr[i]->data.name.operator String().match(p_node_name)) {
			to_ptr[j++] = from_ptr[i];
		}
	}
	nodes->resize(j);

	return nodes;
}

Ref<PackedNodeArray> OmakeFind::get_children_by_group(const Node *p_node, const StringName p_group_name) {
	//ERR_THREAD_GUARD_V(nullptr); // FIXME

	int cc;
	Node *const *from_ptr = _get_children_ptr(p_node, &cc, true);

	Ref<PackedNodeArray> nodes = memnew(PackedNodeArray);
	nodes->resize(cc);
	Node **to_ptr = nodes->get_node_ptr()->ptr();
	int j = 0;
	for (int i = 0; i < cc; i++) {
		if (from_ptr[i]->is_in_group(p_group_name)) {
			to_ptr[j++] = from_ptr[i];
		}
	}
	nodes->resize(j);

	return nodes;
}

Ref<PackedNodeArray> OmakeFind::find_all(const Node *p_node) {
	return OmakeFind::find_by(p_node, "*", "", true, false);
}

Ref<PackedNodeArray> OmakeFind::find_by_name(const Node *p_node, const String &p_node_name) {
	return OmakeFind::find_by(p_node, p_node_name, "", true, false);
}

Ref<PackedNodeArray> OmakeFind::find_by_type(const Node *p_node, const StringName &p_type_name) {
	return OmakeFind::find_by(p_node, "*", p_type_name, true, false);
}

Ref<PackedNodeArray> OmakeFind::find_by_group(const Node *p_node, const StringName &p_group_name) {
	//ERR_THREAD_GUARD_V(TypedArray<Node>()); // FIXME

	LocalVector<Node *> to_search;
	Ref<PackedNodeArray> matches = memnew(PackedNodeArray);
	to_search.push_back((Node *)p_node);
	while (!to_search.is_empty()) {
		Node *entry = to_search[0];
		to_search.remove_at_unordered(0);

		entry->_update_children_cache();
		Node *const *cptr = entry->data.children_cache.ptr();
		const int ccount = entry->data.children_cache.size();
		for (int i = 0; i < ccount; i++) {
			to_search.push_back(cptr[i]);
		}

		if (entry->is_in_group(p_group_name)) {
			matches->push_back(entry);
		}
	}

	return matches;
}

Ref<PackedNodeArray> OmakeFind::find_by_groups(const Node *p_node, const TypedArray<StringName> &p_group_names) {
	//ERR_THREAD_GUARD_V(TypedArray<Node>()); // FIXME

	Ref<PackedNodeArray> matches = memnew(PackedNodeArray);
	LocalVector<Node *> to_search;
	to_search.push_back((Node *)p_node);
	while (!to_search.is_empty()) {
		Node *entry = to_search[0];
		to_search.remove_at_unordered(0);

		entry->_update_children_cache();
		Node *const *cptr = entry->data.children_cache.ptr();
		const int ccount = entry->data.children_cache.size();
		for (int i = 0; i < ccount; i++) {
			to_search.push_back(cptr[i]);
		}

		const int ncount = p_group_names.size();
		for (int i = 0; i < ncount; i++) {
			if (entry->is_in_group(p_group_names[i])) {
				matches->push_back(entry);
			}
		}
	}

	return matches;
}

Ref<PackedNodeArray> OmakeFind::find_by(const Node *p_node, const String &p_pattern, const StringName &p_type, const bool p_recursive, const bool p_owned) {
	//ERR_THREAD_GUARD; // FIXME
	//ERR_FAIL_COND(p_pattern.is_empty() && p_type.is_empty());

	// Save basic pattern and type info for faster lookup
	bool is_pattern_empty = p_pattern.is_empty();
	bool is_type_empty = p_type.is_empty();
	bool is_type_global_class = !is_type_empty && ScriptServer::is_global_class(p_type);
	String type_global_path = is_type_global_class ? ScriptServer::get_global_class_path(p_type) : "";

	LocalVector<Node *> to_search;
	Ref<PackedNodeArray> matches = memnew(PackedNodeArray);
	to_search.push_back((Node *)p_node);
	bool is_adding_children = true;
	while (!to_search.is_empty()) {
		// Pop the next entry off the search stack
		Node *entry = to_search[0];
		to_search.remove_at_unordered(0);

		// Add all the children to the list to search
		entry->_update_children_cache();
		if (is_adding_children) {
			Node *const *cptr = entry->data.children_cache.ptr();
			int ccount = entry->data.children_cache.size();
			for (int i = 0; i < ccount; i++) {
				if (p_owned && !cptr[i]->data.owner) {
					continue;
				}

				to_search.push_back(cptr[i]);
			}

			// Stop further child adding if we don't want recursive
			if (!p_recursive) {
				is_adding_children = false;
			}
		}

		// Check if the entry matches
		bool is_pattern_match = is_pattern_empty || entry->data.name.operator String().match(p_pattern);
		bool is_type_match = is_type_empty || entry->is_class(p_type);
		bool is_script_type_match = false;
		if (!is_type_match) {
			if (ScriptInstance *script_inst = entry->get_script_instance()) {
				Ref<Script> scr = script_inst->get_script();
				while (scr.is_valid()) {
					if ((is_type_global_class && type_global_path == scr->get_path()) || p_type == scr->get_path()) {
						is_script_type_match = true;
						break;
					}

					scr = scr->get_base_script();
				}
			}
		}

		// Save it if it matches the pattern and at least one type
		if (is_pattern_match && (is_type_match || is_script_type_match)) {
			matches->push_back(entry);
		}
	}

	return matches;
}

PackedStringArray OmakeFind::get_groups(const Node *p_node) {
	//ERR_THREAD_GUARD; // FIXME

	PackedStringArray groups;

	const HashMap<StringName, Node::GroupData> node_groups = p_node->data.grouped;
	int gs = node_groups.size();
	groups.resize(gs);
	String* p = groups.ptrw();
	int i = 0;
	for (const KeyValue<StringName, Node::GroupData> &E : node_groups) {
		p[i++] = E.key;
	}

	return groups;
}
