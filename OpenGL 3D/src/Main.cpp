#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Camera.h"

const unsigned int width = 800;
const unsigned int height = 800;

GLfloat vertices[] =
{ //    COORDINATES				  COLORS			 TexCoord 
	-0.5f, 0.0f,  0.5f,		0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	-0.5f, 0.0f, -0.5f,		0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.5f, 0.0f, -0.5f,		0.83f, 0.70f, 0.44f,	0.0f, 0.0f,
	 0.5f, 0.0f,  0.5f,		0.83f, 0.70f, 0.44f,	5.0f, 0.0f,
	 0.0f, 0.8f,  0.0f,		0.92f, 0.86f, 0.76f,	2.5f, 5.0f
};	

GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

int main()
{
	glfwInit();

	// letting glfw know opengl version we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Creates window
	GLFWwindow* window = glfwCreateWindow(width, height, "My Window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	// sets the viewport to our window width and height
	glViewport(0, 0, width, height);

	// Generates shader object using shaders deafult.vert and default.frag
	Shader shaderProgram("res/shaders/default.vert", "res/shaders/default.frag");

	// Generates vertex array object and bind it
	VertexArray VAO;
	VAO.Bind();

	// Generates vertex buffer object and links it to vertices
	VertexBuffer VBO(vertices, sizeof(vertices));
	// Generates element buffer object and links it to indices
	IndexBuffer IBO(indices, sizeof(indices));

	// link VBO to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, 8 * sizeof(float), (void*)0);
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	VAO.LinkAttrib(VBO, 2, 2, GL_FLOAT, 8 * sizeof(float), (void*)(6 * sizeof(float)));

	// unbinding all buffers to prevent accidently modifying them
	VAO.UnBind();
	VBO.UnBind();
	IBO.UnBind();

	// Texture
	Texture tinyDevil("res/textures/brick.png", GL_TEXTURE_2D, 0, GL_RGB, GL_UNSIGNED_BYTE);
	tinyDevil.TexUnit(shaderProgram, "tex0", 0);

	// enables depth buffer
	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

		camera.Inputs(window);
		camera.Matrix(45.0f, 0.1f, 100.0f, shaderProgram, "camMatrix");

		// initialising mvp matrices as identity matrices
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 proj = glm::mat4(1.0f);

		tinyDevil.Bind();

		VAO.Bind();

		glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	VAO.Delete();
	VBO.Delete();
	IBO.Delete();
	tinyDevil.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}