/* ===========================================================================
 * File: stars.c
 * Date: 08 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

global State *state = &global_state;

#define NUM_STARS 1000
global vec3 stars[NUM_STARS];

internal vec3
star_new(void)
{
    vec3 s = {0};
    s = vec3((rand() % state->width) - (state->width * 0.5f),
             (rand() % state->height) - (state->height * 0.5f),
             (rand() % state->width));
    return s;
}

internal void
setup(void)
{
    state->clear_color = vec4(0.1f, 0.1f, 0.1f, 1.0f);
    for(u32 i = 0; i < NUM_STARS; ++i)
        stars[i] = star_new();
}

internal void
update(f32 dt)
{
    f32 speed = map(state->mouse.position.x, -state->width * 0.5f, state->width * 0.5f, 0.0f, 60.0f*20.0f);
    for(u32 i = 0; i < NUM_STARS; ++i) {
        vec3 *s = &stars[i];
        s->z -= speed * dt;
        if(s->z < 0.1) {
            *s = star_new();
        }
    }
}

internal void
draw(void)
{
    for(u32 i = 0; i < NUM_STARS; ++i) {
        f32 px = lerp(0.0f, stars[i].x / stars[i].z, state->width);
        f32 py = lerp(0.0f, stars[i].y / stars[i].z, state->height);

        f32 s = map(stars[i].z, 0.0f, state->width, 8.0f, 0.0f);

        Rectangle r = {
            .position = vec2(px, py),
            .size = vec2(s, s),
            .rotation = 0.0f,
            .color = vec4(s / 8.0f, 1.0f - (s / 8.0f), 0.0f, 1.0f),
            .fill_type = FillType_FILL,
        };

        render_rectangle(&r);
    }
}

internal void
teardown(void)
{

}
