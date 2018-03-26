#version 450 core
in vec4 interpolatedVertexColor;
out vec4 outColor;
void main()
{
	outColor = interpolatedVertexColor;
};

