#version 330 core

layout (location = 0) in vec4 vertex; // vec4 vertex -> (vec2 position, vec2 texCoords)

out vec2 texCoords;

uniform mat4 modelMatrix;
uniform mat4 orthoMatrix;

void main()
{
	texCoords = vertex.zw;
	gl_Position = orthoMatrix * modelMatrix * vec4(vertex.xy, 0.0f, 1.0f);
}