# Omake

Omake is a [Blazium](https://github.com/blazium-games/blazium) module with faster C++ scene tree functions. Works with Blazium 4.3 through 4.5.

# Benchmarks

![Alt text](https://raw.githubusercontent.com/MisterPuma80/omake/refs/heads/master/static/blazium_omake_2026_01_20.png "Benchmark results")

# Install

```bash
git clone -b blazium-4.5 https://github.com/blazium-games/blazium
cd blazium
git clone https://github.com/MisterPuma80/omake modules/omake
./modules/omake/install_module_hooks.sh
```

# Example

```GDScript
func _ready() -> void:
	# Find all the Node3D in the scene
	var nodes := Omake.find_children_by_type(self, "Node3D")
	for node in nodes:
		print(node)

func _ready() -> void:
	# Add some nodes to the array
	var nodes := PackedNodeArray.new()
	nodes.append($Level/Player)
	nodes.append($Level/Enemy)
	nodes.append($Level/PowerUp)

	for node in nodes:
		print(node)
```

# API

```C++
static Ref<PackedNodeArray> get_children(const Node *p_node, const bool p_include_internal = true);
static Ref<PackedNodeArray> get_children_by_name(const Node *p_node, const String &p_pattern);
static Ref<PackedNodeArray> get_children_by_group(const Node *p_node, const StringName &p_group_name);

static Ref<PackedNodeArray> find_children(const Node *p_node);
static Ref<PackedNodeArray> find_children_by(const Node *p_node, const String &p_pattern, const StringName &p_type, const bool p_recursive = true, const bool p_owned = true);
static Ref<PackedNodeArray> find_children_by_name(const Node *p_node, const String &p_pattern);
static Ref<PackedNodeArray> find_children_by_type(const Node *p_node, const StringName &p_type_name);
static Ref<PackedNodeArray> find_children_by_group(const Node *p_node, const StringName &p_group_name);
static Ref<PackedNodeArray> find_children_by_groups(const Node *p_node, const TypedArray<StringName> &p_group_names);

static PackedStringArray get_groups(const Node *p_node);
```