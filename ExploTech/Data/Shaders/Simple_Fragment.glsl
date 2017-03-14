#version 330

out vec4 color;

in vec2 passTextureCoords;

uniform sampler2D ourTexture;

uniform float time;

void main()
{
	color = texture(ourTexture, passTextureCoords) * (sin(time) + 2);
}