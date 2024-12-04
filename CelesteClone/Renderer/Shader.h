#pragma once

#include <glad/glad.h>
#include <string>

class Shader
{
public: 
	unsigned int mID;

	Shader(const char * vertexPath, const char * fragmentPath);

	const void Use();

	const void SetBool(const std::string & name, bool value);
	const void SetInt(const std::string & name, int value);
	const void SetFloat(const std::string & name, float value);

private:
	std::string ReadFile(const char * filePath);
	void CheckCompileErrors(unsigned int shader, std::string type);
};