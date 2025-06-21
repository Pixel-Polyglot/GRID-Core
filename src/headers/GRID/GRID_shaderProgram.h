#pragma once

#include "export.h"
#include "GRID_math.h"
#include "GRID_textureFormat.h"

class ShaderProgram;

class EXPORT GRID_ShaderProgram {
public:
    void use();
    virtual void compile() = 0;

    void setUniform(const char* shaderName, bool value);
    void setUniform(const char* shaderName, float value);
    void setUniform(const char* shaderName, int value);
    void setUniform(const char* shaderName, GRID_Vec2f value);
    void setUniform(const char* shaderName, GRID_Vec3f value);
    void setUniform(const char* shaderName, GRID_Vec4f value);
    void setUniform(const char* shaderName, GRID_Mat3 value);
    void setUniform(const char* shaderName, GRID_Mat4 value);

    void createSsbo(const char* name, int size);
    void bindSsbo(const char* shaderName, const char* value);
    void setSsboValue(const char* name, int offset, int size, void* data);
    void getSsboValue(const char* name, int offset, int size, void* data);

protected:
    ShaderProgram* shaderProgram;
};

class EXPORT GRID_ComputeProgram : public GRID_ShaderProgram {
public:
    GRID_ComputeProgram();
    ~GRID_ComputeProgram();

    void compile();

    void compute(unsigned int numGroupsX = 32, unsigned int numGroupsY = 32, unsigned int numGroupsZ = 1);
    void setComputeShader(const char* name, const char* shaderCode);
    void setComputeShaderFile(const char* source);
    void setImage(const char* texture, const char* value, GRID_TEXTUREFORMAT format);
};