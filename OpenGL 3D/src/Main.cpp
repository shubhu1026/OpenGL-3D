#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"

GLfloat vertices[] =
{
	//	COORDINATES				COLORS
	-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,	// Lower Left Corner
	-0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 1.0f,	// Upper Left Corner
	 0.5f,  0.5f, 0.0f,		0.0f, 0.0f, 1.0f,	1.0f, 1.0f,	// Upper Right Corner
	 0.5f, -0.5f, 0.0f,		1.0f, 1.0f, 1.0f,	1.0f, 0.0f	// Lower Right Corner
};

GLuint indices[] =
{
	0, 2, 1,  //Upper triangle
	0, 3, 2   //Lower triangle
};

int main()
{
	glfwInit();

	// letting glfw know opengl version we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Creates window
	GLFWwindow* window = glfwCreateWindow(800, 800, "My Window", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	gladLoadGL();

	// sets the viewport to our window width and height
	glViewport(0, 0, 800, 800);

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

	// Gets ID of uniform called "scale"
	GLuint uniID = glGetUniformLocation(shaderProgram.ID, "scale");

	// Texture
	Texture tinyDevil("res/textures/devil.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
	tinyDevil.TexUnit(shaderProgram, "tex0", 0);

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();
		glUniform1f(uniID, 0.5f);

		tinyDevil.Bind();

		VAO.Bind();

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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