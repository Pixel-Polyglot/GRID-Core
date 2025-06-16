#include "shaderManager.h"

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

GLuint ShaderManager::loadShader(std::string filePath) {
	if (shaders.find(filePath) != shaders.end()) {
		return shaders[filePath];
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
		std::cout << "Unable to open %s\n" << filePath;
		return 0;
	}

	GLuint shader;

	int extIndex = filePath.find_last_of(".");
	std::string shaderType = filePath.substr(extIndex + 1);

	if (shaderType == "vs") {
		shader = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (shaderType == "fs") {
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else if (shaderType == "cs") {
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

	shaders[filePath] = shader;
	return shader;
}