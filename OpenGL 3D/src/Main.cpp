#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3  , 0.0f,   // Lower left Corner
	 0.5f, -0.5f * float(sqrt(3)) / 3  , 0.0f,   // Lower Right Corner
	 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper Corner

	 -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner Left
	  0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner Right
	  0.0f,    -0.5f * float(sqrt(3)) / 3, 0.0f  // Inner Down
};

GLuint indices[] =
{
	0, 3, 5,  // Lower Left Triangle
	3, 2, 4,  // Lower Right Triangle
	5, 4, 1,  // Upper Triangle
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
	VAO.LinkVertexBuffer(VBO, 0);

	// unbinding all buffers to prevent accidently modifying them
	VAO.UnBind();
	VBO.UnBind();
	IBO.UnBind();

	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();

		VAO.Bind();

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	VAO.Delete();
	VBO.Delete();
	IBO.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}