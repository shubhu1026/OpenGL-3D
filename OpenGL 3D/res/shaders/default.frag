#version 330 core

out vec4 FragColor;

in vec3 currPosition;
in vec3 normal;
in vec3 color;
in vec2 texCoord;

uniform sampler2D diffuse0;
uniform sampler2D specular0;

uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 PointLight()
{
	vec3 lightVec = lightPos - currPosition;
	float dist = length(lightVec);
	float a = 3.0;
	float b = 0.7;
	float intensity = 1.0f / (a * dist * dist + b * dist + 1.0f);


	// Ambient Lighting
	float ambient = 0.2f;

	// Diffuse Lighting
	vec3 Normal = normalize(normal);
	vec3 lightDirection = normalize(lightVec);
	float diffuse = max(dot(Normal, lightDirection), 0.0f);

	// Diffuse Lighting
	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos - currPosition);
	vec3 reflectionDir = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDir), 0.0f), 16);
	float specular = specularLight * specAmount;

	return (texture(diffuse0,texCoord) * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
}

vec4 DirectionalLight()
{
	// Ambient Lighting
	float ambient = 0.2f;

	// Diffuse Lighting
	vec3 Normal = normalize(normal);
	vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
	float diffuse = max(dot(Normal, lightDirection), 0.0f);

	// Diffuse Lighting
	float specularLight = 0.5f;
	vec3 viewDirection = normalize(camPos - currPosition);
	vec3 reflectionDir = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDir), 0.0f), 16);
	float specular = specularLight * specAmount;

	return (texture(diffuse0,texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * lightColor;
}

vec4 SpotLight()
{
	float outerCone = 0.90f;
	float innerCone = 0.95f;

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

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float intensity = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(diffuse0,texCoord) * (diffuse * intensity + ambient) + texture(specular0, texCoord).r * specular * intensity) * lightColor;
}

void main()
{
	//FragColor = DirectionalLight();
	//FragColor = PointLight();
	FragColor = SpotLight();
}