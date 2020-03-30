#version 330 core

uniform vec3 surfaceColor;

out vec4 color;

// the world-space position of the triggering 
// vertex
in vec3 viewPosition;

// a vector from the triggering vertex to the 
// camera position
in vec3 cameraVector;

void main()
{
	vec3 xTangent = dFdx( viewPosition );
	vec3 yTangent = dFdy( viewPosition );

	// normal for this entire face (all fragments 
	// facing the same direction)
	vec3 faceNormal = normalize( cross( xTangent, yTangent ) );

	// calculate direction relative to the camera
	float direction = dot(faceNormal,cameraVector);
	float faceAngle = acos(direction);
	
	// adjust and constrain the angle so that we get 
	// varying per-face shading
	float angle = 1/clamp(faceAngle,1,3);
	color = vec4(surfaceColor * angle,1);
}