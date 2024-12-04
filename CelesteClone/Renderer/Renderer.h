#pragma once

class Renderer
{
public: 
	unsigned int mVAO;
	unsigned int mVBO;
	unsigned int mEBO;

	Renderer();
	~Renderer();

	const void Draw();

private:
	void InitRenderData();
};