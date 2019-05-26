#include <nbt.h>
unsigned int position=0;
char* types[] = {
	"TAG_End", "TAG_Byte", "TAG_Short", "TAG_Int", "TAG_Long",
	"TAG_Float", "TAG_Double", "TAG_ByteArray", "TAG_String",
	"TAG_List", "TAG_Compound", "TAG_IntArray", "TAG_LongArray",
	};


short
swap_short(short orig)
	{
	short new;
	new = (orig>>8) + (orig<<8);
	return new;
	}

int
swap_int(int orig)
	{
	unsigned char* porig;
	unsigned char* pdest;
	unsigned int dest;

	pdest = (unsigned char *)&dest;
	porig = (unsigned char *)&orig;

	pdest[0] = porig[3];
	pdest[1] = porig[2];
	pdest[2] = porig[1];
	pdest[3] = porig[0];

	return dest;
	}

long
swap_long(long orig)
	{
	unsigned char* porig;
	unsigned char* pdest;
	unsigned long dest;

	pdest = (unsigned char *)&dest;
	porig = (unsigned char *)&orig;

	pdest[0] = porig[7];
	pdest[1] = porig[6];
	pdest[2] = porig[5];
	pdest[3] = porig[4];
	pdest[4] = porig[3];
	pdest[5] = porig[2];
	pdest[6] = porig[1];
	pdest[7] = porig[0];

	return dest;
	}

void
get_tag_name(void *data, struct NBT_TAG *tag)
	{
	unsigned short name_length=0;
	memcpy(&tag->type, data+position, 1);

	/*If end compound tag don't bother with name*/
	if (tag->type == 0) {position+=1; return;};
	memcpy(&name_length, data+position+1, 2);
	name_length = swap_short(name_length);

	tag->name = 0;

	if (name_length) {
		tag->name = malloc(name_length+1);
		memcpy(tag->name, data+position+3, name_length);
		tag->name[name_length]=0;
		}
	//printf("Tag: %s(%s) \n", tag->name, types[tag->type]);
	position += 1+2+name_length;
	}

void
get_list(void *data, struct NBT_TAG *tag, int level)
	{
	char type = *((char *)(data+position));
	int size = swap_int(*((int *)(data+position+1)));
	position += 5;
	int i;

	for (i=0; i<size; i++) {
		//printf("\nlist[%i/%i]", i, size);
		struct NBT_TAG new_tag = {0};
		new_tag.type = type;
		get_tag(data, &new_tag, tag, level);
		}
	}

void
get_compound(void *data, struct NBT_TAG *root, int level)
	{
	int i;

	while(1) {
		struct NBT_TAG tag = {0};
		//puts("");
		for (i=0;i<level;i++)printf("  ");
		get_tag_name(data, &tag);
		if (tag.type == 0) {
			//puts("");
			break;
		}
		get_tag(data, &tag, root, level);
		}
	}

struct NBT_TAG*
tag_add_child(struct NBT_TAG* parent, struct NBT_TAG* child)
	{
			/* Add child to parent */
			struct NBT_TAG *lchild;
			lchild = malloc(sizeof(struct NBT_TAG));
			memcpy(lchild, child, sizeof(struct NBT_TAG));
			if (!parent->child) {
				parent->child = lchild;
				}
			else {
				lchild->sibling = parent->child;
				parent->child = lchild;
				}

			/* Add parent */
			lchild->parent = parent;
			return lchild;
	}
int
get_tag(void *data, struct NBT_TAG *new_tag, struct NBT_TAG *parent_tag, int level)
	{
	int i;

		if (parent_tag == 0) {
			//printf("ROOT %i\n", new_tag->type);
		} else {
			new_tag = tag_add_child(parent_tag, new_tag);
			}


	switch (new_tag->type) {
		case 0:
			break;
		case 1: /* Byte */
			{
			char byte = *((char *)(data+position));
			new_tag->payload = malloc(1);
			((char*)new_tag->payload)[0] = byte;
			position += 1;
			break;
			}
		case 2: /* Short */
			{
			short s = swap_short(*((short *)(data+position)));
			new_tag->payload = malloc(2);
			((short*)new_tag->payload)[0] = s;
			position += 2;
			break;
			}
		case 3: /* Int */
			{
			int i = swap_int(*((int *)(data+position)));
			new_tag->payload = malloc(4);
			((int*)new_tag->payload)[0] = i;
			position += 4;
			break;
			}
		case 4: /* Long */
			{
			long l = swap_long(*((long *)(data+position)));
			//printf("%li", l);
			new_tag->payload = malloc(8);
			((long*)new_tag->payload)[0] = l;
			position += 8;
			break;
			}
		case 5: /* Float */
			{
			float f = swap_int(*((float *)(data+position)));
			new_tag->payload = malloc(4);
			((float*)new_tag->payload)[0] = f;
			position += 4;
			break;
			}
		case 6: /* Double */
			{
			double d = swap_long(*((double *)(data+position)));
			new_tag->payload = malloc(8);
			((double*)new_tag->payload)[0] = d;
			position += 8;
			break;
			}
		case 7: /* Byte Array*/
			{
			int i;
			int size = swap_int(*((int*)(data+position)));
			new_tag->payload_length = size;
			new_tag->payload = malloc(size);
			memcpy(new_tag->payload, data+position+4, size);
			position += 4+size;
			break;
			}
		case 8: /*String*/
			{
			short size = swap_short(*((short*)(data+position)));
			new_tag->payload = malloc(size+1);
			memcpy(new_tag->payload, data+position+2, size);
			((char*)new_tag->payload)[size]=0;
			position += 2+size;
			break;
			}
		case 9: /*List*/
			get_list(data, new_tag, level);
			break;
		case 10: /*Compound*/
			get_compound(data, new_tag, level);
			break;
		case 11: /* Int Array */
			{
			int i;
			int* ptr;
			int size = swap_int(*((int*)(data+position)));
			new_tag->payload_length = size;
			new_tag->payload = malloc(size*4);
			ptr = new_tag->payload;
			
			for (i=0;i<size;i++) {
				ptr[i] = swap_int(*((int*)(data+position+4+i*4)));
				}
			position += 4+size*4;
			break;
			}
		default:
			printf("Unknown: %s[%i]\n", types[new_tag->type], new_tag->type);
			exit(-1);
			break;
		}

	return 0;
	}
