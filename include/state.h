#if !defined(STATE_H)
#define STATE_H
/* ===========================================================================
 * File: state.h
 * Date: 07 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

typedef struct {
    vec2 position;
    b32 buttons[GLFW_MOUSE_BUTTON_LAST + 1];
} Mouse;

typedef struct {
    b32 keys[GLFW_KEY_LAST + 1];
    Mouse mouse;

    s32 width;
    s32 height;
    f32 scale;

    b32 clear;
    vec4 clear_color;

    b32 multisample;

    u32 shader;
    u32 empty_tex;

    mat4 projection;
    mat4 view;

    Renderer rectangle;
    Renderer triangle;
    Renderer circle;
    Renderer line;
} State;

global State global_state;

#endif
