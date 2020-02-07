#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <myz.h>
#include <nbt.h>
#include <nbt_utils.h>
#include <shader.h>
#include <math3d.h>

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>


unsigned int vao, vbo, vbo2;
unsigned int model_view_matrix_location;
unsigned int theta_location;
/* Enumerate? */
#define FACE_TOP	0
#define FACE_BOTTOM	1
#define FACE_LEFT	2
#define FACE_RIGHT	3
#define FACE_FRONT	4
#define FACE_BACK	5

#define BLOCK_SIZE 16
#define SPEED 2
int lighting_enabled = 1;
int textures_enabled = 1;

/* scenic spot
xyz:105.821602 78.412117 135.580490 - rot:38.000000 -3.750000 0.000000
xyz: 49.916008 125.423233 80.084755 - rot:47.000000 113.250000 0.000000
56.604927, 102.036270, 95.271812, 36.750000, 143.750000, 0.000000
*/
struct position {
	float x,y,z;
	float rx,ry,rz;
	};

struct position photo_position ={
56.604927, 102.036270, 95.271812, 36.750000, 143.750000, 0.000000
};

void
set_position(struct position* original, struct position* destination)
	{
	original->x = destination->x;
	original->y = destination->y;
	original->z = destination->z;
	original->rx = (destination->rx/180.0)*M_PI;
	original->ry = (destination->ry/180.0)*M_PI;
	original->rz = (destination->rz/180.0)*M_PI;
	}
/*
	transparent [doesnt affect AO] below above left right front back
*/
unsigned char faces[256][8] = {
		{0,0,0,0,0,0,0,0},
		{0,0,1,1,1,1,1,1}, /*stone*/
		{0,0,3,2,4,4,4,4}, /*grass*/
		{0,0,2,2,2,2,2,2}, /*dirt*/
		{0,0,20,20,20,20,20,20}, /*cobble*/
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,8,8,8,8,8,8}, /* flowing water*/
		{0,0,8,8,8,8,8,8}, /*water*/
		{0,0,13,13,13,13,13,13}, /*flowing lava*/
		{0,0,13,13,13,13,13,13}, /*lava*/
		{0,0,9,9,9,9,9,9}, /*sand*/
		{0,0,12,12,12,12,12,12}, /*gravel*/
		{0,0,17,17,17,17,17,17}, /* Gold*/
		{0,0,16,16,16,16,16,16}, /*Iron ore*/
		{0,0,15,15,15,15,15,15}, /*Coal ore*/
		{0,0,7,7,6,6,6,6}, /* log */
		{1,0,5,5,5,5,5,5}, /* leaves*/
		{0,0,0,0,0,0,0,0}, 
		{0,0,0,0,0,0,0,0},
		{0,0,28,28,28,28,28,28}, /*Lapis???*/
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{1,1,64,0,11,11,11,11}, /*Tall Grass*/
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,21,21,21,21,21,21}, /*Mossy cobble*/
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,28,28,28,28,28,28}, /*Mob spawner*/
		{0,0,0,0,0,0,0,0},
		{0,0,22,23,24,25,26,27}, /*Chest*/
		{0,0,0,0,0,0,0,0},
		{0,0,19,19,19,19,19,19}, /*Diamond*/
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,18,18,18,18,18,18}, /*Red stone*/
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,10,10,10,10,10,10}, /*Snow layer*/
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{1,0,64,64,30,30,30,30},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,29,29,29,29,29,29,}, /*Quartz block*/
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{1,0,64,64,14,14,14,14}, /*Tall plant*/
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		};

struct vertex {
	float x,y,z;
	float nx,ny,nz;
	float u,v;
	float r,g,b;
	};

struct geometry {
	struct vertex *verts;
	unsigned int capacity;
	unsigned int count;
	unsigned int vbo;
	};

/* Verts for a cube - used as a reference to build blocks from*/
float cube_verts[] = {
	BLOCK_SIZE*0,		BLOCK_SIZE*1,		BLOCK_SIZE*1,
	BLOCK_SIZE*1,		BLOCK_SIZE*1,		BLOCK_SIZE*1,
	BLOCK_SIZE*1,		BLOCK_SIZE*0,		BLOCK_SIZE*1,
	BLOCK_SIZE*0,		BLOCK_SIZE*0,		BLOCK_SIZE*1,
	/* back */
	BLOCK_SIZE*0,  		BLOCK_SIZE*1,  		BLOCK_SIZE*0,
	BLOCK_SIZE*1,   	BLOCK_SIZE*1,  		BLOCK_SIZE*0,
	BLOCK_SIZE*1,  		BLOCK_SIZE*0,  		BLOCK_SIZE*0,
	BLOCK_SIZE*0, 		BLOCK_SIZE*0,  		BLOCK_SIZE*0,
	};
