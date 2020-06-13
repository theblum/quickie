/* ===========================================================================
 * File: skrmath_vec.c
 * Date: 07 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

/* @Note: vec2 */

internal void vec2_print(vec2 a) { print_info("(%.3f, %.3f)\n", a.x, a.y); }

internal b32 vec2_eq(vec2 a, vec2 b)  { return eqlf(a.x, b.x) && eqlf(a.y, b.y); }
internal b32 vec2_neq(vec2 a, vec2 b) { return !vec2_eq(a, b); }

internal vec2 vec2_add(vec2 a, vec2 b) { return vec2(a.x + b.x, a.y + b.y); }
internal vec2 vec2_sub(vec2 a, vec2 b) { return vec2(a.x - b.x, a.y - b.y); }
internal vec2 vec2_mul(vec2 a, vec2 b) { return vec2(a.x * b.x, a.y * b.y); }
internal vec2 vec2_div(vec2 a, vec2 b) { return vec2(a.x / b.x, a.y / b.y); }

internal vec2 vec2_adds(vec2 a, f32 b) { return vec2(a.x + b, a.y + b); }
internal vec2 vec2_subs(vec2 a, f32 b) { return vec2(a.x - b, a.y - b); }
internal vec2 vec2_muls(vec2 a, f32 b) { return vec2(a.x * b, a.y * b); }
internal vec2 vec2_divs(vec2 a, f32 b) { return vec2(a.x / b, a.y / b); }
#define vec2_scale vec2_muls

internal vec2 vec2_negate(vec2 a) { return vec2(-a.x, -a.y); }

internal vec2
vec2_lerp(vec2 a, f32 t, vec2 b)
{
    vec2 res;
    res.x = lerp(a.x, t, b.x);
    res.y = lerp(a.y, t, b.y);
    return res;
}

internal f32 vec2_dot(vec2 a, vec2 b) { return a.x*b.x + a.y*b.y; }

internal f32 vec2_magnitudesq(vec2 a) { return vec2_dot(a, a); }
internal f32 vec2_magnitude(vec2 a)   { return sqrtf(vec2_magnitudesq(a)); }
#define vec2_lengthsq vec2_magnitudesq
#define vec2_length   vec2_magnitude

internal f32 vec2_distancesq(vec2 a, vec2 b) { return vec2_magnitudesq(vec2_sub(a, b)); }
internal f32 vec2_distance(vec2 a, vec2 b)   { return vec2_magnitude(vec2_sub(a, b)); }

internal vec2
vec2_normalize(vec2 a)
{
    vec2 res = vec2_zero;
    f32 mag = vec2_magnitude(a);
    if(mag != 0.0f)
        res = vec2_muls(a, 1.0f / mag);
    return res;
}

internal f32
vec2_angle(vec2 a, vec2 b)
{
    f32 dot = vec2_dot(a, b);
    f32 norm = sqrtf(vec2_magnitudesq(a) * vec2_magnitudesq(b));
    return acosf(dot / norm);
}

internal vec2
vec2_project(vec2 a, vec2 b)
{
    f32 dot = vec2_dot(a, b);
    f32 magsq = vec2_magnitudesq(b);
    return vec2_muls(b, dot / magsq);
}

internal vec2 vec2_perpendicular(vec2 a, vec2 b) { return vec2_sub(a, vec2_project(a, b)); }

internal vec2
vec2_reflect(vec2 a, vec2 norm)
{
    f32 dot = vec2_dot(a, norm);
    return vec2_sub(a, vec2_muls(norm, 2.0f * dot));
}

internal vec2
vec2_mulmat2(vec2 a, mat2 b)
{
    vec2 res;
    res.x = vec2_dot(a, vec2(b.row[0].x, b.row[1].x));
    res.y = vec2_dot(a, vec2(b.row[0].y, b.row[1].y));
    return res;
}

/* @Note: vec3 */

internal void vec3_print(vec3 a) { print_info("(%.3f, %.3f, %.3f)\n", a.x, a.y, a.z); }

internal b32 vec3_eq(vec3 a, vec3 b)  { return eqlf(a.x, b.x) && eqlf(a.y, b.y) && eqlf(a.z, b.z); }
internal b32 vec3_neq(vec3 a, vec3 b) { return !vec3_eq(a, b); }

