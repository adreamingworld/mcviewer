#version 330
in vec3 in_Position;
in vec2 in_TexCoord;
in vec3 in_Color;

out vec2 TexCoord;
out vec3 Color;
uniform mat4 ModelViewProjectionMatrix;

void 
main(void)
	{
	Color = in_Color;
	gl_Position = ModelViewProjectionMatrix*vec4(in_Position, 1.0);
	TexCoord = in_TexCoord;
	}
