/* ===========================================================================
 * File: skrmath_camera.c
 * Date: 12 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

internal mat4
lookat(vec3 position, vec3 target, vec3 up)
{
    vec3 f = vec3_normalize(vec3_sub(target, position));
    vec3 r = vec3_normalize(vec3_cross(up, f));
    vec3 u = vec3_cross(f, r);

    return mat4(vec4(r.x, u.x, f.x, 0.0f),
                vec4(r.y, u.y, f.y, 0.0f),
                vec4(r.z, u.z, f.z, 0.0f),
                vec4(-vec3_dot(r, position), -vec3_dot(u, position), -vec3_dot(f, position), 1.0f));
}

internal mat4
perspective(f32 fov, f32 aspect, f32 znear, f32 zfar)
{
    f32 thv = tanf(fov * 0.5f);
    f32 fovy = 1.0f / thv;
    f32 fovx = fovy / aspect;

    mat4 res = mat4_zero;
    res.row[0].x = fovx;
    res.row[1].y = fovy;
    res.row[2].z = zfar / (zfar - znear);
    res.row[2].w = 1.0f;
    return res;
}

internal mat4
ortho(f32 left, f32 right, f32 bottom, f32 top, f32 znear, f32 zfar)
{
    mat4 res = mat4_identity;
    res.row[0].x = 2.0f / (right - left);
    res.row[1].y = 2.0f / (top - bottom);
    res.row[2].z = 1.0f / (zfar - znear);
    res.row[3].x = (left + right) / (left - right);
    res.row[3].y = (top + bottom) / (bottom - top);
    res.row[3].z = znear / (znear - zfar);
    return res;
}