internal vec3 vec3_add(vec3 a, vec3 b) { return vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
internal vec3 vec3_sub(vec3 a, vec3 b) { return vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
internal vec3 vec3_mul(vec3 a, vec3 b) { return vec3(a.x * b.x, a.y * b.y, a.z * b.z); }
internal vec3 vec3_div(vec3 a, vec3 b) { return vec3(a.x / b.x, a.y / b.y, a.z / b.z); }

internal vec3 vec3_adds(vec3 a, f32 b) { return vec3(a.x + b, a.y + b, a.z + b); }
internal vec3 vec3_subs(vec3 a, f32 b) { return vec3(a.x - b, a.y - b, a.z - b); }
internal vec3 vec3_muls(vec3 a, f32 b) { return vec3(a.x * b, a.y * b, a.z * b); }
internal vec3 vec3_divs(vec3 a, f32 b) { return vec3(a.x / b, a.y / b, a.z / b); }
#define vec3_scale vec3_muls

internal vec3 vec3_negate(vec3 a) { return vec3(-a.x, -a.y, -a.z); }

internal vec3
vec3_lerp(vec3 a, f32 t, vec3 b)
{
    vec3 res;
    res.x = lerp(a.x, t, b.x);
    res.y = lerp(a.y, t, b.y);
    res.z = lerp(a.z, t, b.z);
    return res;
}

internal f32 vec3_dot(vec3 a, vec3 b) { return a.x*b.x + a.y*b.y + a.z*b.z; }

internal f32 vec3_magnitudesq(vec3 a) { return vec3_dot(a, a); }
internal f32 vec3_magnitude(vec3 a)   { return sqrtf(vec3_magnitudesq(a)); }
#define vec3_lengthsq vec3_magnitudesq
#define vec3_length   vec3_magnitude

internal f32 vec3_distancesq(vec3 a, vec3 b) { return vec3_magnitudesq(vec3_sub(a, b)); }
internal f32 vec3_distance(vec3 a, vec3 b)   { return vec3_magnitude(vec3_sub(a, b)); }

internal vec3
vec3_normalize(vec3 a)
{
    vec3 res = vec3_zero;
    f32 mag = vec3_magnitude(a);
    if(mag != 0.0f)
        res = vec3_muls(a, 1.0f / mag);
    return res;
}

internal vec3
vec3_cross(vec3 a, vec3 b)
{
    return vec3(a.y*b.z - a.z*b.y,
                a.z*b.x - a.x*b.z,
                a.x*b.y - a.y*b.x);
}

internal f32
vec3_angle(vec3 a, vec3 b)
{
    f32 dot = vec3_dot(a, b);
    f32 norm = sqrtf(vec3_magnitudesq(a) * vec3_magnitudesq(b));
    return acosf(dot / norm);
}

internal vec3
vec3_project(vec3 a, vec3 b)
{
    f32 dot = vec3_dot(a, b);
    f32 magsq = vec3_magnitudesq(b);
    return vec3_muls(b, dot / magsq);
}

internal vec3 vec3_perpendicular(vec3 a, vec3 b) { return vec3_sub(a, vec3_project(a, b)); }

internal vec3
vec3_reflect(vec3 a, vec3 norm)
{
    f32 dot = vec3_dot(a, norm);
    return vec3_sub(a, vec3_muls(norm, 2.0f * dot));
}

internal vec3
vec3_mulmat3(vec3 a, mat3 b)
{
    vec3 res;
    res.x = vec3_dot(a, vec3(b.row[0].x, b.row[1].x, b.row[2].x));
    res.y = vec3_dot(a, vec3(b.row[0].y, b.row[1].y, b.row[2].y));
    res.z = vec3_dot(a, vec3(b.row[0].z, b.row[1].z, b.row[2].z));
    return res;
}

internal vec3
vec3_mulmat4(vec3 a, f32 w, mat4 b)
{
    vec3 res;
    res.x = vec3_dot(a, vec3(b.row[0].x, b.row[1].x, b.row[2].x)) + w*b.row[3].x;
    res.y = vec3_dot(a, vec3(b.row[0].y, b.row[1].y, b.row[2].y)) + w*b.row[3].y;
    res.z = vec3_dot(a, vec3(b.row[0].z, b.row[1].z, b.row[2].z)) + w*b.row[3].z;
    return res;
}

/* @Note: vec4 */

internal void vec4_print(vec4 a) { print_info("(%.3f, %.3f, %.3f, %.3f)\n", a.x, a.y, a.z, a.w); }

internal b32 vec4_eq(vec4 a, vec4 b)  { return eqlf(a.x, b.x) && eqlf(a.y, b.y) && eqlf(a.z, b.z) && eqlf(a.w, b.w); }
internal b32 vec4_neq(vec4 a, vec4 b) { return !vec4_eq(a, b); }

internal vec4 vec4_add(vec4 a, vec4 b) { return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w); }
internal vec4 vec4_sub(vec4 a, vec4 b) { return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w); }
internal vec4 vec4_mul(vec4 a, vec4 b) { return vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w); }
internal vec4 vec4_div(vec4 a, vec4 b) { return vec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w); }

