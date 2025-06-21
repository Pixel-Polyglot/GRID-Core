#pragma once
#include <unordered_map>
#include <glm/glm.hpp>
#include <textureManager.h>
#include <GRID/GRID_tiffFormat.h>

class ShaderProgram {
public:
    virtual ~ShaderProgram() = default;

    void use();
    virtual void compile() = 0;

    void setUniform(const char* shaderName, bool value);
    void setUniform(const char* shaderName, float value);
    void setUniform(const char* shaderName, int value);
    void setUniform(const char* shaderName, glm::vec2 value);
    void setUniform(const char* shaderName, glm::vec3 value);
    void setUniform(const char* shaderName, glm::vec4 value);
    void setUniform(const char* shaderName, glm::mat3 value);
    void setUniform(const char* shaderName, glm::mat4 value);

    void createSsbo(const char* name, int size);
    void bindSsbo(const char* shaderName, const char* value);
    void setSsboValue(const char* name, int offset, int size, void* data);
    void getSsboValue(const char* name, int offset, int size, void* data);


protected:
    GLuint programID;
    std::unordered_map<const char*, GLuint> uniformLocations;
    std::unordered_map<const char*, GLuint> ssboList;
    std::unordered_map<const char*, GLuint> ssboLocations;
    GLuint getUniformLocation(const char* shaderName);
    GLuint getSsboLocation(const char* shaderName);
    GLint textureIndex = 0;
    GLuint bindingIndex = 0;
};

class RenderProgram : public ShaderProgram {
public:
    void compile();

    void setVertexShader(const char* name, const char* shaderCode);
    void setVertexShaderFile(const char* source);
    void setFragmentShader(const char* name, const char* shaderCode);
    void setFragmentShaderFile(const char* source);

    void setTexture(const char* texture, const char* value);

private:
    GLuint m_vertexShader = 0;
    GLuint m_fragmentShader = 0;
};

class ComputeProgram : public ShaderProgram {
public:
    void compile();

    void compute(unsigned int numGroupsX = 32, unsigned int numGroupsY = 32, unsigned int numGroupsZ = 1);
    void setComputeShader(const char* name, const char* shaderCode);
    void setComputeShaderFile(const char* source);
    void setImage(const char* texture, const char* value, GRID_TEXTUREFORMAT format);

private:
    GLuint m_computeShader = 0;
};