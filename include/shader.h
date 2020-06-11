#if !defined(SHADER_H)
#define SHADER_H
/* ===========================================================================
 * File: shader.h
 * Date: 03 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

global char *global_vsrc =
"#version 460 core\n\n"
"in layout (location = 0) vec3 vertex;\n"
"in layout (location = 1) vec2 coords;\n"
"out vec2 tex_coords;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main() {\n"
"tex_coords = coords;\n"
"gl_Position = projection * view * model * vec4(vertex, 1.0);\n"
"}\n";

global char *global_fsrc =
"#version 460 core\n\n"
"in vec2 tex_coords;\n"
"out vec4 outp;\n"
"uniform bool use_tex;\n"
"uniform sampler2D tex;\n"
"uniform vec4 color;\n"
"void main() {\n"
"if(use_tex)\n"
"outp = color * texture(tex, tex_coords);\n"
"else\n"
"outp = color;\n"
"}\n";

#endif
