#include "shaderManager.h"
#include <cstring>

ShaderManager shaderManager = ShaderManager();

ShaderManager::ShaderManager() {
}

ShaderManager::~ShaderManager() {
}

bool checkShader(GLuint shader) {
	GLint result = GL_FALSE;
	int infoLogLength;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> shaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderErrorMessage[0]);
		std::cout << "\n" << &shaderErrorMessage[0];
		return false;
	}
	return true;
}

GLuint ShaderManager::loadShader(const char* shaderType, const char* name, const char* shaderCode) {
	if (m_shaders.find(name) != m_shaders.end()) {
		return m_shaders[name];
	}

	GLuint shader;

	if (strcmp(shaderType, "vs") == 0) {
		shader = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (strcmp(shaderType, "fs") == 0) {
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else if (strcmp(shaderType, "cs") == 0) {
		shader = glCreateShader(GL_COMPUTE_SHADER);
	}
	else {
		std::cout << "invalid shaderType: " << shaderType << std::endl;
		return 0;
	}

	std::cout << "Compiling shader: " << name << std::endl;
	char const * sourcePointer = shaderCode;
	glShaderSource(shader, 1, &sourcePointer, NULL);
	glCompileShader(shader);

	if (!checkShader(shader)){
		return 0;
	}

	m_shaders[name] = shader;
	return shader;
}

GLuint ShaderManager::loadShaderFile(const char* filePath) {
	if (m_shaders.find(filePath) != m_shaders.end()) {
		return m_shaders[filePath];
	}
	std::string shaderCode;
	std::ifstream shaderStream(filePath, std::ios::in);
	if (shaderStream.is_open()) {
		std::string Line = "";
		while (std::getline(shaderStream, Line))
			shaderCode += "\n" + Line;
		shaderStream.close();
	}
	else {
		std::cout << "Unable to open: " << filePath << std::endl;
		return 0;
	}

	GLuint shader;

	const char* dot = strrchr(filePath, '.');
	const char* shaderType;
	shaderType = dot + 1;

	if (strcmp(shaderType, "vs") == 0) {
		shader = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (strcmp(shaderType, "fs") == 0) {
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else if (strcmp(shaderType, "cs") == 0) {
		shader = glCreateShader(GL_COMPUTE_SHADER);
	}
	else {
		std::cout << "invalid shaderType: " << shaderType << std::endl;
		return 0;
	}

	std::cout << "Compiling shader: " << filePath << std::endl;
	char const * sourcePointer = shaderCode.c_str();
	glShaderSource(shader, 1, &sourcePointer, NULL);
	glCompileShader(shader);

	if (!checkShader(shader)){
		return 0;
	}

	m_shaders[filePath] = shader;
	return shader;
}