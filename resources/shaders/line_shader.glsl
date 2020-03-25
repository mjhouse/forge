#version 330 core

uniform vec3 surfaceColor;

out vec4 color;

void main()
{	
	color = vec4(surfaceColor,1);
}