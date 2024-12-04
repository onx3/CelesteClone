#include "Shader.h"
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char * vertexPath, const char * fragmentPath)
{
	std::string vertexCode = ReadFile(vertexPath); // Store in a local variable
	std::string fragmentCode = ReadFile(fragmentPath); // Store in a local variable

	const char * vShaderCode = vertexCode.c_str(); // Pointer to the local variable's data
	const char * fShaderCode = fragmentCode.c_str(); // Pointer to the local variable's data

	unsigned int vertex;
	unsigned int fragment;

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	CheckCompileErrors(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	CheckCompileErrors(fragment, "fragment");

	mID = glCreateProgram();
	glAttachShader(mID, vertex);
	glAttachShader(mID, fragment);
	glLinkProgram(mID);
	CheckCompileErrors(mID, "PROGRAM");

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

//----------------------------------------------------------------------------------------------------------------------------

const void Shader::Use()
{
	glUseProgram(mID);
}

//----------------------------------------------------------------------------------------------------------------------------

const void Shader::SetBool(const std::string & name, bool value)
{
	glUniform1i(glGetUniformLocation(mID, name.c_str()), (int)value);
}

//----------------------------------------------------------------------------------------------------------------------------

const void Shader::SetInt(const std::string & name, int value)
{
	glUniform1i(glGetUniformLocation(mID, name.c_str()), value);
}

//----------------------------------------------------------------------------------------------------------------------------

const void Shader::SetFloat(const std::string & name, float value)
{
	glUniform1i(glGetUniformLocation(mID, name.c_str()), (int)value);
}

//----------------------------------------------------------------------------------------------------------------------------

std::string Shader::ReadFile(const char * filePath)
{
	std::ifstream file(filePath);
	if (!file)
	{
		std::cerr << "Failed to open shader file: " << filePath << std::endl;
		return "";
	}
	std::stringstream stream;
	stream << file.rdbuf();
	std::string code = stream.str();

	// Debug: Print the shader code
	std::cout << "Shader code from " << filePath << ":\n" << code << std::endl;

	return code;
}


//----------------------------------------------------------------------------------------------------------------------------

void Shader::CheckCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << type << " shader compilation error: " << infoLog << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "Program linking error: " << infoLog << std::endl;
		}
	}
}


//----------------------------------------------------------------------------------------------------------------------------
// EOF
//----------------------------------------------------------------------------------------------------------------------------