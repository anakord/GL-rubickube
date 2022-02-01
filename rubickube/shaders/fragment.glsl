#version 330 core

in vec3 fragmentColor;
in vec2 TexCoord;

out vec4 Color;

uniform sampler2D sTexture;

void main()
{
	Color = texture(sTexture, TexCoord) * vec4(fragmentColor, 1.0f);;
}