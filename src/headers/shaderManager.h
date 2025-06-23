#pragma once
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

class ShaderManager {
public:
	ShaderManager();
	~ShaderManager();
	GLuint loadShader(std::string shaderType, std::string name, std::string shaderCode);
	GLuint loadShaderFile(std::string filePath);
private:
	std::unordered_map<std::string, GLuint> m_shaders;
};

extern ShaderManager shaderManager;