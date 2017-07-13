#version 330

out vec4 color;

in vec2 passTextureCoords;
flat in float passLayer;

uniform sampler2DArray textureArray;

uniform float time;

void main()
{
	//float test = 1.0f;
	color = vec4(texture(textureArray, vec3(passTextureCoords, passLayer)));
	//* (((sin(time) + 1)/2) + 0.5);
}