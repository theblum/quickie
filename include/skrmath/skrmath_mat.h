#if !defined(SKRMATH_MAT_H)
#define SKRMATH_MAT_H
/* ===========================================================================
 * File: skrmath_mat.h
 * Date: 11 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

/* @Note: mat2 */

typedef union {
    vec2 row[2];
    struct {
        f32 m00, m01;
        f32 m10, m11;
    };
    f32 e[4];
} mat2;

#define mat2_init(v0, v1) { (v0), (v1) }
#define mat2(v0, v1) (mat2)mat2_init((v0), (v1))
#define mat2_zero_init     mat2_init(vec2_init(0.0f, 0.0f), vec2_init(0.0f, 0.0f))
#define mat2_identity_init mat2_init(vec2_init(1.0f, 0.0f), vec2_init(0.0f, 1.0f))
#define mat2_zero     mat2(vec2(0.0f, 0.0f), vec2(0.0f, 0.0f))
#define mat2_identity mat2(vec2(1.0f, 0.0f), vec2(0.0f, 1.0f))

/* @Note: mat3 */

typedef union {
    vec3 row[3];
    struct {
        f32 m00, m01, m02;
        f32 m10, m11, m12;
        f32 m20, m21, m22;
    };
    f32 e[9];
} mat3;

#define mat3_init(v0, v1, v2) { (v0), (v1), (v2) }
#define mat3(v0, v1, v2) (mat3)mat3_init((v0), (v1), (v2))
#define mat3_zero_init     mat3_init(vec3_init(0.0f, 0.0f, 0.0f), vec3_init(0.0f, 0.0f, 0.0f), vec3_init(0.0f, 0.0f, 0.0f))
#define mat3_identity_init mat3_init(vec3_init(1.0f, 0.0f, 0.0f), vec3_init(0.0f, 1.0f, 0.0f), vec3_init(0.0f, 0.0f, 1.0f))
#define mat3_zero     mat3(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f))
#define mat3_identity mat3(vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f))

/* @Note: mat4 */

typedef union {
    vec4 row[4];
    struct {
        f32 m00, m01, m02, m03;
        f32 m10, m11, m12, m13;
        f32 m20, m21, m22, m23;
        f32 m30, m31, m32, m33;
    };
    f32 e[16];
} mat4;

#define mat4_init(v0, v1, v2, v3) { (v0), (v1), (v2), (v3) }
#define mat4(v0, v1, v2, v3) (mat4)mat4_init((v0), (v1), (v2), (v3))
#define mat4_zero_init     mat4_init(vec4_init(0.0f, 0.0f, 0.0f, 0.0f), vec4_init(0.0f, 0.0f, 0.0f, 0.0f), vec4_init(0.0f, 0.0f, 0.0f, 0.0f), vec4_init(0.0f, 0.0f, 0.0f, 0.0f))
#define mat4_identity_init mat4_init(vec4_init(1.0f, 0.0f, 0.0f, 0.0f), vec4_init(0.0f, 1.0f, 0.0f, 0.0f), vec4_init(0.0f, 0.0f, 1.0f, 0.0f), vec4_init(0.0f, 0.0f, 0.0f, 1.0f))
#define mat4_zero     mat4(vec4(0.0f, 0.0f, 0.0f, 0.0f), vec4(0.0f, 0.0f, 0.0f, 0.0f), vec4(0.0f, 0.0f, 0.0f, 0.0f), vec4(0.0f, 0.0f, 0.0f, 0.0f))
#define mat4_identity mat4(vec4(1.0f, 0.0f, 0.0f, 0.0f), vec4(0.0f, 1.0f, 0.0f, 0.0f), vec4(0.0f, 0.0f, 1.0f, 0.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f))

#endif
