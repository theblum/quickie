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
               remainder of pixels in case the size doesn't evenly divide the screen height. */
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
    /* @Note: texture */

    for(u32 y = 0; y < tex.height; ++y) {
        for(u32 x = 0; x < tex.width; ++x) {
            u32 *pixel = (u32 *)tex.data + (y*tex.width + x);
            *pixel = rand();
        }
    }
    texture_update(&tex);

    /* @Note: rectangle */

    r.rotation += deg2rad(60.0f * dt);

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

    /* @Note: camera */

#if 1
    state->view = lookat(vec3(c.position.x, 0.0f, -1.0f),
                         vec3(c.position.x, 0.0f, 0.0f),
                         vec3(0.0f, 1.0f, 0.0f));

    persist f32 s = 1.0f;
    if(state->keys[GLFW_KEY_Q])
        s += -dt;
    if(state->keys[GLFW_KEY_E])
        s += dt;

    state->view = mat4_mul(state->view, scalef(s, s, 1.0f));
#else
    state->view = lookat(vec3(c.position.x, 0.0f, -state->width * 0.5f),
                         vec3(c.position.x, 0.0f, 0.0f),
                         vec3(0.0f, -1.0f, 0.0f));

    persist f32 s = 0.0f;
    if(state->keys[GLFW_KEY_Q])
        s += dt;
    if(state->keys[GLFW_KEY_E])
        s += -dt;

    state->view = mat4_mul(state->view, translationf(0.0f, 0.0f, s*500.0f));
#endif
}

internal void
draw(void)
{
    /* render_grid(grid, nelems(grid)); */
    /*  */
    render_triangle(&t);
    /* render_rectangle(&r); */
    /* render_circle(&c); */

    Line2D l = line2d(vec2(10.0f, 0.0f), vec2(-10.0f, 0.0f));
    render_line2d(&l);
}

internal void
teardown(void)
{
    texture_destroy(&tex);
}