/**
Vertex indices noted on a 3d representation.
(+Y)		0----------1
  |		|\        /|
  |   (-Z)	| 4------5 |
  |   /		| |      | |
  |  /		| |      | |
  | /		| 7------6 |
  |/		|/        \|
  +--------(+X)	3----------2

*/

char face_ints[6][6] = {
		{4,0,1, 4,1,5}, /*Top*/
		{3,7,6, 3,6,2}, /*Bottom*/
		{4,7,3, 4,3,0},
		{1,2,6, 1,6,5},
		{0,3,2, 0,2,1},
		{5,6,7, 5,7,4}
		};

/* 16 vertically stacked sections*/
struct chunk {
	unsigned char x;
	unsigned char z;
	unsigned char sections[16][16*16*16];
	};

/* 32*32 chunks */
struct region {
	struct chunk *chunks[32*32];
	};

void
geometry_init(struct geometry* g)
	{
	g->capacity = 1;
	g->count = 0;
	g->verts = malloc(sizeof(struct vertex));
	}
void
geometry_expand(struct geometry* g)
	{
	//printf("expanding %i\n", g->capacity);
	g->capacity *= 2;
	g->verts = realloc(g->verts, sizeof(struct vertex)*g->capacity);
	//printf("expanded %i\n", g->capacity);
	}
void
geometry_add(struct geometry* g, struct vertex* v)
	{
	int top = g->count;
	/*space left?*/
	if (g->capacity == g->count) geometry_expand(g);
	memcpy(&g->verts[top], v, sizeof(struct vertex));
	g->count++;
	}

void
vertex_print(struct vertex* v)
	{
	printf("%f %f %f\n", v->x, v->y, v->z);
	}
void
geometry_print(struct geometry* g)
	{
	int i;
	for (i=0;i<g->count;i++)
		vertex_print(&g->verts[i]);
	}

void
load_chunk(FILE *fp, struct chunk *chunk)
	{	
	unsigned int length;
	unsigned char* data;
	void* nbt_data;
	unsigned char compression_type;

	fread(&length, 4, 1, fp);
	fread(&compression_type, 1, 1, fp);
	length = swap_int(length);
	data = malloc(length);
	fread(data, length, 1, fp);
//	printf("compressed size = %u\n", length);
//	printf("compression type = %i\n", compression_type);

	nbt_data = malloc(1000000);

	unsigned int nbt_data_size;
	nbt_data_size = inf(data, &nbt_data, length);

	nbt_data = realloc(nbt_data, nbt_data_size);

	struct NBT_TAG root={0};

	get_tag_name(nbt_data, &root);
	get_tag(nbt_data, &root, 0, 0);

	/*Get block data from sections*/
	struct NBT_TAG* section;
	section = nbt_find_child_by_name(&root, "Level");
	section = nbt_find_child_by_name(section, "Sections");
	section = section->child;

	/*Go through each section*/
	while(section) {
		struct NBT_TAG* blocks;
		struct NBT_TAG* y_tag;
		int y;

		blocks = nbt_find_child_by_name(section, "Blocks");
		y_tag = nbt_find_child_by_name(section, "Y");
		y = *((char*)y_tag->payload);
		if (!blocks) puts("Failed to get blocks");
		if (y>15 || y<0) {puts("Y for chunk out of bounds"); exit(-1);}

		memcpy(chunk->sections[y], blocks->payload, 16*16*16);
		section = section->sibling;
	}

	free(nbt_data);
	}

unsigned char
get_id(struct region* r, float x, float y, float z)
	{
	unsigned char id=12;
	int chunkx = x/16;
	int chunkz = z/16;
	int blockx = (int)x%16;
	int blockz = (int)z%16;
	int blocky = (int)y%16;
	int isection = y/16;
	struct chunk* chunk=0;

	if (x<0) return 0;
	if (y<0) return 0;
	if (z<0) return 0;
if (chunkx>31 || chunkz>31) return 0;
	/*Get chunk*/
	chunk = r->chunks[chunkx+chunkz*32];
	if (!chunk) return 0;
	id = chunk->sections[isection][blockx + (blockz*16) + (blocky*(16*16))];


	return id;
	}

