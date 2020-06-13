/* ===========================================================================
 * File: render.c
 * Date: 03 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

internal void
renderer_create_rectangle(Renderer *renderer)
{
    f32 verts[] = {
        -0.5f, -0.5f, 0.0f,   -1.0f, -1.0f,
        +0.5f, -0.5f, 0.0f,   +1.0f, -1.0f,
        +0.5f, +0.5f, 0.0f,   +1.0f, +1.0f,
        -0.5f, +0.5f, 0.0f,   -1.0f, +1.0f,
    };

    u16 idx[] = {
        0, 1, 2, 3, 0, 2,
    };

    u32 bo[2] = {0};
    glGenBuffers(2, bo);

    glGenVertexArrays(1, &renderer->vao);
    glBindVertexArray(renderer->vao);

    glBindBuffer(GL_ARRAY_BUFFER, bo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bo[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(f32), (void *)(0*sizeof(f32)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(f32), (void *)(3*sizeof(f32)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

internal void
renderer_create_triangle(Renderer *renderer)
{
    f32 verts[] = {
        +0.0f, +0.5f, 0.0f,   +0.5f, +1.0f,
        +0.5f, -0.5f, 0.0f,   +1.0f, -1.0f,
        -0.5f, -0.5f, 0.0f,   -1.0f, -1.0f,
    };

    u32 vbo = 0;
    glGenBuffers(1, &vbo);

    glGenVertexArrays(1, &renderer->vao);
    glBindVertexArray(renderer->vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(f32), (void *)(0*sizeof(f32)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(f32), (void *)(3*sizeof(f32)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

#define CIRCLE_SEGMENTS 36

internal void
renderer_create_circle(Renderer *renderer)
{
    f32 verts[CIRCLE_SEGMENTS*5]; /* @Note: 3*f32 position, 2*f32 texcoords, +1 to complete loop */
    f32 *v = verts;
    f32 err = 1e-7f*CIRCLE_SEGMENTS; /* @Note: Account for f32 precision error */
    for(f32 i = 0.0f; i < (2.0f*PI)-err; i += 2.0*PI / CIRCLE_SEGMENTS) {
        f32 x = cos(i);
        f32 y = sin(i);

        *v++ = x * 0.5f;
        *v++ = y * 0.5f;
        *v++ = 0.0f;

        *v++ = x;
        *v++ = y;
    }

    u32 vbo = 0;
    glGenBuffers(1, &vbo);

    glGenVertexArrays(1, &renderer->vao);
    glBindVertexArray(renderer->vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5*sizeof(f32), (void *)(0*sizeof(f32)));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5*sizeof(f32), (void *)(3*sizeof(f32)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

internal void
renderer_create_line2d(Renderer *renderer)
{
    f32 verts[] = {
        -1.0f, 0.0f, 0.0f,
        +1.0f, 0.0f, 0.0f,
    };

    u32 vbo = 0;
    glGenBuffers(2, &vbo);

    glGenVertexArrays(1, &renderer->vao);
    glBindVertexArray(renderer->vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

internal void
renderer_destroy(Renderer *renderer)
{
    glDeleteVertexArrays(1, &renderer->vao);
}

internal void
render_rectangle(Rectangle *r)
{
    mat4 model = transform_axis(vec3_v2(r->size, 1.0f),
                                vec3(0.0f, 0.0f, 1.0f), r->rotation,
                                vec3_v2(r->position, 0.0f));

    texture_activate(r->texture);

    glUseProgram(global_state.shader);

    glUniformMatrix4fv(glGetUniformLocation(global_state.shader, "model"), 1, false, model.e);

    b32 talpha = r->texture && r->texture->alpha;

    glBindVertexArray(global_state.rectangle.vao);

    if(r->fill_type & FillType_FILL) {
        b32 alpha = talpha || r->color.a < 1.0f;
        if(alpha) glEnable(GL_BLEND);
        glUniform4fv(glGetUniformLocation(global_state.shader, "color"), 1, r->color.e);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
        if(alpha) glDisable(GL_BLEND);
    }

    if(r->fill_type & FillType_STROKE) {
        b32 alpha = talpha || r->stroke_color.a < 1.0f;
        if(alpha) glEnable(GL_BLEND);
        glUniform4fv(glGetUniformLocation(global_state.shader, "color"), 1, r->stroke_color.e);
        glEnable(GL_LINE_SMOOTH);
        glLineWidth(r->stroke_size);
        glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_SHORT, 0);
        glDisable(GL_LINE_SMOOTH);
        if(alpha) glDisable(GL_BLEND);
    }

    glBindVertexArray(0);

    glUseProgram(0);

    texture_deactivate(r->texture);
}

internal void
render_triangle(Triangle *t)
{
    mat4 model = transform_axis(vec3_v2(t->size, 1.0f),
                                vec3(0.0f, 0.0f, 1.0f), t->rotation,
                                vec3_v2(t->position, 0.0f));

    texture_activate(t->texture);

    glUseProgram(global_state.shader);

    glUniformMatrix4fv(glGetUniformLocation(global_state.shader, "model"), 1, false, model.e);

    b32 talpha = t->texture && t->texture->alpha;

    glBindVertexArray(global_state.triangle.vao);

    if(t->fill_type & FillType_FILL) {
        b32 alpha = talpha || t->color.a < 1.0f;
        if(alpha) glEnable(GL_BLEND);
        glUniform4fv(glGetUniformLocation(global_state.shader, "color"), 1, t->color.e);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        if(alpha) glDisable(GL_BLEND);
    }

    if(t->fill_type & FillType_STROKE) {
        b32 alpha = talpha || t->stroke_color.a < 1.0f;
        if(alpha) glEnable(GL_BLEND);
        glUniform4fv(glGetUniformLocation(global_state.shader, "color"), 1, t->stroke_color.e);
        glEnable(GL_LINE_SMOOTH);
        glLineWidth(t->stroke_size);
        glDrawArrays(GL_LINE_LOOP, 0, 3);
        glDisable(GL_LINE_SMOOTH);
        if(alpha) glDisable(GL_BLEND);
    }

    glBindVertexArray(0);

    glUseProgram(0);

    texture_deactivate(t->texture);
}

internal void
render_circle(Circle *c)
{
    mat4 model = transform_axis(vec3(c->radius*2.0f, c->radius*2.0f, 1.0f),
                                vec3(0.0f, 0.0f, 1.0f), c->rotation,
                                vec3_v2(c->position, 0.0f));

    texture_activate(c->texture);

    glUseProgram(global_state.shader);

    glUniformMatrix4fv(glGetUniformLocation(global_state.shader, "model"), 1, false, model.e);

    b32 talpha = c->texture && c->texture->alpha;

    glBindVertexArray(global_state.circle.vao);

    if(c->fill_type & FillType_FILL) {
        b32 alpha = talpha || c->color.a < 1.0f;
        if(alpha) glEnable(GL_BLEND);
        glUniform4fv(glGetUniformLocation(global_state.shader, "color"), 1, c->color.e);
        glDrawArrays(GL_TRIANGLE_FAN, 0, CIRCLE_SEGMENTS);
        if(alpha) glDisable(GL_BLEND);
    }

    if(c->fill_type & FillType_STROKE) {
        b32 alpha = talpha || c->stroke_color.a < 1.0f;
        if(alpha) glEnable(GL_BLEND);
        glUniform4fv(glGetUniformLocation(global_state.shader, "color"), 1, c->stroke_color.e);
        glEnable(GL_LINE_SMOOTH);
        glLineWidth(c->stroke_size);
        glDrawArrays(GL_LINE_LOOP, 0, CIRCLE_SEGMENTS);
        glDisable(GL_LINE_SMOOTH);
        if(alpha) glDisable(GL_BLEND);
    }

    glBindVertexArray(0);

    glUseProgram(0);

    texture_deactivate(c->texture);
}

internal void
render_line2d(Line2D *l)
{
    vec2 a = vec2_sub(l->end, l->start);
    mat4 model = transform_axis(vec3(line2d_length(l), 1.0f, 1.0f),
                                vec3(0.0f, 0.0f, 1.0f), atan2(a.y, a.x),
                                vec3_v2(vec2_lerp(l->start, 0.5f, l->end), 0.0f));
    model = mat4_mul(translationf(-0.5f, -0.5f, 0.0f), model);

    texture_activate(0);

    glUseProgram(global_state.shader);

    glUniformMatrix4fv(glGetUniformLocation(global_state.shader, "model"), 1, false, model.e);

    glBindVertexArray(global_state.line2d.vao);

    glUniform4fv(glGetUniformLocation(global_state.shader, "color"), 1, vec4_one.e);
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(1);
    glDrawArrays(GL_LINE_STRIP, 0, 2);
    glDisable(GL_LINE_SMOOTH);

    glBindVertexArray(0);

    glUseProgram(0);

    texture_deactivate(0);
}
