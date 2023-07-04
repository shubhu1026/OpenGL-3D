#pragma once

#include <vector>
#include <glad/glad.h>

class IndexBuffer
{
public:
	GLuint ID;
	IndexBuffer(std::vector<GLuint>& indices);

	void Bind();
	void UnBind();
	void Delete();
};