#pragma once
// #include <glad/glad.h>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <textureManager.h>
#include <GRID/GRID_tiffFormat.h>

class ShaderProgram {
public:
    virtual ~ShaderProgram() = default;

    void use();
    virtual void compile() = 0;

    void setUniform(std::string shaderName, bool value);
    void setUniform(std::string shaderName, float value);
    void setUniform(std::string shaderName, int value);
    void setUniform(std::string shaderName, glm::vec2 value);
    void setUniform(std::string shaderName, glm::vec3 value);
    void setUniform(std::string shaderName, glm::vec4 value);
    void setUniform(std::string shaderName, glm::mat3 value);
    void setUniform(std::string shaderName, glm::mat4 value);

    void createSsbo(std::string name, int size);
    void bindSsbo(std::string shaderName, std::string value);
    void setSsboValue(std::string name, int offset, int size, void* data);
    void getSsboValue(std::string name, int offset, int size, void* data);


protected:
    GLuint programID;
    std::unordered_map<std::string, GLuint> uniformLocations;
    std::unordered_map<std::string, GLuint> ssboList;
    std::unordered_map<std::string, GLuint> ssboLocations;
    GLuint getUniformLocation(std::string shaderName);
    GLuint getSsboLocation(std::string shaderName);
    GLint textureIndex = 0;
    GLuint bindingIndex = 0;
};

class RenderProgram : public ShaderProgram {
public:
    void compile();

    void setVertexShader(std::string source);
    void setFragmentShader(std::string source);

    void setTexture(std::string texture, std::string value);

private:
    GLuint vertexShader = 0;
    GLuint fragmentShader = 0;
};

class ComputeProgram : public ShaderProgram {
public:
    void compile();

    void compute(unsigned int numGroupsX = 32, unsigned int numGroupsY = 32, unsigned int numGroupsZ = 1);
    void setComputeShader(std::string source);
    void setImage(std::string texture, std::string value, GRID_TEXTUREFORMAT format);

private:
    GLuint computeShader = 0;
};