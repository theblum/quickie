/* ===========================================================================
 * File: shader.c
 * Date: 03 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

internal void
shader_print_errors(u32 id, char *type)
{
    s32 success = 0;
    b32 prg = false;
    if(!strncmp("PROGRAM", type, strlen(type)))
        prg = true;

    prg ? glGetProgramiv(id, GL_LINK_STATUS, &success)
        : glGetShaderiv(id, GL_COMPILE_STATUS, &success);

    if(!success) {
        print_error(0, "%s-time shader: %s\n", prg ? "Link" : "Compile", type);
        s32 length = 0;

        prg ? glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length)
            : glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);

        char *log = malloc(length + 1);
        log[length] = '\0';

        if(log) {
            prg ? glGetProgramInfoLog(id, length, 0, log)
                : glGetShaderInfoLog(id, length, 0, log);

            fprintf(stderr, "%s\n", log);
            free(log);
        } else {
            print_error(0, "UNABLE to allocate enough memory to print info log.\n");
        }
    }
}

internal u32
shader_create(char *vsrc, char *fsrc, char *gsrc)
{
    u32 vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, (const char **)&vsrc, 0);
    glCompileShader(vs);
    shader_print_errors(vs, "VERTEX");

    u32 fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, (const char **)&fsrc, 0);
    glCompileShader(fs);
    shader_print_errors(fs, "FRAGMENT");

    u32 gs = 0;
    if(gsrc) {
        gs = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(gs, 1, (const char **)&gsrc, 0);
        glCompileShader(gs);
        shader_print_errors(gs, "GEOMETRY");
    }

    u32 prg = glCreateProgram();
    glAttachShader(prg, vs);
    glAttachShader(prg, fs);
    if(gsrc) glAttachShader(prg, gs);
    glLinkProgram(prg);
    shader_print_errors(prg, "PROGRAM");

    if(gsrc) glDeleteShader(gs);
    glDeleteShader(fs);
    glDeleteShader(vs);

    return prg;
}

internal void
shader_destroy(u32 id)
{
    glDeleteProgram(id);
}
