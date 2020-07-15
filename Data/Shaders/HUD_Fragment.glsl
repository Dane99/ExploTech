#version 330 core
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;

uniform float time;

in vec4 gl_FragCoord;

void main()
{
	vec4 temp = vec4((sin(0.003*gl_FragCoord.x*mod(time, 100) + 0) * 127 + 128)/256,
					(sin(0.003*gl_FragCoord.x*mod(time, 100) + 2) * 127 + 128)/256,
					(sin(0.003*gl_FragCoord.x*mod(time, 100) + 4) * 127 + 128)/256,
					texture(ourTexture, TexCoord).a);
	color = temp;
}