#include <shaderProgram.h>
#include <shaderManager.h>

void ShaderProgram::createSsbo(const char* name, int size) {
    GLuint ssbo;
    glGenBuffers(1, &ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, NULL, GL_DYNAMIC_COPY);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    ssboList[name] = ssbo;
}

void ShaderProgram::bindSsbo(const char* shaderName, const char* value) {
    GLuint location = getSsboLocation(shaderName);
    glShaderStorageBlockBinding(programID, location, bindingIndex);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingIndex, ssboList[value]);
    bindingIndex += 1;
}

void ShaderProgram::setSsboValue(const char* name, int offset, int size, void* data) {
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssboList[name]);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, offset, size, data);
}

void ShaderProgram::getSsboValue(const char* name, int offset, int size, void* data) {
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

    if (m_vertexShader != 0) {
        glAttachShader(program, m_vertexShader);
    }
    if (m_fragmentShader != 0) {
        glAttachShader(program, m_fragmentShader);
    }

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> programErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programErrorMessage[0]);
		std::cout << "\n" << &programErrorMessage[0];
	}

    if (m_vertexShader != 0) {
        glDetachShader(program, m_vertexShader);
    }
    if (m_fragmentShader != 0) {
        glDetachShader(program, m_fragmentShader);
    }

	programID = program;
}

void ComputeProgram::compile() {
    GLint result = GL_FALSE;
	int infoLogLength;

	GLuint program = glCreateProgram();

    if (m_computeShader != 0) {
        glAttachShader(program, m_computeShader);
    }

	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> programErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programErrorMessage[0]);
		std::cout << "\n" << &programErrorMessage[0];
	}

    if (m_computeShader != 0) {
        glDetachShader(program, m_computeShader);
    }

	programID = program;
}

void RenderProgram::setVertexShader(const char* name, const char* shaderCode) {
    m_vertexShader = shaderManager.loadShader("vs", name, shaderCode);
}

void RenderProgram::setVertexShaderFile(const char* source) {
    m_vertexShader = shaderManager.loadShaderFile(source);
}

void RenderProgram::setFragmentShader(const char* name, const char* shaderCode) {
    m_fragmentShader = shaderManager.loadShader("fs", name, shaderCode);
}

void RenderProgram::setFragmentShaderFile(const char* source) {
    m_fragmentShader = shaderManager.loadShaderFile(source);
}

void ComputeProgram::setComputeShader(const char* name, const char* shaderCode) {
    m_computeShader = shaderManager.loadShader("cs", name, shaderCode);
}

void ComputeProgram::setComputeShaderFile(const char* source) {
    m_computeShader = shaderManager.loadShaderFile(source);
}

void ShaderProgram::use() {
    glUseProgram(programID);
    textureIndex = 0;
    bindingIndex = 0;
}

void RenderProgram::setTexture(const char* shaderName, const char* value) {
    setUniform(shaderName, textureIndex);
    glActiveTexture(GL_TEXTURE0 + textureIndex);
    glBindTexture(GL_TEXTURE_2D, textureManager.getTexture(value));
    textureIndex += 1;
}

void ComputeProgram::setImage(const char* shaderName, const char* value, GRID_TEXTUREFORMAT format) {
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

GLuint ShaderProgram::getUniformLocation(const char* shaderName) {
    if (uniformLocations.find(shaderName) == uniformLocations.end()) {
        GLuint location = glGetUniformLocation(programID, shaderName);
        uniformLocations[shaderName] = location;
        return location;
    } else {
        return uniformLocations[shaderName];
    }
}

GLuint ShaderProgram::getSsboLocation(const char* shaderName) {
    if (ssboLocations.find(shaderName) == ssboLocations.end()) {
        GLuint location = glGetProgramResourceIndex(programID, GL_SHADER_STORAGE_BLOCK, shaderName);
        ssboLocations[shaderName] = location;
        return location;
    } else {
        return ssboLocations[shaderName];
    }
}

void ShaderProgram::setUniform(const char* shaderName, bool value) {
    glUniform1i(getUniformLocation(shaderName), (GLint)value);
}

void ShaderProgram::setUniform(const char* shaderName, float value) {
    glUniform1fv(getUniformLocation(shaderName), 1, &value);
}

void ShaderProgram::setUniform(const char* shaderName, int value) {
    glUniform1iv(getUniformLocation(shaderName), 1, &value);
}

void ShaderProgram::setUniform(const char* shaderName, glm::vec2 value) {
    glUniform2fv(getUniformLocation(shaderName), 1, &value[0]);
}

void ShaderProgram::setUniform(const char* shaderName, glm::vec3 value) {
    glUniform3fv(getUniformLocation(shaderName), 1, &value[0]);
}

void ShaderProgram::setUniform(const char* shaderName, glm::vec4 value) {
    glUniform4fv(getUniformLocation(shaderName), 1, &value[0]);
}

void ShaderProgram::setUniform(const char* shaderName, glm::mat3 value) {
    glUniformMatrix3fv(getUniformLocation(shaderName), 1, GL_FALSE, &value[0][0]);
}

void ShaderProgram::setUniform(const char* shaderName, glm::mat4 value) {
    glUniformMatrix4fv(getUniformLocation(shaderName), 1, GL_FALSE, &value[0][0]);
}
