#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 normal;
in vec3 currPosition;

uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPosition;
uniform vec3 lightPos;

void main()
{
	vec3 Normal = normalize(normal);
	vec3 lightDirection = normalize(lightPos - currPosition);

	float diffuse = max(dot(Normal, lightDirection), 0.0f);

	FragColor = texture(tex0,texCoord) * lightColor * diffuse;
}