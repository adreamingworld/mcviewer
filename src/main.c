#include <config.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <myz.h>
#include <nbt.h>
#include <nbt_utils.h>

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>

unsigned int vao, vbo, vbo2;

#define BLOCK_SIZE 16
#define SPEED 2

/*
	below above left right front back
*/
unsigned char faces[256][6] = {
		{0,0,0,0,0,0},
		{1,1,1,1,1,1}, /*stone*/
		{3,2,4,4,4,4}, /*grass*/
		{2,2,2,2,2,2}, /*dirt*/
		{20,20,20,20,20,20}, /*cobble*/
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{8,8,8,8,8,8}, /* flowing water*/
		{8,8,8,8,8,8}, /*water*/
		{13,13,13,13,13,13}, /*flowing lava*/
		{13,13,13,13,13,13}, /*lava*/
		{9,9,9,9,9,9}, /*sand*/
		{12,12,12,12,12,12}, /*gravel*/
		{17,17,17,17,17,17}, /* Gold*/
		{16,16,16,16,16,16}, /*Iron ore*/
		{15,15,15,15,15,15}, /*Coal ore*/
		{7,7,6,6,6,6}, /* log */
		{5,5,5,5,5,5}, /* leaves*/
		{0,0,0,0,0,0}, 
		{0,0,0,0,0,0},
		{28,28,28,28,28,28}, /*Lapis???*/
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{64,0,11,11,11,11}, /*Tall Grass*/
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{21,21,21,21,21,21}, /*Mossy cobble*/
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{28,28,28,28,28,28}, /*Mob spawner*/
		{0,0,0,0,0,0},
		{22,23,24,25,26,27}, /*Chest*/
		{0,0,0,0,0,0},
		{19,19,19,19,19,19}, /*Diamond*/
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{18,18,18,18,18,18}, /*Red stone*/
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{10,10,10,10,10,10}, /*Snow layer*/
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{29,29,29,29,29,29,}, /*Quartz block*/
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{64,64,14,14,14,14},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		};

struct vertex {
	float x,y,z;
	float nx,ny,nz;
	float u,v;
	};

struct geometry {
	struct vertex *verts;
	unsigned int capacity;
	unsigned int count;
	unsigned int vbo;
	};

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

int front_ints[] = {0,3,2, 0,2,1};
int back_ints[] = {5,6,7, 5,7,4};
int top_ints[] = {4,0,1, 4,1,5};
int bottom_ints[] = {3,7,6, 3,6,2};
int left_ints[] = {4,7,3, 4,3,0};
int right_ints[] = {1,2,6, 1,6,5};

/* 16*16*16 blocks */
struct section {
	unsigned char blocks[16*16*16];
	unsigned char y;
	};

