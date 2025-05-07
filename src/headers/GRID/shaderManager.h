#pragma once
#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>

class ShaderManager {
public:
	ShaderManager();
	~ShaderManager();
	GLuint loadShader(std::string filePath);
private:
	std::unordered_map<std::string, GLuint> shaders;
};

extern ShaderManager shaderManager;