void
build_top(struct region* r, float x, float y, float z, int face_ind, float nx, float ny, float nz, struct geometry *g, char id)
	{
	int i;
	int uindex[] = {0,0,1, 0,1,1};
	int vindex[] = {0,1,1, 0,1,0};
	float tu = (1.0/64);
	
	float fx,fy,fz;
	fx = x/BLOCK_SIZE;
	fy = y/BLOCK_SIZE;
	fz = z/BLOCK_SIZE;

	for (i=0; i<6; i++) {
		float light=0;
		struct vertex v;
		unsigned char side1, side2, corner;
		
		/* Generate cube mesh */
		v.x = cube_verts[face_ints[face_ind][i]*3 + 0] + x;
		v.y = cube_verts[face_ints[face_ind][i]*3 + 1] + y;
		v.z = cube_verts[face_ints[face_ind][i]*3 + 2] + z;
		v.nx = nx;
		v.ny = ny;
		v.nz = nz;
		v.u = (tu * (id%64)) + (tu*uindex[i]);
		v.v = (tu * (id/64)) + (tu*vindex[i]);

		/*Generate lighting*/
		int icorner[3]={0};
		int iside1[3]={0};
		int iside2[3]={0};
		
		/*Get corner according to the position of the vertex
		being calculated
		*/
		icorner[0] = iside1[0] = iside2[0] = (v.x - x)==0 ? -1 : 1;
		icorner[1] = iside1[1] = iside2[1] = (v.y - y)==0 ? -1 : 1;
		icorner[2] = iside1[2] = iside2[2] = (v.z - z)==0 ? -1 : 1;

		if (face_ind == FACE_TOP || face_ind==FACE_BOTTOM) {
			iside1[0] = 0;
			iside2[2] = 0;
		}
		if (face_ind == FACE_LEFT || face_ind==FACE_RIGHT) {
			iside1[1] = 0;
			iside2[2] = 0;
		}
		if (face_ind==FACE_FRONT || face_ind==FACE_BACK) {
			iside1[0] = 0;
			iside2[1] = 0;
		}
		side1 = get_id(r, fx+iside1[0],fy+iside1[1],fz+iside1[2]);
		side2 = get_id(r, fx+iside2[0],fy+iside2[1],fz+iside2[2]);
		corner = get_id(r, fx+icorner[0],fy+icorner[1],fz+icorner[2]);

		/* Not air and not not effect Ambient Occlusion*/
		side1 = (side1 && !faces[side1][1]) ? 1:0;
		side2 = (side2 && !faces[side2][1]) ? 1:0;
		corner = (corner && !faces[corner][1]) ? 1:0;

		if (side1 && side2) light = 0;
		else light = 3-(side1+side2+corner);
		#define CONTRAST 0.8
		light = (1.0-CONTRAST) + light/(3.0/CONTRAST);

		/* get 2 sides and corner block for lighting */
		v.r = v.g = v.b = light;

		geometry_add(g, &v);
		}
	}



SDL_Window *window;

float verts[] = {
	0,0, -1,
	0,-1,-1,
	1,0, -1,
	};

float verts2[] = {
	1,0, -1,
	0,-1,-1,
	1,-1, -1,
	};

void
setup_sdl(char* title, int w, int h, int x, int y)
	{
	SDL_GLContext *context;

	SDL_Init(SDL_INIT_VIDEO);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	window = SDL_CreateWindow(title, x,y, w, h, SDL_WINDOW_OPENGL|SDL_WINDOW_BORDERLESS|SDL_WINDOW_MOUSE_CAPTURE);
	context = SDL_GL_CreateContext(window);
	puts((const char*)glGetString(GL_VERSION));

	if (!context) puts("Failed context");
	glewInit();
	/*VAO*/
	glCreateVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0,0,1,0);

	struct shader shaders[2];
	shaders[0].type = GL_VERTEX_SHADER;
	shader_source_from_file(&shaders[0], "resources/shader.vert");
	shaders[1].type = GL_FRAGMENT_SHADER;
	shader_source_from_file(&shaders[1], "resources/shader.frag");

	unsigned int program = shader_create_program(2, shaders);

	model_view_matrix_location = glGetUniformLocation(program, "ModelViewProjectionMatrix");
	printf("mvp location = %i\n", model_view_matrix_location);
	theta_location = glGetUniformLocation(program, "theta");
	printf("theta location = %i\n", theta_location);

	}

/*Set a block in the region
	return the chunk index;
*/
unsigned int
set_id(struct region* r, int bx,int by,int bz, unsigned char id)
	{
	int chunkx = bx/16;
	int chunkz = bz/16;
	int blockx = (int)bx%16;
	int blockz = (int)bz%16;
	int blocky = (int)by%16;
	int isection = by/16;
	struct chunk* chunk=0;

	/*Get chunk*/
	chunk = r->chunks[chunkx+chunkz*32];
	if (!chunk) return 0;
	chunk->sections[isection][blockx + (blockz*16) + (blocky*(16*16))] = id;
	return chunkx+chunkz*32;
	}


