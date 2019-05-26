#include <config.h>
#include <stdio.h>
#include <stdlib.h>

#include <myz.h>
#include <nbt.h>
#include <nbt_utils.h>

#include <SDL.h>
#include <GL/glew.h>
#include <SDL_opengl.h>

unsigned int vao, vbo, vbo2;

/*
	below above left right front back
*/
unsigned char faces[256][6] = {
		{0,0,0,0,0,0},
		{1,1,1,1,1,1}, /*stone*/
		{3,2,4,4,4,4}, /*grass*/
		{2,2,2,2,2,2}, /*dirt*/
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{8,8,8,8,8,8}, /* flowing water*/
		{8,8,8,8,8,8}, /*water*/
		{13,13,13,13,13,13}, /*flowing lava*/
		{13,13,13,13,13,13}, /*lava*/
		{9,9,9,9,9,9}, /*sand*/
		{12,12,12,12,12,12}, /*gravel*/
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{0,0,0,0,0,0},
		{7,7,6,6,6,6}, /* log?? */
		{5,5,5,5,5,5}, /* leaves*/
		{0,0,0,0,0,0}, /* log?? */
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
	};

float cube_verts[] = {
	-0.5,	0.5,	0.5,
	0.5,	0.5,	0.5,
	0.5,	-0.5,	0.5,
	-0.5,	-0.5,	0.5,
	/* back */
	-0.5,  0.5,  	-0.5,
	0.5,   0.5,  	-0.5,
	0.5,  -0.5,  	-0.5,
	-0.5, -0.5,  	-0.5,
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
		y = *((int*)y_tag->payload);
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

void
build_section(unsigned char section[4096], int sy, int cx, int cz, struct geometry* g)
	{
	int i;
	for (i=0; i<16*16*16; i++) {
		int x = i%16;
		int z = (i%(16*16))/16;
		int y = i/(16*16);
		if (section[i] !=0) continue;
	
		int nx = x+cx*16;
		int ny = y+sy*16;
		int nz = z+cz*16;

		unsigned char below=0, above=0, left=0, right=0, front=0, back=0;
		if (y>0) below = section[i-(16*16)];
		if (y<15) above = section[i+(16*16)];
		if (x>0) left = section[i-1];
		if (x<15) right = section[i+1];
		if (z<15) front = section[i+16];
		if (z>0) back = section[i-16];

		if (below) 	build_top(nx,ny-1,nz, top_ints, 0,1,0, g, 	faces[below][0]);
		if (above) 	build_top(nx,ny+1,nz, bottom_ints, 0,-1,0, g, 	faces[above][1]);
		if (left)	build_top(nx-1,ny,nz, right_ints, 1,0,0, g, 	faces[left][2]);
		if (right)	build_top(nx+1,ny,nz, left_ints, -1,0,0, g, 	faces[right][3]);
		//if (front)	build_top(nx,ny,nz+1, back_ints, 0,0,-1, g, 	faces[front][4]);
		if (back)	build_top(nx,ny,nz-1, front_ints, 0,0,1, g, 	faces[back][5]);
		}
	}

void
build_chunk(struct chunk* chunk, int x, int z, struct geometry* g)
	{
	int i;
	for (i=0; i<16; i++) {
		build_section(chunk->sections[i], i, x, z, g);
		}
	}

void
build_region(struct region* region, struct geometry* g)
	{
	int i;
	for (i=0; i<32*32; i++) {
		int x= (i%32);
		int z= i/32;
		int index = x+(z*32);
		if (region->chunks[index]) {
			build_chunk(region->chunks[index], x, z, g);
			}
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

int
main(int argc, char *argv[])
	{
	char* filename;
	FILE *fp;
	int i;
	int region_map[0x2000];
	puts(PACKAGE_STRING);
	struct region region = {0};

	filename = argv[1];

	printf("Opening region file %s\n", filename);
	fp = fopen(filename, "rb");
	if (!fp) return -1;
	fread(region_map, 32*32, 4, fp);

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
unsigned char pixels[1024*1024*4];
fseek(fp, 18, SEEK_SET);
fread(pixels, 1024*1024, 4, fp);
fclose(fp);

unsigned int texid;
glGenTextures(1, &texid);
glBindTexture(GL_TEXTURE_2D, texid);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

glEnable(GL_TEXTURE_2D);
glEnable(GL_DEPTH_TEST);
glEnable(GL_LIGHTING);
glEnable(GL_LIGHT0);
glEnable(GL_CULL_FACE);

float dir[] = {0,0.7,0.4,0};
float color[] = {1,1,1};
glLightfv(GL_LIGHT0, GL_POSITION, dir);
glLightfv(GL_LIGHT0, GL_AMBIENT, color);
//glLightfv(GL_LIGHT0, GL_DIFFUSE, color);

glMatrixMode(GL_PROJECTION);
glFrustum(-1, 1, -1, 1, 1, 1000);
glMatrixMode(GL_MODELVIEW);

float x=0;
float y=-100;
float z=-50;

struct geometry geometry;
unsigned int gvbo;
geometry_init(&geometry);
build_geometry(&geometry, &region);
printf("g count %i\n", geometry.count);

gvbo = geometry_to_vbo(&geometry);
char up=0,down=0,left=0,right=0;
	while(!quit) {
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_KEYDOWN: 
					switch(event.key.keysym.sym) {
						case SDLK_ESCAPE:quit = 1;break;
						case SDLK_w:z+=1; break;
						case SDLK_s:z-=1; break;
						case SDLK_a:x+=1; break;
						case SDLK_d:x-=1; break;
						case SDLK_q:y+=1; break;
						case SDLK_e:y-=1; break;
						case SDLK_z:printf("%f %f %f\n",x/16,y/16,z/16); break;
						}
				case SDL_KEYUP: 
					switch(event.key.keysym.sym) {
						}
				}
			}
		if (up) {
			puts("UP");
			z++;
			}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
		glTranslatef(x,y,z);
		glDrawArrays(GL_TRIANGLES, 0, geometry.count);
	//	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//	glDrawArrays(GL_TRIANGLES, 0, 3);
		SDL_GL_SwapWindow(window);
		}

	SDL_Quit();
	return 0;
	}
