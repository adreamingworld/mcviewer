#version 130
attribute vec3 in_Position;
attribute vec2 in_TexCoord;
attribute vec3 in_Color;

varying vec2 TexCoord;
varying vec3 Color;

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
