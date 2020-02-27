#version 150

uniform mat4 mvp;

in vec3 vertexPosition;

void main(void)
{
    gl_Position = mvp * vec4(vertexPosition, 1);
}