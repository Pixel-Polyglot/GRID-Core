#include "GRID/GRID_shaderProgram.h"
#include <shaderProgram.h>
#include <glm/glm.hpp>
#include <glm_convert.h>

void GRID_ShaderProgram::use() {
    shaderProgram->use();
}

void GRID_ShaderProgram::setUniform(std::string shaderName, bool value) {
    shaderProgram->setUniform(shaderName, value);
}

void GRID_ShaderProgram::setUniform(std::string shaderName, float value) {
    shaderProgram->setUniform(shaderName, value);
}

void GRID_ShaderProgram::setUniform(std::string shaderName, int value) {
    shaderProgram->setUniform(shaderName, value);
}

void GRID_ShaderProgram::setUniform(std::string shaderName, GRID_Vec2f value) {
    shaderProgram->setUniform(shaderName, toGLM(value));
}

void GRID_ShaderProgram::setUniform(std::string shaderName, GRID_Vec3f value) {
    shaderProgram->setUniform(shaderName, toGLM(value));
}

void GRID_ShaderProgram::setUniform(std::string shaderName, GRID_Vec4f value) {
    shaderProgram->setUniform(shaderName, toGLM(value));
}

void GRID_ShaderProgram::setUniform(std::string shaderName, GRID_Mat3 value) {
    shaderProgram->setUniform(shaderName, toGLM(value));
}

void GRID_ShaderProgram::setUniform(std::string shaderName, GRID_Mat4 value){
    shaderProgram->setUniform(shaderName, toGLM(value));
}

void GRID_ShaderProgram::createSsbo(std::string name, int size){
    shaderProgram->createSsbo(name, size);
}

void GRID_ShaderProgram::bindSsbo(std::string shaderName, std::string value) {
    shaderProgram->bindSsbo(shaderName, value);
}

void GRID_ShaderProgram::setSsboValue(std::string name, int offset, int size, void* data) {
    shaderProgram->setSsboValue(name, offset, size, data);
}

void GRID_ShaderProgram::getSsboValue(std::string name, int offset, int size, void* data) {
    shaderProgram->getSsboValue(name, offset, size, data);
}

GRID_RenderProgram::GRID_RenderProgram() {
    shaderProgram = (ShaderProgram*)(new RenderProgram());
}

GRID_RenderProgram::~GRID_RenderProgram() {
    delete (RenderProgram*)shaderProgram;
}

void GRID_RenderProgram::compile() {
    ((RenderProgram*)shaderProgram)->compile();
}

void GRID_RenderProgram::setVertexShader(std::string source) {
    ((RenderProgram*)shaderProgram)->setVertexShader(source);
}

void GRID_RenderProgram::setFragmentShader(std::string source) {
    ((RenderProgram*)shaderProgram)->setFragmentShader(source);
}

void GRID_RenderProgram::setTexture(std::string texture, std::string value) {
    ((RenderProgram*)shaderProgram)->setTexture(texture, value);
}

GRID_ComputeProgram::GRID_ComputeProgram() {
    shaderProgram = (ShaderProgram*)(new ComputeProgram());
}

GRID_ComputeProgram::~GRID_ComputeProgram() {
    delete (ComputeProgram*)shaderProgram;
}

void GRID_ComputeProgram::compile() {
    ((ComputeProgram*)shaderProgram)->compile();
}

void GRID_ComputeProgram::compute(unsigned int numGroupsX, unsigned int numGroupsY, unsigned int numGroupsZ){
    ((ComputeProgram*)shaderProgram)->compute(numGroupsX, numGroupsY, numGroupsZ);
}

void GRID_ComputeProgram::setComputeShader(std::string source) {
    ((ComputeProgram*)shaderProgram)->setComputeShader(source);
}

void GRID_ComputeProgram::setImage(std::string texture, std::string value, GRID_TEXTUREFORMAT format) {
    ((ComputeProgram*)shaderProgram)->setImage(texture, value, format);
}