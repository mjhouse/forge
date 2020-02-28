#version 330

uniform mat4 mvp;

uniform mat4 modelView;

uniform mat4 modelMatrix;

uniform vec3 eyePosition;

in vec3 vertexPosition;

in vec3 vertexNormal;

// the world-space position of the triggering vertex
out vec3 viewPosition;

// a vector from the vertex to the camera position
out vec3 cameraVector;

void main(void)
{
    gl_Position = mvp * vec4(vertexPosition, 1);

    viewPosition = (modelView * vec4(vertexPosition,1)).xyz;
    cameraVector = normalize(eyePosition - viewPosition);
    vec3 worldNormal = normalize(mat3(modelMatrix) * vertexNormal);
}