#if !defined(SHAPES_H)
#define SHAPES_H
/* ===========================================================================
 * File: shapes.h
 * Date: 08 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

enum FillType {
    FillType_NONE   = 0,
    FillType_FILL   = 1 << 0,
    FillType_STROKE = 1 << 1,
};

typedef struct {
    vec2 position;
    vec2 size;
    f32 rotation;
    vec4 color;
    u32 fill_type;
    u32 stroke_size;
    vec4 stroke_color;
    Texture *texture;
} Rectangle;

typedef struct {
    vec2 position;
    vec2 size;
    f32 rotation;
    vec4 color;
    u32 fill_type;
    u32 stroke_size;
    vec4 stroke_color;
    Texture *texture;
} Triangle;

typedef struct {
    vec2 position;
    f32 radius;
    f32 rotation;
    vec4 color;
    u32 fill_type;
    u32 stroke_size;
    vec4 stroke_color;
    Texture *texture;
} Circle;

#endif
