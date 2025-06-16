#include <GRID/GRID_math.h>

#include <glm/glm.hpp>

glm::vec2 toGLM(const GRID_Vec2f& vec) { return glm::vec2(vec.x, vec.y); }
glm::ivec2 toGLM(const GRID_Vec2i& vec) { return glm::ivec2(vec.x, vec.y); }
glm::vec3 toGLM(const GRID_Vec3f& vec) { return glm::vec3(vec.x, vec.y, vec.z); }
glm::ivec3 toGLM(const GRID_Vec3i& vec) { return glm::ivec3(vec.x, vec.y, vec.z); }
glm::vec4 toGLM(const GRID_Vec4f& vec) { return glm::vec4(vec.x, vec.y, vec.z, vec.w); }
glm::ivec4 toGLM(const GRID_Vec4i& vec) { return glm::ivec4(vec.x, vec.y, vec.z, vec.w); }

glm::mat2 toGLM(const GRID_Mat2& mat) { return glm::mat2(mat[0][0], mat[0][1], mat[1][0], mat[1][1]); }
glm::mat3 toGLM(const GRID_Mat3& mat) { return glm::mat3(mat[0][0], mat[0][1], mat[0][2], mat[1][0], mat[1][1], mat[1][2], mat[2][0], mat[2][1], mat[2][2]); }
glm::mat4 toGLM(const GRID_Mat4& mat) { return glm::mat4(mat[0][0], mat[0][1], mat[0][2], mat[0][3], mat[1][0], mat[1][1], mat[1][2], mat[1][3], mat[2][0], mat[2][1], mat[2][2], mat[2][3], mat[3][0], mat[3][1], mat[3][2], mat[3][3]); }

GRID_Vec2f fromGLM(const glm::vec2& vec) { return GRID_Vec2f(vec.x, vec.y); }
GRID_Vec2i fromGLM(const glm::ivec2& vec) { return GRID_Vec2i(vec.x, vec.y); }
GRID_Vec3f fromGLM(const glm::vec3& vec) { return GRID_Vec3f(vec.x, vec.y, vec.z); }
GRID_Vec3i fromGLM(const glm::ivec3& vec) { return GRID_Vec3i(vec.x, vec.y, vec.z); }
GRID_Vec4f fromGLM(const glm::vec4& vec) { return GRID_Vec4f(vec.x, vec.y, vec.z, vec.w); }
GRID_Vec4i fromGLM(const glm::ivec4& vec) { return GRID_Vec4i(vec.x, vec.y, vec.z, vec.w); }

GRID_Mat2 fromGLM(const glm::mat2& mat) { return GRID_Mat2(mat[0][0], mat[0][1], mat[1][0], mat[1][1]); }
GRID_Mat3 fromGLM(const glm::mat3& mat) { return GRID_Mat3(mat[0][0], mat[0][1], mat[0][2], mat[1][0], mat[1][1], mat[1][2], mat[2][0], mat[2][1], mat[2][2]); }
GRID_Mat4 fromGLM(const glm::mat4& mat) { return GRID_Mat4(mat[0][0], mat[0][1], mat[0][2], mat[0][3], mat[1][0], mat[1][1], mat[1][2], mat[1][3], mat[2][0], mat[2][1], mat[2][2], mat[2][3], mat[3][0], mat[3][1], mat[3][2], mat[3][3]); }

bool fromGLM(const bool& val) { return val; }
float fromGLM(const float& val) { return val; }
int fromGLM(const int& val) { return val; }

#define OP(selfType, op) \
auto selfType::operator##op(const selfType& other) const -> decltype(fromGLM(toGLM(*this) op toGLM(other))) { \
    return fromGLM(toGLM(*this) op toGLM(other)); \
}

#define OP_REF(selfType, op) \
auto selfType::operator##op(const selfType& other) -> decltype(fromGLM(toGLM(*this) op toGLM(other))) { \
    *this = fromGLM(toGLM(*this) op toGLM(other)); \
    return *this; \
}

#define OPS(selfType) \
OP(selfType, +) \
OP(selfType, -) \
OP(selfType, *) \
OP(selfType, /) \
OP_REF(selfType, +=) \
OP_REF(selfType, -=) \
OP_REF(selfType, *=) \
OP_REF(selfType, /=) \
OP(selfType, ==) \
OP(selfType, !=)

#define FUNC1(selfType, func) \
auto selfType::func() const -> decltype(fromGLM(glm::func(toGLM(*this)))) { \
    return fromGLM(glm::func(toGLM(*this))); \
}

#define FUNC2(selfType, func, argType) \
auto selfType::func(const argType& other) const -> decltype(fromGLM(glm::func(toGLM(*this), toGLM(other)))) { \
    return fromGLM(glm::func(toGLM(*this), toGLM(other))); \
}

#define VEC_FUNCS(selfType) \
FUNC1(selfType, length) \
FUNC2(selfType, distance, selfType) \
FUNC1(selfType, normalize) \
FUNC2(selfType, dot, selfType) \
FUNC2(selfType, outerProduct, selfType)

#define IVEC_FUNCS(selfType) \
FUNC1(selfType, normalize)

#define MATRIX_FUNCS(selfType) \
FUNC1(selfType, determinant) \
FUNC1(selfType, inverse) \
FUNC1(selfType, transpose) \
FUNC2(selfType, matrixCompMult, selfType)

#define VECS \
OPS(GRID_Vec2i) \
IVEC_FUNCS(GRID_Vec2i) \
OPS(GRID_Vec2f) \
VEC_FUNCS(GRID_Vec2f) \
OPS(GRID_Vec3i) \
IVEC_FUNCS(GRID_Vec3i) \
OPS(GRID_Vec3f) \
VEC_FUNCS(GRID_Vec3f) \
FUNC2(GRID_Vec3f, cross, GRID_Vec3f) \
OPS(GRID_Vec4i) \
IVEC_FUNCS(GRID_Vec4i) \
OPS(GRID_Vec4f) \
VEC_FUNCS(GRID_Vec4f)

#define MATS \
OPS(GRID_Mat2)
MATRIX_FUNCS(GRID_Mat2)
OPS(GRID_Mat3)
MATRIX_FUNCS(GRID_Mat3)
OPS(GRID_Mat4)
MATRIX_FUNCS(GRID_Mat4)

VECS
MATS