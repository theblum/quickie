#if !defined(SKRMATH_H)
#define SKRMATH_H
/* ===========================================================================
 * File: skrmath.h
 * Date: 07 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

/* @Note: vec2 */

typedef union {
    struct { f32 x, y; };
    f32 e[2];
} vec2;

#define vec2_init(x, y) {{ (x), (y) }}
#define vec2(x, y) (vec2)vec2_init((x), (y))
#define vec2_zero_init vec2_init(0.0f, 0.0f)
#define vec2_one_init vec2_init(1.0f, 1.0f)
#define vec2_zero vec2(0.0f, 0.0f)
#define vec2_one  vec2(1.0f, 1.0f)

/* @Note: vec3 */

typedef union {
    struct { f32 x, y, z; };
    struct { vec2 xy; f32 ignored(z); };
    struct { f32 ignored(x); vec2 yz; };
    struct { f32 r, g, b; };
    f32 e[3];
} vec3;

#define vec3_init(x, y, z) {{ (x), (y), (z) }}
#define vec3(x, y, z) (vec3)vec3_init((x), (y), (z))
#define vec3_zero_init vec3_init(0.0f, 0.0f, 0.0f)
#define vec3_one_init  vec3_init(1.0f, 1.0f, 1.0f)
#define vec3_zero vec3(0.0f, 0.0f, 0.0f)
#define vec3_one  vec3(1.0f, 1.0f, 1.0f)

/* @Note: vec4 */

typedef union {
    struct { f32 x, y, z, w; };
    struct { vec2 xy; f32 ignored(z); f32 ignored(w); };
    struct { f32 ignored(x); vec2 yz; f32 ignored(w); };
    struct { f32 ignored(x); f32 ignored(y); vec2 zw; };
    struct { vec3 xyz; f32 ignored(w); };
    struct { f32 ignored(x); vec3 yzw; };
    struct { f32 r, g, b, a; };
    struct { vec3 rgb; f32 ignored(a); };
    f32 e[4];
} vec4;

#define vec4_init(x, y, z, w) {{ (x), (y), (z), (w) }}
#define vec4(x, y, z, w) (vec4)vec4_init((x), (y), (z), (w))
#define vec4_zero_init vec4_init(0.0f, 0.0f, 0.0f, 0.0f)
#define vec4_one_init  vec4_init(1.0f, 1.0f, 1.0f, 1.0f) 
#define vec4_zero vec4(0.0f, 0.0f, 0.0f, 0.0f)
#define vec4_one  vec4(1.0f, 1.0f, 1.0f, 1.0f) 

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
#define mat2_zero mat2(vec2(0.0f, 0.0f), \
                       vec2(0.0f, 0.0f))
#define mat2_identity mat2(vec2(1.0f, 0.0f), \
                           vec2(0.0f, 1.0f))

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
#define mat3_zero mat3(vec3(0.0f, 0.0f, 0.0f), \
                       vec3(0.0f, 0.0f, 0.0f), \
                       vec3(0.0f, 0.0f, 0.0f))
#define mat3_identity mat3(vec3(1.0f, 0.0f, 0.0f), \
                           vec3(0.0f, 1.0f, 0.0f), \
                           vec3(0.0f, 0.0f, 1.0f))

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
#define mat4_zero mat4(vec4(0.0f, 0.0f, 0.0f, 0.0f), \
                       vec4(0.0f, 0.0f, 0.0f, 0.0f), \
                       vec4(0.0f, 0.0f, 0.0f, 0.0f), \
                       vec4(0.0f, 0.0f, 0.0f, 0.0f))
#define mat4_identity mat4(vec4(1.0f, 0.0f, 0.0f, 0.0f), \
                           vec4(0.0f, 1.0f, 0.0f, 0.0f), \
                           vec4(0.0f, 0.0f, 1.0f, 0.0f), \
                           vec4(0.0f, 0.0f, 0.0f, 1.0f))
#endif
