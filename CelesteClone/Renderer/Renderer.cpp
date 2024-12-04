#pragma once
#include "Renderer.h"
#include <glad/glad.h>

Renderer::Renderer()
{
	InitRenderData();
}

//----------------------------------------------------------------------------------------------------------------------------

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &mVAO);
	glDeleteBuffers(1, &mVBO);
	glDeleteBuffers(1, &mEBO);
}

//----------------------------------------------------------------------------------------------------------------------------

void Renderer::InitRenderData()
{
	float vertices[] = {
	-0.5f, -0.5f, 0.0f,  1.0f, 1.0f, 0.0f, // Bottom-left: Green
	 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Bottom-right: Green
	 0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 1.0f, // Top-right: Green
	-0.5f,  0.5f, 0.0f,  0.0f, 1.0f, 0.0f  // Top-left: Green
	};
	unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);
	glGenBuffers(1, &mEBO);

	glBindVertexArray(mVAO);

	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);          // Position
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float))); // Color
	glEnableVertexAttribArray(1);
}

//----------------------------------------------------------------------------------------------------------------------------

const void Renderer::Draw()
{
	glBindVertexArray(mVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

//----------------------------------------------------------------------------------------------------------------------------
// EOF
//----------------------------------------------------------------------------------------------------------------------------