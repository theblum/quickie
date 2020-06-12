/* ===========================================================================
 * File: skrmath_mat.c
 * Date: 11 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

internal void
_mat_transpose(f32 *dst, f32 *src, u32 rows, u32 cols)
{
    for(u32 i = 0; i < rows*cols; ++i) {
        u32 row = i / rows;
        u32 col = i % rows;
        dst[i] = src[cols*col + row];
    }
}

internal void
_mat_mul(f32 *dst, f32 *a, u32 arows, u32 acols, f32 *b, u32 brows, u32 bcols)
{
    assert(acols == brows);
    for(u32 i = 0; i < arows; ++i)
        for(u32 j = 0; j < bcols; ++j) {
            dst[i*bcols + j] = 0.0f;
            for(u32 k = 0; k < brows; ++k)
                dst[i*bcols + j] += a[i*acols + k] * b[k*bcols + j];
        }
}

internal void
_mat_cofactor(f32 *dst, f32 *src, u32 rows, u32 cols)
{
    for(u32 i = 0; i < rows; ++i)
        for(u32 j = 0; j < cols; ++j)
            dst[j*cols + i] = src[j*cols + i] * powf(-1.0f, i + j);
}

/* @Note: mat2 */

internal void
mat2_print(mat2 a)
{
    print_info("[[%.3f, %.3f]\n",  a.row[0].x, a.row[0].y);
    print_info(" [%.3f, %.3f]]\n", a.row[1].x, a.row[1].y);
}

internal b32
mat2_eq(mat2 a, mat2 b)
{
    for(u32 i = 0; i < 4; ++i)
        if(!eqlf(a.e[i], b.e[i]))
            return false;
    return true;
}

internal b32 mat2_neq(mat2 a, mat2 b) { return !mat2_eq(a, b); }

internal mat2
mat2_transpose(mat2 a)
{
    mat2 res;
    _mat_transpose(res.e, a.e, 2, 2);
    return res;
}

internal mat2
mat2_muls(mat2 a, f32 b)
{
    mat2 res;
    for(u32 i = 0; i < 2; ++i)
        res.row[i] = vec2_muls(a.row[i], b);
    return res;
}

internal mat2
mat2_mul(mat2 a, mat2 b)
{
    mat2 res;
    _mat_mul(res.e, a.e, 2, 2, b.e, 2, 2);
    return res;
}

internal f32
mat2_determinant(mat2 a)
{
    return a.m00 * a.m11 - a.m01 * a.m10;
}

internal mat2
mat2_minor(mat2 a)
{
    return mat2(vec2(a.m11, a.m10),
                vec2(a.m01, a.m00));
}

internal mat2
mat2_cofactor(mat2 a)
{
    mat2 res;
    _mat_cofactor(res.e, mat2_minor(a).e, 2, 2);
    return res;
}

internal mat2
mat2_adjugate(mat2 a)
{
    return mat2_transpose(mat2_cofactor(a));
}

internal mat2
mat2_inverse(mat2 a)
{
    mat2 res = mat2_identity;
    f32 det = mat2_determinant(a);
    if(!eqlf(det, 0.0f))
        res = mat2_muls(mat2_adjugate(a), 1.0f / det);
    return res;
}

/* @Note: mat3 */

internal void
mat3_print(mat3 a)
{
    print_info("[[%.3f, %.3f, %.3f]\n",  a.row[0].x, a.row[0].y, a.row[0].z);
    print_info(" [%.3f, %.3f, %.3f]\n",  a.row[1].x, a.row[1].y, a.row[1].z);
    print_info(" [%.3f, %.3f, %.3f]]\n", a.row[2].x, a.row[2].y, a.row[2].z);
}

internal b32
mat3_eq(mat3 a, mat3 b)
{
    for(u32 i = 0; i < 9; ++i)
        if(!eqlf(a.e[i], b.e[i]))
            return false;
    return true;
}

internal b32 mat3_neq(mat3 a, mat3 b) { return !mat3_eq(a, b); }

internal mat3
mat3_transpose(mat3 a)
{
    mat3 res;
    _mat_transpose(res.e, a.e, 3, 3);
    return res;
}

internal mat3
mat3_muls(mat3 a, f32 b)
{
    mat3 res;
    for(u32 i = 0; i < 3; ++i)
        res.row[i] = vec3_muls(a.row[i], b);
    return res;
}

internal mat3
mat3_mul(mat3 a, mat3 b)
{
    mat3 res;
    _mat_mul(res.e, a.e, 3, 3, b.e, 3, 3);
    return res;
}

internal mat2
mat3_cut(mat3 a, u32 row, u32 col)
{
    mat2 res;
    u32 idx = 0;
    for(u32 i = 0; i < 3; ++i)
        for(u32 j = 0; j < 3; ++j) {
            if(i == row || j == col)
                continue;
            res.e[idx++] = a.e[i*3 + j];
        }
    return res;
}

