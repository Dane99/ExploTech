#version 330 core
in vec2 TexCoord;

out vec4 color;

uniform sampler2D ourTexture;

in vec4 gl_FragCoord;

void main()
{
	vec4 temp = vec4((sin(0.3*gl_FragCoord.x + 0) * 127 + 128)/256 + (sin(0.3*gl_FragCoord.y + 0) * 127 + 128)/256, (sin(0.3*gl_FragCoord.x + 2) * 127 + 128)/256 + (sin(0.3*gl_FragCoord.y + 2) * 127 + 128)/256, (sin(0.3*gl_FragCoord.x + 4) * 127 + 128)/256 + (sin(0.3*gl_FragCoord.y + 4) * 127 + 128)/256, texture(ourTexture, TexCoord).a);
    color = temp;
}