#pragma once

#include "export.h"
#include <string>
#include "GRID_math.h"
#include "GRID_textureFormat.h"

class ShaderProgram;

class EXPORT GRID_ShaderProgram {
public:
    void use();
    virtual void compile() = 0;

    void setUniform(std::string shaderName, bool value);
    void setUniform(std::string shaderName, float value);
    void setUniform(std::string shaderName, int value);
    void setUniform(std::string shaderName, GRID_Vec2f value);
    void setUniform(std::string shaderName, GRID_Vec3f value);
    void setUniform(std::string shaderName, GRID_Vec4f value);
    void setUniform(std::string shaderName, GRID_Mat3 value);
    void setUniform(std::string shaderName, GRID_Mat4 value);

    void createSsbo(std::string name, int size);
    void bindSsbo(std::string shaderName, std::string value);
    void setSsboValue(std::string name, int offset, int size, void* data);
    void getSsboValue(std::string name, int offset, int size, void* data);

protected:
    ShaderProgram* shaderProgram;
};

class EXPORT GRID_RenderProgram : public GRID_ShaderProgram {
public:
    GRID_RenderProgram();
    ~GRID_RenderProgram();

    void compile();

    void setVertexShader(std::string source);
    void setFragmentShader(std::string source);

    void setTexture(std::string texture, std::string value);
};

class EXPORT GRID_ComputeProgram : public GRID_ShaderProgram {
public:
    GRID_ComputeProgram();
    ~GRID_ComputeProgram();

    void compile();

    void compute(unsigned int numGroupsX = 32, unsigned int numGroupsY = 32, unsigned int numGroupsZ = 1);
    void setComputeShader(std::string source);
    void setImage(std::string texture, std::string value, GRID_TEXTUREFORMAT format);
};