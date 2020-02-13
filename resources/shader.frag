#version 130

varying vec2 TexCoord;
varying vec3 Color;
uniform sampler2D ourTexture;

void
main(void)
	{
	vec4 final_color = texture(ourTexture, TexCoord) * vec4(Color, 1.0f);
	if (
		texture2D(ourTexture,TexCoord).a == 0) discard;  
		gl_FragColor = final_color;
	}
