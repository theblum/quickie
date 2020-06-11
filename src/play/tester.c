/* ===========================================================================
 * File: tester.c
 * Date: 07 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 180
#define SCREEN_SCALE  4.0f

global State *state = &global_state;

#define GRID_SIZE 8
#define GRID_COLS (SCREEN_WIDTH / GRID_SIZE)
#define GRID_ROWS ((SCREEN_HEIGHT / GRID_SIZE) + 1)

global Texture tex;
global Rectangle grid[GRID_COLS*GRID_ROWS];
global Rectangle r;
global Rectangle r2;
global Triangle t;
global Circle c;

internal void
create_grid(Rectangle *grid, u32 size, u32 cols, u32 rows, vec4 color)
{
    for(u32 y = 0; y < rows; ++y) {
        for(u32 x = 0; x < cols; ++x) {
            Rectangle *g    = grid + y*cols + x;
            f32 xx = (x * size) - (state->width * 0.5f) + (size * 0.5f);
            /* @Note: Drawing from bottom up so we have to draw an extra row and subtract the
             , remainder of pixels in case the size doesn't evenly divide the screen height. */
            f32 yy = (y * size) - (state->height * 0.5f) + (size * 0.5f)
                - (size * (state->height % size) / (f32)size);

            g->position     = vec2(xx, yy);
            g->size         = vec2(size, size);
            g->fill_type    = FillType_STROKE;
            g->stroke_size  = 1;
            g->stroke_color = color;
        }
    }
}

internal void
render_grid(Rectangle *grid, u32 length)
{
    for(u32 i = 0; i < length; ++i)
        render_rectangle(grid + i);
}

internal void
setup(void)
{
    create_grid(grid, GRID_SIZE, GRID_COLS, GRID_ROWS, vec4(1.0f, 1.0f, 1.0f, 0.2f));

    r.position  = vec2(0.0f, 0.0f);
    r.size      = vec2(100.0f, 100.0f);
    r.color     = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    r.fill_type = FillType_FILL;

    r2.position  = vec2(75.0f, 90.0f);
    r2.size      = vec2(100.0f, 150.0f);
    r2.color     = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    r2.fill_type = FillType_FILL | FillType_STROKE;
    r2.stroke_size  = 5;
    r2.stroke_color = vec4(0.0f, 1.0f, 1.0f, 1.0f);

    t.position  = vec2(0.0f, 0.0f);
    t.size      = vec2(50.0f, 200.0f);
    t.color     = vec4(1.0f, 1.0f, 1.0f, 1.0f);
    t.fill_type = FillType_STROKE;
    t.stroke_size  = 3;
    t.stroke_color = vec4(0.0f, 1.0f, 0.0f, 1.0f);

    c.position  = vec2(0.0f, 0.0f);
    c.radius    = 5.0f;
    c.color     = vec4(0.0f, 0.0f, 1.0f, 1.0f);
    c.fill_type = FillType_FILL | FillType_STROKE;
    c.stroke_size  = 2;
    c.stroke_color = vec4(1.0f, 0.0f, 0.0f, 1.0f);

    texture_create(&tex, 10, 10, false);
    for(u32 y = 0; y < tex.height; ++y) {
        for(u32 x = 0; x < tex.width; ++x) {
            u32 *pixel = (u32 *)tex.data + (y*tex.width + x);
            *pixel = rand();
        }
    }
    texture_update(&tex);
    r.texture = &tex;
}

internal void
update(f32 dt)
{
    for(u32 y = 0; y < tex.height; ++y) {
        for(u32 x = 0; x < tex.width; ++x) {
            u32 *pixel = (u32 *)tex.data + (y*tex.width + x);
            *pixel = rand();
        }
    }
    texture_update(&tex);

    /* @Note: camera  */

    vec3 vcam = vec3_zero;
    if(state->keys[GLFW_KEY_A])
        vcam.x += 1.0f;
    if(state->keys[GLFW_KEY_D])
        vcam.x -= 1.0f;
    if(state->keys[GLFW_KEY_W])
        vcam.y += 1.0f;
    if(state->keys[GLFW_KEY_S])
        vcam.y -= 1.0f;

    vcam = vec3_muls(vcam, state->width * dt);
    state->view = translate(state->view, vcam);

    f32 vscale = 1.0f;
    if(state->keys[GLFW_KEY_Q])
        vscale += dt;
    if(state->keys[GLFW_KEY_E])
        vscale -= dt;
    state->view = scale(state->view, vec3(vscale, vscale, 1.0f));

    /* @Note: bouncy ball */

    persist vec2 cvel = vec2_zero_init;
    vec2 cgrav = vec2(0.0f, -9.81f * dt); /* @Note: Earth gravity 9.81 m/s^2 */

    if(c.position.x >= state->width * 0.5f || c.position.x <= -state->width * 0.5f)
        cvel.x = -cvel.x;
    if(c.position.y < -state->height * 0.5f) {
        c.position.y = -state->height * 0.5f;
        cvel.y = -cvel.y * 1.0f;
    }

    vec2 cacc = vec2_zero;
    if(state->mouse.buttons[GLFW_MOUSE_BUTTON_1])
        cacc.x = 2.0f * dt;
    if(state->mouse.buttons[GLFW_MOUSE_BUTTON_2])
        cacc.x = -2.0f * dt;

    cacc.x += -cvel.x * 0.5f * dt;

    cvel = vec2_add(cvel, cacc);
    cvel = vec2_add(cvel, cgrav);
    c.position = vec2_add(c.position, cvel);
}

internal void
draw(void)
{
    render_circle(&c);

    render_grid(grid, nelems(grid));

    /* render_triangle(&t); */
    /* render_rectangle(&r); */
    /* render_rectangle(&r2); */
}

internal void
teardown(void)
{
    texture_destroy(&tex);
}
