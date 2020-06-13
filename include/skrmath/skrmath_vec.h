#if !defined(SKRMATH_VEC_H)
#define SKRMATH_VEC_H
/* ===========================================================================
 * File: skrmath_vec.h
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
#define vec2_one_init  vec2_init(1.0f, 1.0f)
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

#endif
