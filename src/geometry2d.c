/* ===========================================================================
 * File: geometry2d.c
 * Date: 12 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

internal Point2D
point2d(f32 x, f32 y)
{
    return vec2(x, y);
}

internal Line2D
line2d(Point2D start, Point2D end)
{
    Line2D res = {
        .start = start,
        .end = end,
    };
    return res;
}

internal f32
line2d_length(Line2D *line)
{
    return vec2_distance(line->end, line->start);
}

internal f32
line2d_lengthsq(Line2D *line)
{
    return vec2_distancesq(line->end, line->start);
}
