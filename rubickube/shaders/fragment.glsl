#version 330 core

in vec3 fragmentColor;
in vec2 TexCoord;

out vec4 Color;

uniform sampler2D sTexture;

void main()
{
	Color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	//Color = texture(sTexture, TexCoord);
}