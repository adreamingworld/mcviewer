#version 330

in vec2 TexCoord;
in vec3 Color;
uniform sampler2D ourTexture;

void
main(void)
	{
	gl_FragColor = texture(ourTexture, TexCoord) * vec4(Color, 1.0f);
	}
