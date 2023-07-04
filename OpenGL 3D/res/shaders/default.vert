#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec3 currPosition;
out vec3 normal;
out vec3 color;
out vec2 texCoord;

uniform float scale;
uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
	currPosition = vec3(model * vec4(aPos, 1.0f));
	normal = aNormal;
	color = aColor;
	texCoord = aTex;

	gl_Position = camMatrix * vec4(currPosition, 1.0);
}