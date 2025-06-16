#pragma once

#include "export.h"

struct GRID_Vec2f;
struct GRID_Vec2i;
struct GRID_Vec3f;
struct GRID_Vec3i;
struct GRID_Vec4f;
struct GRID_Vec4i;
struct GRID_Mat2;
struct GRID_Mat3;
struct GRID_Mat4;

#define OPS(typeSelf) \
    typeSelf operator+(const typeSelf& other) const; \
    typeSelf operator-(const typeSelf& other) const; \
    typeSelf operator*(const typeSelf& other) const; \
    typeSelf operator/(const typeSelf& other) const; \
    bool operator==(const typeSelf& other) const; \
    bool operator!=(const typeSelf& other) const; \
    typeSelf operator+=(const typeSelf& other); \
    typeSelf operator-=(const typeSelf& other); \
    typeSelf operator*=(const typeSelf& other); \
    typeSelf operator/=(const typeSelf& other);

#define VECTOR_FUNCS(typeSelf) \
    float length() const; \
    float distance(const typeSelf& other) const; \
    typeSelf normalize() const; \
    float dot(const typeSelf& other) const;

#define MATRIX_FUNCS(typeSelf) \
    typeSelf matrixCompMult(const typeSelf& other) const; \
    typeSelf transpose() const; \
    typeSelf inverse() const; \
    float determinant() const;

#define ITERATOR_OP(elementType, firstElement) \
    elementType& operator[](int index) { return *(&##firstElement + index); } \
    const elementType& operator[](int index) const { return *(&##firstElement + index); }

struct EXPORT GRID_Vec2f {
    float x, y;
    GRID_Vec2f(float x_, float y_) : x(x_), y(y_) {}
    ITERATOR_OP(float, x)
    OPS(GRID_Vec2f)
    VECTOR_FUNCS(GRID_Vec2f)
    GRID_Mat2 outerProduct(const GRID_Vec2f& other) const;
};

struct EXPORT GRID_Vec2i {
    int x, y;
    GRID_Vec2i(int x_, int y_) : x(x_), y(y_) {}
    ITERATOR_OP(int, x)
    OPS(GRID_Vec2i)
};

struct EXPORT GRID_Vec3f {
    float x, y, z;
    GRID_Vec3f(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    ITERATOR_OP(float, x)
    OPS(GRID_Vec3f)
    VECTOR_FUNCS(GRID_Vec3f)
    GRID_Vec3f cross(const GRID_Vec3f& other) const;
    GRID_Mat3 outerProduct(const GRID_Vec3f& other) const;
};

struct EXPORT GRID_Vec3i {
    int x, y, z;
    GRID_Vec3i(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}
    ITERATOR_OP(int, x)
    OPS(GRID_Vec3i)
};

struct EXPORT GRID_Vec4f {
    float x, y, z, w;
    GRID_Vec4f(float x_, float y_, float z_, float w_) : x(x_), y(y_), z(z_), w(w_) {}
    ITERATOR_OP(float, x)
    OPS(GRID_Vec4f)
    VECTOR_FUNCS(GRID_Vec4f)
    GRID_Mat4 outerProduct(const GRID_Vec4f& other) const;
};

struct EXPORT GRID_Vec4i {
    int x, y, z, w;
    GRID_Vec4i(int x_, int y_, int z_, int w_) : x(x_), y(y_), z(z_), w(w_) {}
    ITERATOR_OP(int, x)
    OPS(GRID_Vec4i)
};

struct EXPORT GRID_Mat2 {
    GRID_Vec2f col0, col1;
    GRID_Mat2(float x0_, float y0_,
            float x1_, float y1_)
            : col0(GRID_Vec2f(x0_, y0_)),
            col1(GRID_Vec2f(x1_, y1_)) {}
    ITERATOR_OP(GRID_Vec2f, col0)
    OPS(GRID_Mat2)
    MATRIX_FUNCS(GRID_Mat2)
};

struct EXPORT GRID_Mat3 {
    GRID_Vec3f col0, col1, col2;
    GRID_Mat3(float x0_, float y0_, float z0_,
            float x1_, float y1_, float z1_,
            float x2_, float y2_, float z2_)
            : col0(GRID_Vec3f(x0_, y0_, z0_)),
            col1(GRID_Vec3f(x1_, y1_, z1_)),
            col2(GRID_Vec3f(x2_, y2_, z2_)) {}
    ITERATOR_OP(GRID_Vec3f, col0)
    OPS(GRID_Mat3)
    MATRIX_FUNCS(GRID_Mat3)
};

struct EXPORT GRID_Mat4 {
    GRID_Vec4f col0, col1, col2, col3;
    GRID_Mat4(float x0_, float y0_, float z0_, float w0_,
            float x1_, float y1_, float z1_, float w1_,
            float x2_, float y2_, float z2_, float w2_,
            float x3_, float y3_, float z3_, float w3_)
            : col0(GRID_Vec4f(x0_, y0_, z0_, w0_)),
            col1(GRID_Vec4f(x1_, y1_, z1_, w1_)),
            col2(GRID_Vec4f(x2_, y2_, z2_, w2_)),
            col3(GRID_Vec4f(x3_, y3_, z3_, w3_)) {}
    ITERATOR_OP(GRID_Vec4f, col0)
    OPS(GRID_Mat4)
    MATRIX_FUNCS(GRID_Mat4)
};

#undef VECTOR_OPS