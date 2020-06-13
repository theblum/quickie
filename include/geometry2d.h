#if !defined(GEOMETRY2D_H)
#define GEOMETRY2D_H
/* ===========================================================================
 * File: geometry2d.h
 * Date: 12 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

typedef vec2 Point2D;

typedef struct {
    Point2D start;
    Point2D end;
} Line2D;

#endif