unsigned int
geometry_to_vbo(struct geometry* g)
	{
	unsigned int vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(struct vertex)*g->count, g->verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(struct vertex), (const void*) (6*sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(struct vertex), (const void*) (8*sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	/*Set default texture color rgb as 1,1,1 white*/
	glVertexAttrib2f(1, (16.0/1024)*10,0);
	/*Set default color rgb as 1,1,1 white*/
	glVertexAttrib3f(2, 1,1,1);

	glBindAttribLocation(1, 0, "in_Position");
	glBindAttribLocation(1, 1, "in_TexCoord");
	glBindAttribLocation(1, 2, "in_Color");
g->vbo = vbo;
	return vbo;
	}

/*
We don't really need the square root to get the length?
As long as unit vectors?
we want the angle, not the actual length
so the proportion is important not the exact length?
*/
/* returns cos(theta) not theta*/
float
angle_between3(float v1[3], float v2[3])
	{
	/*ANGLE BETWEEN TWO VECTORS*/
	float len1 = v1[0]*v1[0] + v1[1]*v1[1] + v1[2]*v1[2];
	//len1 = sqrt(len1);
	float len2 = v2[0]*v2[0] + v2[1]*v2[1] + v2[2]*v2[2];
	//len2 = sqrt(len2);
	float dot = v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
	float angle = dot/(len1*len2);
	//printf("Angle: %f\n", 180*(acos(angle)/M_PI));
	return angle;
	}
#define lerp(a,b,t) a+((b-a)*t)

/*
	find next intersection along a line to the x y and z axes
	see which is shorter, go that length along the line
	get id at that point
	repeat till length = max_length

	find X
	adjacent = point to point with x axis on next grid point
	cos(theta) = (a . b) / (|a| . |b|)
	Already have cos(theta) just use directly
	Hypotonese = adjacent / cos(theta) 
*/
float
get_next_intersection(int axis, float ray[3], float pos[3])
	{
	float length;
		float next[3];
		float adj;
		int neg=0;
		/*init all*/
		next[0]=0;
		next[1]=0;
		next[2]=0;

		if (ray[axis]>0) {
			adj= 1-(pos[axis] - floor(pos[axis]));
			next[axis]= 1;
			}
		else {
			adj= (pos[axis] - floor(pos[axis]));
			next[axis]= -1;
			neg=1;
			}
		float angle = angle_between3(ray, next);
		length= adj/angle;
		/*If angle is zero then axis is straight ahead
		the length is just the adjacent side??
		*/
		if (angle==0) length=adj;
		if (neg) length+=0.01;
		return length;
	}

/* should get previous block to return one infront
	this way we can place blocks
*/
unsigned char
cast_ray(struct region* region, int previous, float x, float y, float z, 
	float vx, float vy, float vz, float *bx, float *by, float *bz)
	{
	float max = 4.0f;
	float m = max*10;
	unsigned char id;
	float nx,ny,nz;
	float px,py,pz;
	int i;

	for (i=0; i<max*m ; i++) {
		*bx= x;
		*by= y;
		*bz= z;
		id = get_id(region, x,y,z);
		if (id) {
			if (previous) {
			*bx=px; *by=py; *bz=pz;
			}
			return id;
			}
		px = x; py = y; pz = z;
		x += vx/m;
		y += vy/m;
		z += vz/m;
		}
	return 0;
	

	}
/*Keep THIS!!! - Slow but it is the most accurate?, With this we
know which face is hit
*/
//unsigned char
//old_cast_ray(struct line *l, struct region* region, float *bx, float *by, float *bz)
//	{
//	unsigned char id=0;
//	float x,y,z;
//	float total_length=0;
//	float ray[3];
//	float c_pos[3]; /*current position on ray*/
//	memcpy(c_pos, l->a, sizeof(float)*3);
//	/* Get the vector of the ray */
//	ray[0] = l->b[0] - l->a[0];
//	ray[1] = l->b[1] - l->a[1];
//	ray[2] = l->b[2] - l->a[2];
//	//printf("ray %.2f %.2f %.2f", ray[0], ray[1], ray[2]);
//	float ray_length = sqrt(ray[0]*ray[0] + ray[1]*ray[1] + ray[2]*ray[2]);
//	//printf("length %02f\n", ray_length);
//
//		//printf("initial c_pos:%f %f %f\n", c_pos[0], c_pos[1], c_pos[2]);
//
//	int i;
//	while(1) {
//		/*Get length to next X,Y,Z intersection*/
//		float tox=4;
//		float toy=4;
//		float toz=4;
//		tox = get_next_intersection(0, ray, c_pos);
//		toy = get_next_intersection(1, ray, c_pos);
//		toz = get_next_intersection(2, ray, c_pos);
//
//		float prog=toz; /*progress*/
//		/*Dont let it go minus or minus infity, if it does then make
//			it far away
//			Zero is also not good, progress will not be made
//		*/
//		if (tox<=0) tox=100;
//		if (toy<=0) toy=100;
//		if (toz<=0) toz=100;
//		/*Choose shortest*/
//		if (toy<prog) prog=toy;
//		if (tox<prog) prog=tox;
//		//printf("Loop prog=%f; %f %f %f\n", prog, tox, toy, toz);
//		total_length+=prog;
//		x = lerp(c_pos[0], c_pos[0]+ray[0], prog);
//		y = lerp(c_pos[1], c_pos[1]+ray[1], prog);
//		z = lerp(c_pos[2], c_pos[2]+ray[2], prog);
//		/* next time start from last position */
//		c_pos[0] =x;
//		c_pos[1] =y;
//		c_pos[2] =z;
//		id = get_id(region, x,y,z);
//		//printf("Got ID:%i\n", id);
//		//printf("[%i]c_pos:%f %f %f\n", i, c_pos[0], c_pos[1], c_pos[2]);
//		if (id) break;
//		if (total_length > 4.0f) break;
//		}
//		l->b[0] = x;
//		l->b[1] = y;
//		l->b[2] = z;
//	if (bx) *bx=x;
//	if (by) *by=y;
//	if (bz) *bz=z;
//	return id;
//	}
void
build_chunk(struct region* region, struct geometry* g, unsigned int chunk_id)
	{
	int j;
	int i=chunk_id;
	if (!region->chunks[chunk_id]) return ;

		for (j=0; j<16*16*256;j++) {
			int x= j%16;
			int y= j/(16*16);
			int z= (j%(16*16))/16;
			x += (i%32)*16;
			z += (i/32)*16;

			/*Skip if chunk doesn't even exist*/
			//if (!region->chunks[(x/16)+(z/16)*32]) continue;

			unsigned char id = get_id(region, x,y, z);
			/* If not transparent and also not air*/
			if (!(id==0) && !faces[id][0]) continue;

			unsigned char below=0, above=0, left=0, right=0, front=0, back=0;
			if (y>0) below = 	get_id(region, x,y-1,z);
			if (y<255) above = 	get_id(region, x,y+1,z);
			if (x>0) left = 	get_id(region, x-1,y,z);
			if (x<511) right = 	get_id(region, x+1,y,z);
			if (z<511) front = 	get_id(region, x,y,z+1);
			if (z>0) back = 	get_id(region, x,y,z-1);

			int nx = x*BLOCK_SIZE;
			int ny = y*BLOCK_SIZE;
			int nz = z*BLOCK_SIZE;

			if (below) 	build_top(region, nx,ny-BLOCK_SIZE,nz, FACE_TOP, 0,1,0, g, 	faces[below][2]);
			if (above) 	build_top(region, nx,ny+BLOCK_SIZE,nz, FACE_BOTTOM, 0,-1,0, g, 	faces[above][3]);
			if (left )	build_top(region, nx-BLOCK_SIZE,ny,nz, FACE_RIGHT, 1,0,0, g, 	faces[left][4]);
			if (right)	build_top(region, nx+BLOCK_SIZE,ny,nz, FACE_LEFT, -1,0,0, g, 	faces[right][5]);
			if (front)	build_top(region, nx,ny,nz+BLOCK_SIZE, FACE_BACK, 0,0,-1, g, 	faces[front][6]);
			if (back )	build_top(region, nx,ny,nz-BLOCK_SIZE, FACE_FRONT, 0,0,1, g, 	faces[back][7]);
			}
	}

void
rebuild_chunk(struct region* r, struct geometry chunks[32*32], unsigned int id)
	{
	struct geometry *g;
	g = &chunks[id];
	free(g->verts);
	geometry_init(g);
	build_chunk(r, g, id);
	geometry_to_vbo(g);
	}
void
build_chunks(struct region *region, struct geometry chunks[32*32])
	{
	int i,j;
	struct geometry *g;

	for (i=0; i<32*32; i++) {
		g = &chunks[i];
		geometry_init(g);
		if (!region->chunks[i]) continue;
		unsigned int cx = i%32;
		unsigned int cz = i/32;
		build_chunk(region, g, i);
		geometry_to_vbo(g);
		//printf("g count %i vbo=%i\n", g->count, chunks[i].vbo);
		}
	}

struct player {
	float matrix[16];
	float v[3];
	};

void
player_update(struct player* p, struct region* r)
	{
	float x = p->matrix[12]/BLOCK_SIZE;
	float y = p->matrix[13]/BLOCK_SIZE;
	float z = p->matrix[14]/BLOCK_SIZE;
	float v[3];
	v[0] = p->v[0];
	v[1] = p->v[1];
	v[2] = p->v[2];

	/* Collision test */
	unsigned char id = get_id(r, x+v[0],y+v[1],z+v[2]);
	if (id == 0) {
		/*Gravity */
		p->v[1] -= 0.05;
		p->matrix[12]+=v[0]*BLOCK_SIZE;
		p->matrix[13]+=v[1]*BLOCK_SIZE;
		p->matrix[14]+=v[2]*BLOCK_SIZE;
		} 
	else p->v[0] = p->v[1] = p->v[2]=0;

	} 
float pverts[]={
	0,0,0, 		0,-32,0,	16,-32,0,	16,0,0,
	/* Back */
	16,0,-16, 	16,-32,-16, 	0,-32,-16, 	0,0,-16,
	/* Left */
	0,0,0,		0,0,-16,	 0,-32,-16,	0,-32,0,
	/* Right */
	16,0,0,		16,-32,0,	16,-32,-16,	16,0,-16,
	/*Top*/
	0,0,0, 		16,0,0, 	16,0,-16, 	0,0,-16,
	/*Bottom*/
	0,-32,0, 	0,-32,-16, 	16,-32,-16,	16,-32,0,
	};
int
map_place_block(float vx, float vy, float vz, float x, float y, float z, struct region* region, struct geometry* chunks, unsigned char block_id, int previous)
	{
	float bx,by,bz;
	unsigned char id = cast_ray(region, previous, x,y,z, vx,vy,vz, &bx,&by,&bz);
	printf("Result %f %f %f\n", bx,by,bz);
	if (bx>0 && by>0 && bz>0 && id>0) {
		unsigned int chunk_id = set_id(region, bx,by,bz, block_id);
		unsigned char nid = get_id(region, bx,by,bz);
		int cx = chunk_id%32;
		int cz = chunk_id/32;
		glDeleteBuffers(1, &chunks[chunk_id].vbo);
		/*THIS IS A PROBLEM, WHAT IF chunk_id is invalid?*/
		rebuild_chunk(region, chunks, chunk_id);
		if (cx>0) rebuild_chunk(region, chunks, chunk_id-1);
		if (cx<32) rebuild_chunk(region, chunks, chunk_id+1);
		if (cz>0) rebuild_chunk(region, chunks, chunk_id-32);
		if (cz<32) rebuild_chunk(region, chunks, chunk_id+32);
		printf("ID=%i; vbo:%i\n", id, chunks[chunk_id].vbo);
		}
	return 0;
	}

void
geometry_draw(struct geometry* g)
	{
	glBindBuffer(GL_ARRAY_BUFFER, g->vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(struct vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(struct vertex), (const void*) (6*sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(struct vertex), (const void*) (8*sizeof(float)));
	glDrawArrays(GL_TRIANGLES, 0, g->count);
	}
int
main(int argc, char *argv[])
	{
	struct position cam_pos = {0};
	char* filename;
	FILE *fp;
	int i;
	int region_map[0x2000];
	struct region region = {0};
	int quit = 0;
	SDL_Event event;
int display_index = 0;

	puts(PACKAGE_STRING);
	filename = argv[1];

	printf("Opening region file %s\n", filename);
	fp = fopen(filename, "rb");
	if (!fp) return -1;
	fread(region_map, 32*32, 4, fp);

	for (i=0; i<32*32; i++) {
		int x = i%32;
		if (region_map[i]) printf("X");
		else printf("0");
		if (x==31) puts("");
		}

	for (i=0; i<32*32; i++) {
		unsigned char* ptr = (unsigned char*)(&region_map[i]);
		region.chunks[i] = 0;
		if (region_map[i] == 0) continue;
		unsigned int offset = (ptr[0]<<16 | ptr[1]<<8 | ptr[2]);
		unsigned char sector = ptr[3];
		//printf("%X %i\n", offset, sector);
		fseek(fp, 0x1000*offset, SEEK_SET);
		extern unsigned int position;
		position = 0;
		region.chunks[i] = calloc(1, sizeof(struct chunk));
		//printf("loading chunk %i,%i\n", i%32,i/32);
		load_chunk(fp, region.chunks[i]);
	}
	fclose(fp);

	/* Set up SDL*/

SDL_Init(SDL_INIT_VIDEO);

	SDL_DisplayMode dm;
 printf("Using Display %i\n", display_index);

 if (SDL_GetCurrentDisplayMode(display_index, &dm) != 0)
  {
  printf("Display[%i] does not exist.", display_index);
 exit(-1);
}
	SDL_Rect b_rect;
	SDL_GetDisplayUsableBounds(display_index, &b_rect);
	printf("Display: %ix%i\n", b_rect.w, b_rect.h);
setup_sdl("MCViewer", dm.w, dm.h, b_rect.x, b_rect.y);

fp = fopen("resources/tiles.tga", "rb");
void* pixels;
pixels = malloc(1024*1024*4);
fseek(fp, 18, SEEK_SET);
fread(pixels, 1024*1024, 4, fp);
fclose(fp);

unsigned int texid;
glGenTextures(1, &texid);
glBindTexture(GL_TEXTURE_2D, texid);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, 4);
glGenerateMipmap(GL_TEXTURE_2D);

free(pixels);


set_position(&cam_pos, &photo_position);

struct geometry chunks[32*32] = {0};
struct geometry player_geometry = {};

geometry_init(&player_geometry);
for (i=0; i<6; i++)
	{
	int j;
	for (j=0;j<6;j++) {
		struct vertex v;
		v.x = cube_verts[face_ints[i][j]*3+0];
		v.y = cube_verts[face_ints[i][j]*3+1]*2.0;
		v.z = cube_verts[face_ints[i][j]*3+2];
		v.r = 1;
		v.g = 0;
		v.b = 1;
		geometry_add(&player_geometry, &v);
		}
	}
geometry_to_vbo(&player_geometry);

build_chunks(&region, chunks);

char up=0,down=0,left=0,right=0;
char q_key=0;
char e_key=0;

float camvx =0;
float camvy =0;
float camvz =0;
float rot=0;
float m[16];
int mleft=0;
int mright=0;
float projection_matrix[16];
make_projection_matrix(projection_matrix, b_rect.w, b_rect.h, 80);
SDL_SetRelativeMouseMode(SDL_TRUE);

struct player player = {0};
matrix_identity(player.matrix);
matrix_translate(player.matrix, 0, 85*BLOCK_SIZE, 45*BLOCK_SIZE);
float theta=0;
float target_rx=cam_pos.rx;
float target_ry=cam_pos.ry;

	while(!quit) {
		matrix_load(m, projection_matrix);
		matrix_rotate(m, 1,0,0, cam_pos.rx);
		matrix_rotate(m, 0,1,0, cam_pos.ry);
		matrix_translate(m, -cam_pos.x*BLOCK_SIZE, -cam_pos.y*BLOCK_SIZE, -cam_pos.z*BLOCK_SIZE);

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN: 
					switch(event.key.keysym.sym) {
						case SDLK_ESCAPE:quit = 1;break;
						case SDLK_UP:  player.v[2]+=0.1; break;
						case SDLK_DOWN:  player.v[2]-=0.1; break;
						case SDLK_w: up=1; break;
						case SDLK_s: down=1; break;
						case SDLK_a: left=1; break;
						case SDLK_d: right=1; break;
						case SDLK_q: q_key=1; break;
						case SDLK_e: e_key=1; break;
						case SDLK_z:
							/*xyz rotationxzy*/
							printf("position: %f, %f, %f, %f, %f, %f\n",
							cam_pos.x, cam_pos.y, cam_pos.z,
							cam_pos.rx, cam_pos.ry, cam_pos.rz);
							break;
						case SDLK_p:
							/*Stop any movement*/
							camvx=0;
							camvy=0;
							camvz=0;
							/*Set cam position*/
							set_position(&cam_pos, &photo_position);

							target_rx = cam_pos.rx;
							target_ry = cam_pos.ry;
							break;
						case SDLK_t: {
							textures_enabled ^= 1; 
							if (!textures_enabled)
								glDisableVertexAttribArray(1);
							else
								glEnableVertexAttribArray(1);
							break;
							}
						case SDLK_l: {
							lighting_enabled ^= 1; 
							if (!lighting_enabled)
								glDisableVertexAttribArray(2);
							else
								glEnableVertexAttribArray(2);
							break;
							}
						case SDLK_o:
							{
							player.matrix[12] = 15*BLOCK_SIZE;
							player.matrix[13] = 85*BLOCK_SIZE;
							player.matrix[14] = 45*BLOCK_SIZE;

							break;
							}
						case SDLK_SPACE:
							{
							player.v[1]+=0.6;

							break;
							}
						}
					break;
				case SDL_KEYUP: 
					switch(event.key.keysym.sym) {
						case SDLK_w: up=0; break;
						case SDLK_s: down=0; break;
						case SDLK_a: left=0; break;
						case SDLK_d: right=0; break;
						case SDLK_q: q_key=0; break;
						case SDLK_e: e_key=0; break;
						}
					break;
				}
			}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		#define LERP_FACTOR 0.02
		if (up) {
			camvx = lerp(camvx, m[2]*SPEED, LERP_FACTOR); 
			camvy = lerp(camvy, m[6]*SPEED, LERP_FACTOR); 
			camvz = lerp(camvz, m[10]*SPEED, LERP_FACTOR); 
			}
		else {
			camvx = lerp(camvx, 0, LERP_FACTOR); 
			camvy = lerp(camvy, 0, LERP_FACTOR); 
			camvz = lerp(camvz, 0, LERP_FACTOR); 
			}
		if (down) {
			camvx = lerp(camvx, -m[2]*SPEED, LERP_FACTOR); 
			camvy = lerp(camvy, -m[6]*SPEED, LERP_FACTOR); 
			camvz = lerp(camvz, -m[10]*SPEED, LERP_FACTOR); 
			}
		else {
			camvx = lerp(camvx, 0, LERP_FACTOR); 
			camvy = lerp(camvy, 0, LERP_FACTOR); 
			camvz = lerp(camvz, 0, LERP_FACTOR); 
			}
	
		if (left) {
			camvx = lerp(camvx, -m[0]*SPEED, LERP_FACTOR); 
			camvy = lerp(camvy, -m[4]*SPEED, LERP_FACTOR); 
			camvz = lerp(camvz, -m[8]*SPEED, LERP_FACTOR); 
			}
		else {
			camvx = lerp(camvx, 0, LERP_FACTOR); 
			camvy = lerp(camvy, 0, LERP_FACTOR); 
			camvz = lerp(camvz, 0, LERP_FACTOR); 
			}
	
		if (right) {
			camvx = lerp(camvx, m[0]*SPEED, LERP_FACTOR); 
			camvy = lerp(camvy, m[4]*SPEED, LERP_FACTOR); 
			camvz = lerp(camvz, m[8]*SPEED, LERP_FACTOR); 
			}
		else {
			camvx = lerp(camvx, 0, LERP_FACTOR); 
			camvy = lerp(camvy, 0, LERP_FACTOR); 
			camvz = lerp(camvz, 0, LERP_FACTOR); 
			}
		if (q_key) {
			camvx = lerp(camvx, 0, LERP_FACTOR); 
			camvy = lerp(camvy, SPEED, LERP_FACTOR); 
			camvz = lerp(camvz, 0, LERP_FACTOR); 
			}
		else {
			camvx = lerp(camvx, 0, LERP_FACTOR); 
			camvy = lerp(camvy, 0, LERP_FACTOR); 
			camvz = lerp(camvz, 0, LERP_FACTOR); 
			}
		if (e_key) {
			camvx = lerp(camvx, 0, LERP_FACTOR); 
			camvy = lerp(camvy, -SPEED, LERP_FACTOR); 
			camvz = lerp(camvz, 0, LERP_FACTOR); 
			}
		else {
			camvx = lerp(camvx, 0, LERP_FACTOR); 
			camvy = lerp(camvy, 0, LERP_FACTOR); 
			camvz = lerp(camvz, 0, LERP_FACTOR); 
			}
		/*add movement VECTOr not VIEW vector */
		float uvx, uvy, uvz;
		float vlen = camvx*camvx + camvy*camvy + camvz*camvz;
		if (vlen == 0) {
			vlen=0;
			uvx=uvy=uvz=0;
			}
		else {
			vlen = sqrt(vlen);
			uvx = camvx/vlen;
			uvy = camvy/vlen;
			uvz = camvz/vlen;
		}
	
		cam_pos.x += camvx;
		cam_pos.y += camvy;
		cam_pos.z += camvz;

		glUniformMatrix4fv(model_view_matrix_location, 1, 0, m);

		glUniform1f(theta_location, theta);
		theta+=0.1;
		int mx,my;
		int ret = SDL_GetRelativeMouseState(&mx, &my);
		if (ret & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			if (mleft) mleft &= 0x7F;
			else mleft |= 0x80;
			mleft |= 1;
		 	}
		else mleft=0;

		if (ret & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
			if (mright) mright &= 0x7F;
			else mright |= 0x80;
			mright |= 1;
		 	}
		else mright=0;

	if (mleft & 0x80){
		map_place_block(m[2], m[6], m[10], 
			cam_pos.x, cam_pos.y, cam_pos.z, 
			&region, chunks, 1, 1);
		}
	if (mright & 0x80){
		map_place_block(m[2], m[6], m[10], 
			cam_pos.x, cam_pos.y, cam_pos.z, 
			&region, chunks, 0, 0);
		}

		if (mx) {
			target_ry += mx/256.0;
		}
		if (my) {
			target_rx += my/256.0;
		}

		cam_pos.rx = lerp(cam_pos.rx, target_rx, 0.2);
		cam_pos.ry = lerp(cam_pos.ry, target_ry, 0.2);


		for (i=0; i<32*32; i++) {
			geometry_draw(&chunks[i]);
		}

		/* Render player*/
		player_update(&player, &region);
		matrix_multiply(m, player.matrix);
		glUniformMatrix4fv(model_view_matrix_location, 1, 0, m);
		geometry_draw(&player_geometry);
		SDL_GL_SwapWindow(window);
		}

	SDL_Quit();
	return 0;
	}
