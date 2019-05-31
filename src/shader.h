#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>

struct shader {
	unsigned int type;
	const char *source;
	};

int shader_source_from_file(struct shader* shader, const char* filename);
int shader_create_program(int count, struct shader* shaders);

#endif /* SHADER_H */
