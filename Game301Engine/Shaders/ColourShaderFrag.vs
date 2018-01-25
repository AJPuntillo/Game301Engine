#version 330 core

out vec4 FragColour;

uniform vec3 diffuse_colour;

void main()
{
	FragColour = vec4(diffuse_colour, 1.0);
}