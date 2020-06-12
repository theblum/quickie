/* ===========================================================================
 * File: skrmath_transform.c
 * Date: 11 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

internal mat4
translation(vec3 v)
{
    return mat4(vec4(1.0f, 0.0f, 0.0f, 0.0f),
                vec4(0.0f, 1.0f, 0.0f, 0.0f),
                vec4(0.0f, 0.0f, 1.0f, 0.0f),
                vec4( v.x,  v.y,  v.z, 1.0f));
}

internal mat4
translationf(f32 x, f32 y, f32 z)
{
    return mat4(vec4(1.0f, 0.0f, 0.0f, 0.0f),
                vec4(0.0f, 1.0f, 0.0f, 0.0f),
                vec4(0.0f, 0.0f, 1.0f, 0.0f),
                vec4(   x,    y,    z, 1.0f));
}

internal vec3
get_translation(mat4 m)
{
    return vec3(m.row[3].x, m.row[3].y, m.row[3].z);
}

internal mat4
scale(vec3 v)
{
    return mat4(vec4( v.x, 0.0f, 0.0f, 0.0f),
                vec4(0.0f,  v.y, 0.0f, 0.0f),
                vec4(0.0f, 0.0f,  v.z, 0.0f),
                vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

internal mat4
scalef(f32 x, f32 y, f32 z)
{
    return mat4(vec4(   x, 0.0f, 0.0f, 0.0f),
                vec4(0.0f,    y, 0.0f, 0.0f),
                vec4(0.0f, 0.0f,    z, 0.0f),
                vec4(0.0f, 0.0f, 0.0f, 1.0f));
}

internal vec3
get_scale(mat4 m)
{
    return vec3(m.row[0].x, m.row[1].y, m.row[2].z);
}

internal mat4
xrotation(f32 a)
{
    return mat4(vec4(1.0f,     0.0f,    0.0f, 0.0f),
                vec4(0.0f,  cosf(a), sinf(a), 0.0f),
                vec4(0.0f, -sinf(a), cosf(a), 0.0f),
                vec4(0.0f,     0.0f,    0.0f, 1.0f));
}

internal mat4
yrotation(f32 a)
{
    return mat4(vec4(cosf(a), 0.0f, -sinf(a), 0.0f),
                vec4(   0.0f, 1.0f,     0.0f, 0.0f),
                vec4(sinf(a), 0.0f,  cosf(a), 0.0f),
                vec4(   0.0f, 0.0f,    0.0f, 1.0f));
}

internal mat4
zrotation(f32 a)
{
    return mat4(vec4( cosf(a), sinf(a), 0.0f, 0.0f),
                vec4(-sinf(a), cosf(a), 0.0f, 0.0f),
                vec4(    0.0f,    0.0f, 1.0f, 0.0f),
                vec4(    0.0f,    0.0f, 0.0f, 1.0f));
}

internal mat4
rotationf(f32 pitch, f32 yaw, f32 roll)
{
#if 1
    mat4 zrot = zrotation(roll);
    mat4 xrot = xrotation(pitch);
    mat4 yrot = yrotation(yaw);

    return mat4_mul(mat4_mul(zrot, xrot), yrot);
#else
    /* @Note: Check with compiler disassembly to see if the below is faster. */
    return mat4(vec4(cosf(roll)*cosf(yaw) + sinf(roll)*sinf(pitch)*sinf(yaw),
                     sinf(roll)*cosf(pitch),
                     cosf(roll)*-sinf(yaw) + sinf(roll)*sinf(pitch)*cosf(yaw),
                     0.0f),
                vec4(-sinf(roll)*cosf(yaw) + cosf(roll)*sinf(pitch)*sinf(yaw),
                     cosf(roll)*cosf(pitch),
                     sinf(roll)*sinf(yaw) + cosf(roll)*sinf(pitch)*cosf(yaw),
                     0.0f),
                vec4(cosf(pitch)*sinf(yaw),
                     -sinf(pitch),
                     cosf(pitch)*cosf(yaw),
                     0.0f),
                vec4(0.0f, 0.0f, 0.0f, 1.0f));
#endif
}

internal mat4
rotation(vec3 v)
{
    return rotationf(v.x, v.y, v.z);
}

internal mat3
xrotation3x3(f32 a)
{
    return mat3(vec3(1.0f,     0.0f,    0.0f),
                vec3(0.0f,  cosf(a), sinf(a)),
                vec3(0.0f, -sinf(a), cosf(a)));
}

internal mat3
yrotation3x3(f32 a)
{
    return mat3(vec3(cosf(a), 0.0f,  -sinf(a)),
                vec3(   0.0f, 1.0f,      0.0f),
                vec3(sinf(a), 0.0f,   cosf(a)));
}

internal mat3
zrotation3x3(f32 a)
{
    return mat3(vec3( cosf(a), sinf(a), 0.0f),
                vec3(-sinf(a), cosf(a), 0.0f),
                vec3(    0.0f,    0.0f, 1.0f));
}

internal mat3
rotationf3x3(f32 pitch, f32 yaw, f32 roll)
{
#if 1
    mat3 zrot = zrotation3x3(roll);
    mat3 xrot = xrotation3x3(pitch);
    mat3 yrot = yrotation3x3(yaw);

    return mat3_mul(mat3_mul(zrot, xrot), yrot);
#else
    /* @Note: Check with compiler disassembly to see if the below is faster. */
    return mat3(vec3(cosf(roll)*cosf(yaw) + sinf(roll)*sinf(pitch)*sinf(yaw),
                     sinf(roll)*cosf(pitch),
                     cosf(roll)*-sinf(yaw) + sinf(roll)*sinf(pitch)*cosf(yaw)),
                vec3(-sinf(roll)*cosf(yaw) + cosf(roll)*sinf(pitch)*sinf(yaw),
                     cosf(roll)*cosf(pitch),
                     sinf(roll)*sinf(yaw) + cosf(roll)*sinf(pitch)*cosf(yaw)),
                vec3(cosf(pitch)*sinf(yaw),
                     -sinf(pitch),
                     cosf(pitch)*cosf(yaw)));
#endif
}

internal mat3
rotation3x3(vec3 v)
{
    return rotationf3x3(v.x, v.y, v.z);
}

internal mat2
rotation2x2(f32 a)
{
    return mat2(vec2( cosf(a), sinf(a)),
                vec2(-sinf(a), cosf(a)));
}
