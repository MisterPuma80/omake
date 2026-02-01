/**************************************************************************/
/*  omake_packed_node_array.h                                             */
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

#include "scene/main/node.h"

class PackedNodeArray : public RefCounted {
	GDCLASS(PackedNodeArray, RefCounted);

private:
	mutable LocalVector<Node *> nodes;
	uint32_t current_index;

protected:
	static void _bind_methods();

public:
	PackedNodeArray();
	~PackedNodeArray();

	LocalVector<Node *> *get_node_ptr();
	const Node **ptrw() const;
	Node **ptr();
	void push_back(Node *p_node);
	_FORCE_INLINE_ void append(Node *p_node);
	Node *get_node(int p_index) const;
	void set_node(int p_index, Node *p_node);
	int size() const;
	void resize(int p_new_size);
	void clear();

	Node &operator[](int p_index) {
		return *(nodes[p_index]);
	}

	const Node &operator[](int p_index) const {
		return *(nodes[p_index]);
	}

	Node *front() const;
	Node *back() const;
	Node *pick_random() const;
	int find(Node *p_node, int p_from = 0) const;
	bool has(Node *p_node) const;
	TypedArray<Node> to_array() const;
	bool is_empty() const;

	bool _iter_init(const Variant &p_args);
	bool _iter_next(const Variant &p_args);
	Node *_iter_get(const Variant &p_args);

	struct Iterator {
		_FORCE_INLINE_ Node* &operator*() const { return *elem_ptr; }
		_FORCE_INLINE_ Node* *operator->() const { return elem_ptr; }
		_FORCE_INLINE_ Iterator &operator++() { elem_ptr++; return *this; }
		_FORCE_INLINE_ Iterator &operator--() { elem_ptr--; return *this; }
		_FORCE_INLINE_ bool operator==(const Iterator &b) const { return elem_ptr == b.elem_ptr; }
		_FORCE_INLINE_ bool operator!=(const Iterator &b) const { return elem_ptr != b.elem_ptr; }

		Iterator(Node* *p_ptr) { elem_ptr = p_ptr; }
		Iterator() {}
		Iterator(const Iterator &p_it) { elem_ptr = p_it.elem_ptr; }

	private:
		Node* *elem_ptr = nullptr;
	};

	struct ConstIterator {
		_FORCE_INLINE_ const Node* &operator*() const { return *elem_ptr; }
		_FORCE_INLINE_ const Node* *operator->() const { return elem_ptr; }
		_FORCE_INLINE_ ConstIterator &operator++() { elem_ptr++; return *this; }
		_FORCE_INLINE_ ConstIterator &operator--() { elem_ptr--; return *this; }
		_FORCE_INLINE_ bool operator==(const ConstIterator &b) const { return elem_ptr == b.elem_ptr; }
		_FORCE_INLINE_ bool operator!=(const ConstIterator &b) const { return elem_ptr != b.elem_ptr; }

		ConstIterator(const Node* *p_ptr) { elem_ptr = p_ptr; }
		ConstIterator() {}
		ConstIterator(const ConstIterator &p_it) { elem_ptr = p_it.elem_ptr; }

	private:
		const Node* *elem_ptr = nullptr;
	};

	_FORCE_INLINE_ Iterator begin() { return Iterator(ptr()); }
	_FORCE_INLINE_ Iterator end() { return Iterator(ptr() + size()); }

	_FORCE_INLINE_ ConstIterator begin() const { return ConstIterator(ptrw()); }
	_FORCE_INLINE_ ConstIterator end() const { return ConstIterator(ptrw() + size()); }
};
