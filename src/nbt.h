#ifndef NBT_H
#define NBT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char* types[];

struct NBT_TAG {
	unsigned char type;
	char *name;
	void* payload;
	unsigned int payload_length;
	struct NBT_TAG *parent;
	struct NBT_TAG *child;
	struct NBT_TAG *sibling;
	};

short swap_short(short orig);
int swap_int(int orig);
long swap_long(long orig);
void get_tag_name(void *data, struct NBT_TAG *tag);
void get_list(void *data, struct NBT_TAG *tag, int level);
void get_compound(void *data, struct NBT_TAG *root, int level);
int get_tag(void *data, struct NBT_TAG *new_tag, struct NBT_TAG *parent_tag, int level);


#endif /* NBT_H */
