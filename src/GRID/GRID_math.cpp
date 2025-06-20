#include <glm_convert.h>

#include <GRID/GRID_math.h>
#include <glm/glm.hpp>

#define OP_IMPL(selfType, op) \
auto selfType::operator op(const selfType& other) const -> decltype(fromGLM(toGLM(*this) op toGLM(other))) { \
    return fromGLM(toGLM(*this) op toGLM(other)); \
}

#define OP_REF_IMPL(selfType, op) \
auto selfType::operator op(const selfType& other) -> decltype(fromGLM(toGLM(*this) op toGLM(other))) { \
    *this = fromGLM(toGLM(*this) op toGLM(other)); \
    return *this; \
}

#define OPS_IMPL(selfType) \
OP_IMPL(selfType, +) \
OP_IMPL(selfType, -) \
OP_IMPL(selfType, *) \
OP_IMPL(selfType, /) \
OP_REF_IMPL(selfType, +=) \
OP_REF_IMPL(selfType, -=) \
OP_REF_IMPL(selfType, *=) \
OP_REF_IMPL(selfType, /=) \
OP_IMPL(selfType, ==) \
OP_IMPL(selfType, !=)

#define FUNC1(selfType, func) \
auto selfType::func() const -> decltype(fromGLM(glm::func(toGLM(*this)))) { \
    return fromGLM(glm::func(toGLM(*this))); \
}

#define FUNC2(selfType, func, argType) \
auto selfType::func(const argType& other) const -> decltype(fromGLM(glm::func(toGLM(*this), toGLM(other)))) { \
    return fromGLM(glm::func(toGLM(*this), toGLM(other))); \
}

#define VEC_FUNCS_IMPL(selfType) \
FUNC1(selfType, length) \
FUNC2(selfType, distance, selfType) \
FUNC1(selfType, normalize) \
FUNC2(selfType, dot, selfType) \
FUNC2(selfType, outerProduct, selfType)

#define MATRIX_FUNCS_IMPL(selfType) \
FUNC1(selfType, determinant) \
FUNC1(selfType, inverse) \
FUNC1(selfType, transpose) \
FUNC2(selfType, matrixCompMult, selfType)

#define VECS \
OPS_IMPL(GRID_Vec2i) \
OPS_IMPL(GRID_Vec2f) \
VEC_FUNCS_IMPL(GRID_Vec2f) \
OPS_IMPL(GRID_Vec3i) \
OPS_IMPL(GRID_Vec3f) \
VEC_FUNCS_IMPL(GRID_Vec3f) \
FUNC2(GRID_Vec3f, cross, GRID_Vec3f) \
OPS_IMPL(GRID_Vec4i) \
OPS_IMPL(GRID_Vec4f) \
VEC_FUNCS_IMPL(GRID_Vec4f)

#define MATS \
OPS_IMPL(GRID_Mat2)
MATRIX_FUNCS_IMPL(GRID_Mat2)
OPS_IMPL(GRID_Mat3)
MATRIX_FUNCS_IMPL(GRID_Mat3)
OPS_IMPL(GRID_Mat4)
MATRIX_FUNCS_IMPL(GRID_Mat4)

VECS
MATS