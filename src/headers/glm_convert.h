#pragma once

#include <glm/glm.hpp>
#include <GRID/GRID_math.h>

glm::vec2 toGLM(const GRID_Vec2f& vec);
glm::ivec2 toGLM(const GRID_Vec2i& vec);
glm::vec3 toGLM(const GRID_Vec3f& vec);
glm::ivec3 toGLM(const GRID_Vec3i& vec);
glm::vec4 toGLM(const GRID_Vec4f& vec);
glm::ivec4 toGLM(const GRID_Vec4i& vec);

glm::mat2 toGLM(const GRID_Mat2& mat);
glm::mat3 toGLM(const GRID_Mat3& mat); 
glm::mat4 toGLM(const GRID_Mat4& mat); 

GRID_Vec2f fromGLM(const glm::vec2& vec);
GRID_Vec2i fromGLM(const glm::ivec2& vec);
GRID_Vec3f fromGLM(const glm::vec3& vec);
GRID_Vec3i fromGLM(const glm::ivec3& vec);
GRID_Vec4f fromGLM(const glm::vec4& vec);
GRID_Vec4i fromGLM(const glm::ivec4& vec);

GRID_Mat2 fromGLM(const glm::mat2& mat);
GRID_Mat3 fromGLM(const glm::mat3& mat);
GRID_Mat4 fromGLM(const glm::mat4& mat);

bool fromGLM(const bool& val);
float fromGLM(const float& val);
int fromGLM(const int& val);