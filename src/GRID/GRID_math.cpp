#include <glm_convert.h>

#include <GRID/GRID_math.h>
#include <glm/glm.hpp>

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

#define MATRIX_FUNCS(selfType) \
FUNC1(selfType, determinant) \
FUNC1(selfType, inverse) \
FUNC1(selfType, transpose) \
FUNC2(selfType, matrixCompMult, selfType)

#define VECS \
OPS(GRID_Vec2i) \
OPS(GRID_Vec2f) \
VEC_FUNCS(GRID_Vec2f) \
OPS(GRID_Vec3i) \
OPS(GRID_Vec3f) \
VEC_FUNCS(GRID_Vec3f) \
FUNC2(GRID_Vec3f, cross, GRID_Vec3f) \
OPS(GRID_Vec4i) \
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