internal vec4 vec4_adds(vec4 a, f32 b) { return vec4(a.x + b, a.y + b, a.z + b, a.w + b); }
internal vec4 vec4_subs(vec4 a, f32 b) { return vec4(a.x - b, a.y - b, a.z - b, a.w - b); }
internal vec4 vec4_muls(vec4 a, f32 b) { return vec4(a.x * b, a.y * b, a.z * b, a.w * b); }
internal vec4 vec4_divs(vec4 a, f32 b) { return vec4(a.x / b, a.y / b, a.z / b, a.w / b); }
#define vec4_scale vec4_muls

internal vec4 vec4_negate(vec4 a) { return vec4(-a.x, -a.y, -a.z, -a.w); }

internal vec4
vec4_lerp(vec4 a, f32 t, vec4 b)
{
    vec4 res;
    res.x = lerp(a.x, t, b.x);
    res.y = lerp(a.y, t, b.y);
    res.z = lerp(a.z, t, b.z);
    res.w = lerp(a.w, t, b.w);
    return res;
}

internal f32 vec4_dot(vec4 a, vec4 b) { return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w; }

internal f32 vec4_magnitudesq(vec4 a) { return vec4_dot(a, a); }
internal f32 vec4_magnitude(vec4 a)   { return sqrtf(vec4_magnitudesq(a)); }
#define vec4_lengthsq vec4_magnitudesq
#define vec4_length   vec4_magnitude

internal f32 vec4_distancesq(vec4 a, vec4 b) { return vec4_magnitudesq(vec4_sub(a, b)); }
internal f32 vec4_distance(vec4 a, vec4 b)   { return vec4_magnitude(vec4_sub(a, b)); }

internal vec4
vec4_normalize(vec4 a)
{
    vec4 res = vec4_zero;
    f32 mag = vec4_magnitude(a);
    if(mag != 0.0f)
        res = vec4_muls(a, 1.0f / mag);
    return res;
}

internal vec4
vec4_mulmat4(vec4 a, mat4 b)
{
    vec4 res;
    res.x = vec4_dot(a, vec4(b.row[0].x, b.row[1].x, b.row[2].x, b.row[3].x));
    res.y = vec4_dot(a, vec4(b.row[0].y, b.row[1].y, b.row[2].y, b.row[3].y));
    res.z = vec4_dot(a, vec4(b.row[0].z, b.row[1].z, b.row[2].z, b.row[3].z));
    res.w = vec4_dot(a, vec4(b.row[0].w, b.row[1].w, b.row[2].w, b.row[3].w));
    return res;
}

/* @Note: generic */

#define _vec_fn(f, a, ...)   \
    _Generic((a),            \
             vec2: vec2_##f, \
             vec3: vec3_##f, \
             vec4: vec4_##f)((a), ##__VA_ARGS__)

#define vec_print(a) _vec_fn(print, (a))

#define vec_eq(a, b)  _vec_fn(eq, (a), (b))
#define vec_neq(a, b) _vec_fn(neq, (a), (b))

#define vec_add(a, b) _vec_fn(add, (a), (b))
#define vec_sub(a, b) _vec_fn(sub, (a), (b))
#define vec_mul(a, b) _vec_fn(mul, (a), (b))
#define vec_div(a, b) _vec_fn(div, (a), (b))

#define vec_adds(a, b) _vec_fn(adds, (a), (b))
#define vec_subs(a, b) _vec_fn(subs, (a), (b))
#define vec_muls(a, b) _vec_fn(muls, (a), (b))
#define vec_divs(a, b) _vec_fn(divs, (a), (b))
#define vec_scale vec_muls

#define vec_negate _vec_fn(negate, (a))
#define vec_lerp   _vec_fn(lerp, (a), (t), (b))

#define vec_dot(a, b) _vec_fn(dot, (a), (b))

#define vec_magnitudesq(a) _vec_fn(magnitudesq, (a))
#define vec_magnitude(a)   _vec_fn(magnitude, (a))
#define vec_lengthsq vec_magnitudesq
#define vec_length   vec_magnitude

#define vec_distancesq(a, b) _vec_fn(distancesq, (a), (b))
#define vec_distance(a, b)   _vec_fn(distance, (a), (b))

#define vec4_normalize(a) _vec_fn(normalize, (a))
