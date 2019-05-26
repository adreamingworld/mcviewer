#ifndef NBT_UTILS_H
#define NBT_UTILS_H

#include <nbt.h>

struct NBT_TAG* nbt_find_child_by_name(struct NBT_TAG *root, char *name);

#endif /* NBT_UTILS_H */
