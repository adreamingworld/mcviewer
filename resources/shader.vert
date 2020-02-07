#version 330
in vec3 in_Position;
in vec2 in_TexCoord;
in vec3 in_Color;

out vec2 TexCoord;
out vec3 Color;

uniform mat4 ModelViewProjectionMatrix;
uniform float theta;

void 
main(void)
	{
	Color = in_Color;
	//vec3 nPos = vec3(in_Position.x+cos(in_Position.y+in_Position.z+theta), in_Position.y, in_Position.z+sin(theta+in_Position.x+in_Position.y));
	gl_Position = ModelViewProjectionMatrix*vec4(in_Position, 1.0);
	TexCoord = in_TexCoord;
	}