internal mat3
mat3_minor(mat3 a)
{
    mat3 res;
    for(u32 i = 0; i < 3; ++i)
        for(u32 j = 0; j < 3; ++j)
            res.e[i*3 + j] = mat2_determinant(mat3_cut(a, i, j));
    return res;
}

internal mat3
mat3_cofactor(mat3 a)
{
    mat3 res;
    _mat_cofactor(res.e, mat3_minor(a).e, 3, 3);
    return res;
}

internal f32
mat3_determinant(mat3 a)
{
    f32 res = 0.0f;
    mat3 cof = mat3_cofactor(a);
    for(u32 i = 0; i < 3; ++i)
        res += a.e[i] * cof.e[i];
    return res;
}

internal mat3
mat3_adjugate(mat3 a)
{
    return mat3_transpose(mat3_cofactor(a));
}

internal mat3
mat3_inverse(mat3 a)
{
    mat3 res = mat3_identity;
    f32 det = mat3_determinant(a);
    if(!eqlf(det, 0.0f))
        res = mat3_muls(mat3_adjugate(a), 1.0f / det);
    return res;
}

/* @Note: mat4 */

internal void
mat4_print(mat4 a)
{
    print_info("[[%.3f, %.3f, %.3f, %.3f]\n",  a.row[0].x, a.row[0].y, a.row[0].z, a.row[0].w);
    print_info(" [%.3f, %.3f, %.3f, %.3f]\n",  a.row[1].x, a.row[1].y, a.row[1].z, a.row[1].w);
    print_info(" [%.3f, %.3f, %.3f, %.3f]\n",  a.row[2].x, a.row[2].y, a.row[2].z, a.row[2].w);
    print_info(" [%.3f, %.3f, %.3f, %.3f]]\n", a.row[3].x, a.row[3].y, a.row[3].z, a.row[3].w);
}

internal b32
mat4_eq(mat4 a, mat4 b)
{
    for(u32 i = 0; i < 16; ++i)
        if(!eqlf(a.e[i], b.e[i]))
            return false;
    return true;
}

internal b32 mat4_neq(mat4 a, mat4 b) { return !mat4_eq(a, b); }

internal mat4
mat4_transpose(mat4 a)
{
    mat4 res;
    _mat_transpose(res.e, a.e, 4, 4);
    return res;
}

internal mat4
mat4_muls(mat4 a, f32 b)
{
    mat4 res;
    for(u32 i = 0; i < 4; ++i)
        res.row[i] = vec4_muls(a.row[i], b);
    return res;
}

internal mat4
mat4_mul(mat4 a, mat4 b)
{
    mat4 res;
    _mat_mul(res.e, a.e, 4, 4, b.e, 4, 4);
    return res;
}

internal mat3
mat4_cut(mat4 a, u32 row, u32 col)
{
    mat3 res;
    u32 idx = 0;
    for(u32 i = 0; i < 4; ++i)
        for(u32 j = 0; j < 4; ++j) {
            if(i == row || j == col)
                continue;
            res.e[idx++] = a.e[i*4 + j];
        }
    return res;
}

internal mat4
mat4_minor(mat4 a)
{
    mat4 res;
    for(u32 i = 0; i < 4; ++i)
        for(u32 j = 0; j < 4; ++j)
            res.e[i*4 + j] = mat3_determinant(mat4_cut(a, i, j));
    return res;
}

internal mat4
mat4_cofactor(mat4 a)
{
    mat4 res;
    _mat_cofactor(res.e, mat4_minor(a).e, 4, 4);
    return res;
}

internal f32
mat4_determinant(mat4 a)
{
    f32 res = 0.0f;
    mat4 cof = mat4_cofactor(a);
    for(u32 i = 0; i < 4; ++i)
        res += a.e[i] * cof.e[i];
    return res;
}

internal mat4
mat4_adjugate(mat4 a)
{
    return mat4_transpose(mat4_cofactor(a));
}

internal mat4
mat4_inverse(mat4 a)
{
    mat4 res = mat4_identity;
    f32 det = mat4_determinant(a);
    if(!eqlf(det, 0.0f))
        res = mat4_muls(mat4_adjugate(a), 1.0f / det);
    return res;
}

/* @Note: generic */

#define _mat_fn(f, a, ...)   \
    _Generic((a),            \
             mat2: mat2_##f, \
             mat3: mat3_##f, \
             mat4: mat4_##f)((a), ##__VA_ARGS__)

#define mat_print(a)  _mat_fn(print, (a))

#define mat_eq(a, b)  _mat_fn(eq, (a), (b))
#define mat_neq(a, b) _mat_fn(neq, (a), (b))

#define mat_transpose(a) _mat_fn(transpose, (a))

#define mat_muls(a, b) _mat_fn(muls, (a), (b))
#define mat_mul(a, b)  _mat_fn(mul, (a), (b))

#define mat_minor(a)       _mat_fn(minor, (a))
#define mat_cofactor(a)    _mat_fn(cofactor, (a))
#define mat_determinant(a) _mat_fn(determinant, (a))
#define mat_adjugate(a)    _mat_fn(adjugate, (a))
#define mat_inverse(a)     _mat_fn(inverse, (a))
