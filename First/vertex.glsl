#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertexColor;

out vec4 interpolatedVertexColor;

void main()
{
	interpolatedVertexColor = vec4(vertexColor, 1);
	gl_Position = vec4(position.x, position.y, position.z, 2.0);
}