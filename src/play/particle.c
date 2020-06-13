/* ===========================================================================
 * File: particle.c
 * Date: 11 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 180
#define SCREEN_SCALE 4.0f

global State *state = &global_state;

typedef struct {
    vec2 position;
    vec2 velocity; /* @TODO: Where I left off...add random velocity */
    f32 radius;

    vec4 start_color;
    vec4 end_color;
    vec4 color;

    f32 life_total;
    f32 life_remaining;
} Particle;

#define MAX_PARTICLES 10000
global Particle particles[MAX_PARTICLES];
global u32 num_particles;

internal void
particle_create(Particle *particle, vec2 position)
{
    particle->position = position;
    particle->velocity = vec2((rand() % 50) - 25, (rand() % 50) - 25);
    particle->radius = 10.0f;

    particle->start_color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    particle->end_color = vec4(1.0f, 1.0f, 0.0f, 0.5f);
    particle->color = particle->start_color;

    particle->life_total = 1.0f;
    particle->life_remaining = particle->life_total;
}

internal void
setup(void)
{
    num_particles = 0;
    state->clear = false;
}

internal void
update(f32 dt)
{
    for(u32 i = 0; i < 3; ++i) {
        particle_create(particles + num_particles++, state->mouse.position);
        num_particles %= MAX_PARTICLES;
    }

    for(u32 i = 0; i < num_particles; ++i) {
        Particle *p = particles + i;
        if(p->life_remaining <= 0.0f)
            continue;
        p->life_remaining -= dt;
        p->position = vec2_add(p->position, vec2_muls(p->velocity, dt));
        p->color.r = map(p->life_remaining, 0.0f, p->life_total, p->end_color.r, p->start_color.r);
        p->color.g = map(p->life_remaining, 0.0f, p->life_total, p->end_color.g, p->start_color.g);
        p->color.b = map(p->life_remaining, 0.0f, p->life_total, p->end_color.b, p->start_color.b);
        p->color.a = map(p->life_remaining, 0.0f, p->life_total, p->end_color.a, p->start_color.a);
    }
}

internal void
draw(void)
{
    for(u32 i = 0; i < num_particles; ++i) {
        Particle *p = particles + i;
        if(p->life_remaining <= 0.0f)
            continue;
        Circle c = {
            .position = p->position,
            .radius = map(p->life_remaining, 0.0f, p->life_total, 0.0f, p->radius),
            .color = p->color,
            .fill_type = FillType_FILL,
        };
        render_circle(&c);
    }
}

internal void
teardown(void)
{

}
