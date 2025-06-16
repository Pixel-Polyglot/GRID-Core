#include <shaderProgram.h>
#include <shaderManager.h>

void ShaderProgram::createSsbo(std::string name, int size) {
    GLuint ssbo;
    glGenBuffers(1, &ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, NULL, GL_DYNAMIC_COPY);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    ssboList[name] = ssbo;
}

void ShaderProgram::bindSsbo(std::string shaderName, std::string value) {
    GLuint location = getSsboLocation(shaderName);
    glShaderStorageBlockBinding(programID, location, bindingIndex);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingIndex, ssboList[value]);
    bindingIndex += 1;
}

void ShaderProgram::setSsboValue(std::string name, int offset, int size, void* data) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboList[name]);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
}

void ShaderProgram::getSsboValue(std::string name, int offset, int size, void* data) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboList[name]);
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
}

void ComputeProgram::compute(unsigned int numGroupsX, unsigned int numGroupsY, unsigned int numGroupsZ) {
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
    glDispatchCompute(numGroupsX, numGroupsY, numGroupsZ);
    glMemoryBarrier(GL_ALL_BARRIER_BITS);
}

void RenderProgram::compile() {
    GLint result = GL_FALSE;
	int infoLogLength;

	GLuint program = glCreateProgram();

    if (vertexShader != 0) {
        glAttachShader(program, vertexShader);
    }
    if (fragmentShader != 0) {
        glAttachShader(program, fragmentShader);
    }

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> programErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programErrorMessage[0]);
		std::cout << "\n" << &programErrorMessage[0];
	}

    if (vertexShader != 0) {
        glDetachShader(program, vertexShader);
    }
    if (fragmentShader != 0) {
        glDetachShader(program, fragmentShader);
    }

	programID = program;
}

void ComputeProgram::compile() {
    GLint result = GL_FALSE;
	int infoLogLength;

	GLuint program = glCreateProgram();

    if (computeShader != 0) {
        glAttachShader(program, computeShader);
    }

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> programErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programErrorMessage[0]);
		std::cout << "\n" << &programErrorMessage[0];
	}

    if (computeShader != 0) {
        glDetachShader(program, computeShader);
    }

	programID = program;
}

void RenderProgram::setVertexShader(std::string path) {
    vertexShader = shaderManager.loadShader(path);
}

void RenderProgram::setFragmentShader(std::string path) {
    fragmentShader = shaderManager.loadShader(path);
}

void ComputeProgram::setComputeShader(std::string path) {
    computeShader = shaderManager.loadShader(path);
}

void ShaderProgram::use() {
    glUseProgram(programID);
    textureIndex = 0;
    bindingIndex = 0;
}

void RenderProgram::setTexture(std::string shaderName, std::string value) {
    setUniform(shaderName, textureIndex);
    glActiveTexture(GL_TEXTURE0 + textureIndex);
    glBindTexture(GL_TEXTURE_2D, textureManager.getTexture(value));
    textureIndex += 1;
}

void ComputeProgram::setImage(std::string shaderName, std::string value, GRID_TEXTUREFORMAT format) {
    int imageType;
    switch (format) {
        case GRID_TEXTUREFORMAT::R8:
            imageType = GL_R8;
            break;        
        case GRID_TEXTUREFORMAT::R8UI:
            imageType = GL_R8UI;
            break;
        case GRID_TEXTUREFORMAT::R16UI:
            imageType = GL_R16UI;
            break;
        case GRID_TEXTUREFORMAT::RGBA8:
            imageType = GL_RGBA8;
            break;
        case GRID_TEXTUREFORMAT::RGBA8UI:
            imageType = GL_RGBA8UI;
            break;
        case GRID_TEXTUREFORMAT::RGBA16F:
            imageType = GL_RGBA16F;
            break;
        case GRID_TEXTUREFORMAT::R16F:
            imageType = GL_R16F;
            break;
        case GRID_TEXTUREFORMAT::RGBA16UI:
            imageType = GL_RGBA16UI;
            break;
        case GRID_TEXTUREFORMAT::RGBA32F:
            imageType = GL_RGBA32F;
            break;
        case GRID_TEXTUREFORMAT::R32UI:
            imageType = GL_R32UI;
            break;
        case GRID_TEXTUREFORMAT::RGBA32UI:
            imageType = GL_RGBA32UI;
            break;
        default:
            std::cout << "Invalid format " << value << std::endl;
            break;
    }

    setUniform(shaderName, textureIndex);
    glActiveTexture(GL_TEXTURE0 + textureIndex);
    glBindImageTexture(textureIndex, textureManager.getTexture(value), 0, 0, 0, GL_READ_WRITE, imageType);
    textureIndex += 1;
}

GLuint ShaderProgram::getUniformLocation(std::string shaderName) {
    if (uniformLocations.find(shaderName) == uniformLocations.end()) {
        GLuint location = glGetUniformLocation(programID, shaderName.c_str());
        uniformLocations[shaderName] = location;
        return location;
    } else {
        return uniformLocations[shaderName];
    }
}

GLuint ShaderProgram::getSsboLocation(std::string shaderName) {
    if (ssboLocations.find(shaderName) == ssboLocations.end()) {
        GLuint location = glGetProgramResourceIndex(programID, GL_SHADER_STORAGE_BLOCK, shaderName.c_str());
        ssboLocations[shaderName] = location;
        return location;
    } else {
        return ssboLocations[shaderName];
    }
}

void ShaderProgram::setUniform(std::string shaderName, bool value) {
    glUniform1i(getUniformLocation(shaderName), (GLint)value);
}

void ShaderProgram::setUniform(std::string shaderName, float value) {
    glUniform1fv(getUniformLocation(shaderName), 1, &value);
}

void ShaderProgram::setUniform(std::string shaderName, int value) {
    glUniform1iv(getUniformLocation(shaderName), 1, &value);
}

void ShaderProgram::setUniform(std::string shaderName, glm::vec2 value) {
    glUniform2fv(getUniformLocation(shaderName), 1, &value[0]);
}

void ShaderProgram::setUniform(std::string shaderName, glm::vec3 value) {
    glUniform3fv(getUniformLocation(shaderName), 1, &value[0]);
}

void ShaderProgram::setUniform(std::string shaderName, glm::vec4 value) {
    glUniform4fv(getUniformLocation(shaderName), 1, &value[0]);
}

void ShaderProgram::setUniform(std::string shaderName, glm::mat3 value) {
    glUniformMatrix3fv(getUniformLocation(shaderName), 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::setUniform(std::string shaderName, glm::mat4 value) {
    glUniformMatrix4fv(getUniformLocation(shaderName), 1, GL_FALSE, &value[0][0]);
}
