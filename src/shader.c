#include <shader.h>

int
shader_source_from_file(struct shader* shader, const char* filename)
	{
	FILE* fp;
	char* source = 0;
	unsigned int size;

	fp = fopen(filename, "rb");
	if (!fp) return -1;
	fseek(fp, 0, SEEK_END);
	size=ftell(fp);
	rewind(fp);
	source = malloc(size);
	fread(source, size, 1, fp);
	source[size-1]=0;
	shader->source = source;
	return 0;
	}

int
shader_create_program(int count, struct shader* shaders)
	{
	int i;
	unsigned int program = glCreateProgram();

	for (i=0; i<count; i++)	{
		unsigned int shader = glCreateShader(shaders[i].type);
		glShaderSource(shader, 1, &shaders[i].source, 0);
		glCompileShader(shader);
		char log[256];
		int length;
		glGetShaderInfoLog(shader, 255, &length, log);
		if (length) puts(log);
		glAttachShader(program, shader);
	}
	glLinkProgram(program);
	char log[256];
	int length;
	glGetProgramInfoLog(program, 255, &length, log);
	if (length) puts(log);
	glUseProgram(program);
	return program;
	}
