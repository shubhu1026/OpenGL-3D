#pragma once

#include <glad/glad.h>
#include "VertexBuffer.h"

class VertexArray
{
public:
	GLuint ID;
	VertexArray();

	void LinkVertexBuffer(VertexBuffer VBO, GLuint layout);
	void Bind();
	void UnBind();
	void Delete();
};