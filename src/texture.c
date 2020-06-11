/* ===========================================================================
 * File: texture.c
 * Date: 09 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

internal void
texture_create(Texture *texture, u32 width, u32 height, b32 alpha)
{
    texture->width = width;
    texture->height = height;
    texture->alpha = alpha;
    texture->data = calloc(texture->width*texture->height, sizeof(u32));

    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexImage2D(GL_TEXTURE_2D, 0,
                 GL_RGBA,
                 texture->width, texture->height,
                 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, texture->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);
}

internal void
texture_update(Texture *texture)
{
    glBindTexture(GL_TEXTURE_2D, texture->id);
    glTexSubImage2D(GL_TEXTURE_2D,
                    0,
                    0, 0,
                    texture->width, texture->height,
                    GL_RGBA,
                    GL_UNSIGNED_BYTE, texture->data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

internal void
texture_activate(Texture *texture)
{

    glUseProgram(global_state.shader);
    glActiveTexture(GL_TEXTURE0);
    if(texture) {
        glBindTexture(GL_TEXTURE_2D, texture->id);
        glUniform1i(glGetUniformLocation(global_state.shader, "use_tex"), true);
    } else {
        glBindTexture(GL_TEXTURE_2D, global_state.empty_tex);
        glUniform1i(glGetUniformLocation(global_state.shader, "use_tex"), false);
    }
    glUseProgram(0);
}

internal void
texture_deactivate(Texture *texture)
{
    unused(texture);
    glBindTexture(GL_TEXTURE_2D, 0);
}

internal void
texture_destroy(Texture *texture)
{
    glDeleteTextures(1, &texture->id);
    free(texture->data);
    texture->data = 0;
    texture->width = 0;
    texture->height = 0;
}