/* 16 vertically stacked sections*/
struct chunk {
	unsigned char x;
	unsigned char z;
//	struct section* sections[16];
	unsigned char sections[16][16*16*16];
	unsigned char map[16]; /* which actually hold information*/
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

void
build_top(float x, float y, float z, int inds[6], float nx, float ny, float nz, struct geometry *g, char id)
	{
	int i;
	//id = 3;
	int uindex[] = {0,0,1, 0,1,1};
	int vindex[] = {0,1,1, 0,1,0};
	float tu = (1.0/64);
	for (i=0; i<6; i++) {
		struct vertex v;
		v.x = cube_verts[inds[i]*3 + 0] + x;
		v.y = cube_verts[inds[i]*3 + 1] + y;
		v.z = cube_verts[inds[i]*3 + 2] + z;
		v.nx = nx;
		v.ny = ny;
		v.nz = nz;
		v.u = (tu * (id%64)) + (tu*uindex[i]);
		v.v = (tu * (id/64)) + (tu*vindex[i]);
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
setup_sdl(char* title, int w, int h)
	{
	SDL_GLContext *context;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow(title, 0,0, w, h, SDL_WINDOW_OPENGL);
	context = SDL_GL_CreateContext(window);

	if (!context) puts("Failed context");
	glewInit();
	/*VAO*/
	//glCreateVertexArrays(1, &vao);
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

	/*Get chunk*/
	chunk = r->chunks[chunkx+chunkz*32];
	if (!chunk) return 0;
	id = chunk->sections[isection][blockx + (blockz*16) + (blocky*(16*16))];


	return id;
	}

void
build_region(struct region* region, struct geometry* g)
	{
	int i;
	for (i=0; i<512*512*256; i++) {
		int x= i%512;
		int y= i/(512*512);
		int z= (i%(512*512))/512;


	/*Skip if chunk doesn't even exist*/
	if (!region->chunks[(x/16)+(z/16)*32]) continue;

		unsigned char id = get_id(region, x,y, z);
		if (id !=0) continue;

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

		if (below) 	build_top(nx,ny-BLOCK_SIZE,nz, top_ints, 0,1,0, g, 	faces[below][0]);
		if (above) 	build_top(nx,ny+BLOCK_SIZE,nz, bottom_ints, 0,-1,0, g, 	faces[above][1]);
		if (left)	build_top(nx-BLOCK_SIZE,ny,nz, right_ints, 1,0,0, g, 	faces[left][2]);
		if (right)	build_top(nx+BLOCK_SIZE,ny,nz, left_ints, -1,0,0, g, 	faces[right][3]);
		if (front)	build_top(nx,ny,nz+BLOCK_SIZE, back_ints, 0,0,-1, g, 	faces[front][4]);
		if (back)	build_top(nx,ny,nz-BLOCK_SIZE, front_ints, 0,0,1, g, 	faces[back][5]);
		}
	}
void
build_geometry(struct geometry* g, struct region* region)
	{
	build_region(region, g);
	}

unsigned int
geometry_to_vbo(struct geometry* g)
	{
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(struct vertex)*g->count, g->verts, GL_STATIC_DRAW);

	glVertexPointer(3, GL_FLOAT, sizeof(struct vertex), 0);
	glNormalPointer(GL_FLOAT, sizeof(struct vertex), (const void*) (3*sizeof(float)) );
	glTexCoordPointer(2, GL_FLOAT, sizeof(struct vertex), (const void*) (6*sizeof(float)) );

	return vbo;
	}

struct line {
	float a[3];
	float b[3];
	};

void
draw_line(struct line *l)
	{
	float a[3];
	float b[3];
	a[0] = l->a[0]*BLOCK_SIZE;
	a[1] = l->a[1]*BLOCK_SIZE;
	a[2] = l->a[2]*BLOCK_SIZE;
	b[0] = l->b[0]*BLOCK_SIZE;
	b[1] = l->b[1]*BLOCK_SIZE;
	b[2] = l->b[2]*BLOCK_SIZE;
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
		glBegin(GL_LINES);
		glColor3f(0.5, 0.5, 0.5);
		glVertex3fv(a);
		glVertex3fv(b);
		glEnd();
		glBegin(GL_POINTS);
		glColor3f(0,1,0);
		glVertex3fv(a);
		glColor3f(1,0,0);
		glVertex3fv(b);
		glEnd();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
		glColor3f(1,1,1);
	}
/*
We don't really need the square root to get the length?
we want the angle, not the actual length
so the proportion is important not the exact length?
*/
/* returns cos(theta) not theta*/
float
angle_between3(float v1[3], float v2[3])
	{
	/*ANGLE BETWEEN TWO VECTORS*/
	float len1 = v1[0]*v1[0] + v1[1]*v1[1] + v1[2]*v1[2];
	len1 = sqrt(len1);
	float len2 = v2[0]*v2[0] + v2[1]*v2[1] + v2[2]*v2[2];
	len2 = sqrt(len2);
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
		if (neg) length+=0.1;
		return length;
	}
unsigned char
cast_ray(struct line *l, struct region* region, int *bx, int *by, int *bz)
	{
	unsigned char id=0;
	float x,y,z;
	float total_length=0;
	float ray[3];
	float c_pos[3]; /*current position on ray*/
	memcpy(c_pos, l->a, sizeof(float)*3);
	/* Get the vector of the ray */
	ray[0] = l->b[0] - l->a[0];
	ray[1] = l->b[1] - l->a[1];
	ray[2] = l->b[2] - l->a[2];
	//printf("ray %.2f %.2f %.2f", ray[0], ray[1], ray[2]);
	float ray_length = sqrt(ray[0]*ray[0] + ray[1]*ray[1] + ray[2]*ray[2]);
	//printf("length %02f\n", ray_length);

		//printf("initial c_pos:%f %f %f\n", c_pos[0], c_pos[1], c_pos[2]);

	int i;
	while(1) {
		/*Get length to next X,Y,Z intersection*/
		float tox=4;
		float toy=4;
		float toz=4;
		tox = get_next_intersection(0, ray, c_pos);
		toy = get_next_intersection(1, ray, c_pos);
		toz = get_next_intersection(2, ray, c_pos);

		float prog=toz; /*progress*/
		/*Dont let it go minus or minus infity, if it does then make
			it far away
			Zero is also not good, progress will not be made
		*/
		if (tox<=0) tox=100;
		if (toy<=0) toy=100;
		if (toz<=0) toz=100;
		/*Choose shortest*/
		if (toy<prog) prog=toy;
		if (tox<prog) prog=tox;
		//printf("Loop prog=%f; %f %f %f\n", prog, tox, toy, toz);
		total_length+=prog;
		x = lerp(c_pos[0], c_pos[0]+ray[0], prog);
		y = lerp(c_pos[1], c_pos[1]+ray[1], prog);
		z = lerp(c_pos[2], c_pos[2]+ray[2], prog);
		/* next time start from last position */
		c_pos[0] =x;
		c_pos[1] =y;
		c_pos[2] =z;
		id = get_id(region, x,y,z);
		//printf("Got ID:%i\n", id);
		//printf("[%i]c_pos:%f %f %f\n", i, c_pos[0], c_pos[1], c_pos[2]);
		if (id) break;
		if (total_length > 4.0f) break;
		}
		l->b[0] = x;
		l->b[1] = y;
		l->b[2] = z;
	if (bx) *bx=x;
	if (by) *by=y;
	if (bz) *bz=z;
	return id;
	}
void
build_chunk(struct region* region, struct geometry* g, unsigned int chunk_id)
	{
	int j;
	int i=chunk_id;

		for (j=0; j<16*16*256;j++) {
			int x= j%16;
			int y= j/(16*16);
			int z= (j%(16*16))/16;
			x += (i%32)*16;
			z += (i/32)*16;

			/*Skip if chunk doesn't even exist*/
			//if (!region->chunks[(x/16)+(z/16)*32]) continue;

			unsigned char id = get_id(region, x,y, z);
			if (id !=0) continue;

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

			if (below) 	build_top(nx,ny-BLOCK_SIZE,nz, top_ints, 0,1,0, g, 	faces[below][0]);
			if (above) 	build_top(nx,ny+BLOCK_SIZE,nz, bottom_ints, 0,-1,0, g, 	faces[above][1]);
			if (left)	build_top(nx-BLOCK_SIZE,ny,nz, right_ints, 1,0,0, g, 	faces[left][2]);
			if (right)	build_top(nx+BLOCK_SIZE,ny,nz, left_ints, -1,0,0, g, 	faces[right][3]);
			if (front)	build_top(nx,ny,nz+BLOCK_SIZE, back_ints, 0,0,-1, g, 	faces[front][4]);
			if (back)	build_top(nx,ny,nz-BLOCK_SIZE, front_ints, 0,0,1, g, 	faces[back][5]);
			}
	}

unsigned int 
rebuild_chunk(struct region* r, unsigned int id)
	{
	struct geometry g={0};
	geometry_init(&g);
	build_chunk(r, &g, id);
	return geometry_to_vbo(&g);
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
		//if (cz>0) continue;
		//if (cx>0) continue;
		build_chunk(region, g, i);
		chunks[i].vbo = geometry_to_vbo(g);
		//printf("g count %i vbo=%i\n", g->count, chunks[i].vbo);
		}
	}
int
main(int argc, char *argv[])
	{
	char* filename;
	FILE *fp;
	int i;
	int region_map[0x2000];
	puts(PACKAGE_STRING);
	struct region region = {0};
struct line line = {0,0,0, 0,0,10};
	filename = argv[1];

	printf("Opening region file %s\n", filename);
	fp = fopen(filename, "rb");
	if (!fp) return -1;
	fread(region_map, 32*32, 4, fp);

	for (i=0; i<32*32; i++) {
		int x = i%32;
		if (region_map[i]) printf("XX");
		else printf("00");
		if (x==31) puts("");
		}

	angle_between3(
		((float[3]){0,1,0}),
		((float[3]){1,0,0})
		);

	for (i=0; i<32*32; i++) {
		unsigned char* ptr = (unsigned char*)(&region_map[i]);
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
	int quit = 0;
	SDL_Event event;
setup_sdl("MCViewer", 1024, 1024);

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

glEnable(GL_TEXTURE_2D);
glEnable(GL_DEPTH_TEST);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glEnable(GL_LIGHT1);
glEnable(GL_LIGHT2);
glEnable(GL_CULL_FACE);

float dir[] = {0,0.7,0.4,0};
float color[] = {1,1,1,1};
glLightfv(GL_LIGHT0, GL_POSITION, dir);
glLightfv(GL_LIGHT0, GL_AMBIENT, color);
glLightModelfv(GL_LIGHT_MODEL_AMBIENT, color);

glMatrixMode(GL_PROJECTION);
glFrustum(-1, 1, -1, 1, 1, 10000);
glMatrixMode(GL_MODELVIEW);

glClearColor(0,0,1,0);

float x=0;
float y=100;
float z=50.5;

struct geometry geometry;
unsigned int gvbo;
geometry_init(&geometry);
//build_geometry(&geometry, &region);
printf("g count %i\n", geometry.count);

struct geometry chunks[32*32] = {0};

//gvbo = geometry_to_vbo(&geometry);

build_chunks(&region, chunks);

char up=0,down=0,left=0,right=0;
char q_key=0;
char e_key=0;

float rx=0;
float ry=0;
float rz=0;
float m[16]={0};
	while(!quit) {
		float fx, fy, fz;
		fx = m[2];
		fy = m[6];
		fz = m[10];

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN: 
					switch(event.key.keysym.sym) {
						case SDLK_ESCAPE:quit = 1;break;
						case SDLK_w: up=1; break;
						case SDLK_s: down=1; break;
						case SDLK_a: left=1; break;
						case SDLK_d: right=1; break;
						case SDLK_q: q_key=1; break;
						case SDLK_e: e_key=1; break;
						case SDLK_z:printf("%f %f %f\n",x,y,z); break;
						case SDLK_SPACE:
							{
							int bx,by,bz;
							line.a[0]=x; 
							line.a[1]=y; 
							line.a[2]=z;
							line.b[0]=x+-m[2]*1; 
							line.b[1]=y+-m[6]*1; 
							line.b[2]=z+-m[10]*1;
							unsigned char id = cast_ray(&line, &region, &bx,&by,&bz);
							unsigned int chunk_id = set_id(&region, bx,by,bz, 0);
							glDeleteBuffers(1, &chunks[chunk_id].vbo);
							chunks[chunk_id].vbo = rebuild_chunk(&region, chunk_id);
							printf("ID=%i; vbo:%i\n", id, chunks[chunk_id].vbo);
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

	if (up) {	x-=m[2]*SPEED; y-=m[6]*SPEED; z-=m[10]*SPEED;}
	if (down) {	x+=m[2]*SPEED; y+=m[6]*SPEED; z+=m[10]*SPEED;}
	if (left) {	x-=m[0]*SPEED; y-=m[4]*SPEED; z-=m[8]*SPEED;}
	if (right) {	x+=m[0]*SPEED; y+=m[4]*SPEED; z+=m[8]*SPEED;}
	if (q_key) {y-=1*SPEED;}
	if (e_key) {y+=1*SPEED;}

		int mx,my;
		int mleft = 0;
		int ret = SDL_GetRelativeMouseState(&mx, &my);
		if (ret & SDL_BUTTON(SDL_BUTTON_LEFT)) mleft = 1;

		if (mx && mleft) {
			ry += mx/4.0;
		}
		if (my && mleft) {
			rx += my/4.0;
		}

		glLoadIdentity();
		glRotatef(rx, 1,0,0);
		glRotatef(ry, 0,1,0);
		glTranslatef(-x*BLOCK_SIZE,-y*BLOCK_SIZE,-z*BLOCK_SIZE);
		glGetFloatv(GL_MODELVIEW_MATRIX, m);
		
		//glDrawArrays(GL_TRIANGLES, 0, geometry.count);
		for (i=0; i<32*32; i++) {
			glBindBuffer(GL_ARRAY_BUFFER, chunks[i].vbo);
			glVertexPointer(3, GL_FLOAT, sizeof(struct vertex), 0);
			glNormalPointer(GL_FLOAT, sizeof(struct vertex), (const void*) (3*sizeof(float)) );
			glTexCoordPointer(2, GL_FLOAT, sizeof(struct vertex), (const void*) (6*sizeof(float)) );
			glDrawArrays(GL_TRIANGLES, 0, chunks[i].count);
		}
glLineWidth(4);
glPointSize(8);
							line.a[0]=x; 
							line.a[1]=y; 
							line.a[2]=z;
							line.b[0]=x+-m[2]*1; 
							line.b[1]=y+-m[6]*1; 
							line.b[2]=z+-m[10]*1;
		unsigned char id = cast_ray(&line, &region, 0,0,0);
		//glDisable(GL_DEPTH_TEST);
		draw_line(&line);
		//glEnable(GL_DEPTH_TEST);
		SDL_GL_SwapWindow(window);
		}

	SDL_Quit();
	return 0;
	}
