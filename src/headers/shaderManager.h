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
	GLuint loadShader(const char* shaderType, const char* name, const char* shaderCode);
	GLuint loadShaderFile(const char* filePath);
private:
	std::unordered_map<const char*, GLuint> m_shaders;
};

extern ShaderManager shaderManager;