#include <nbt_utils.h>

struct NBT_TAG*
nbt_find_child_by_name(struct NBT_TAG *root, char *name)
	{
	struct NBT_TAG *child;

	child = root->child;
	while(child) {
		if (!strcmp(child->name, name)) break;
		child = child->sibling;
	}

	return child;
	}

