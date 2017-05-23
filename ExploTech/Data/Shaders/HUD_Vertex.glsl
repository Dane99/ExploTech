#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoord;

uniform mat4 projMatrix;

void main()
{
	gl_Position = projMatrix * vec4(position.xy, 0.0f, 1.0f);
	TexCoord = texCoords;
}