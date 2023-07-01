#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 texCoord;
in vec3 normal;
in vec3 currPosition;

uniform sampler2D tex0;
uniform sampler2D tex1;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
	// Ambient Lighting
	float ambient = 0.2f;

	// Diffuse Lighting
	vec3 Normal = normalize(normal);
	vec3 lightDirection = normalize(lightPos - currPosition);
	float diffuse = max(dot(Normal, lightDirection), 0.0f);

	// Diffuse Lighting
	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos - currPosition);
	vec3 reflectionDir = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDir), 0.0f), 16);
	float specular = specularLight * specAmount;

	FragColor = texture(tex0,texCoord) * lightColor * (diffuse + ambient) + texture(tex1, texCoord).r * specular;
}