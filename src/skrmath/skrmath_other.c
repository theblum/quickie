/* ===========================================================================
 * File: skrmath_other.c
 * Date: 11 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

/* @Note: other */

internal mat4
ortho(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far)
{
    mat4 r = mat4_zero;

    f32 rlinv = 1.0f / (right - left);
    f32 tbinv = 1.0f / (top - bottom);
    f32 fninv = -1.0f / (far - near);

    r.row[0].x = 2.0f * rlinv;
    r.row[1].y = 2.0f * tbinv;
    r.row[2].z = 2.0f * fninv;
    r.row[3].x = -(right + left) * rlinv;
    r.row[3].y = -(top + bottom) * tbinv;
    r.row[3].z = (far + near) * fninv;
    r.row[3].w = 1.0f;

    return r;
}
