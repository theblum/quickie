#if !defined(INCLUDES_H)
#define INCLUDES_H
/* ===========================================================================
 * File: includes.h
 * Date: 03 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#define GLAD_GL_IMPLEMENTATION
#include "glad/gl.h"
#include <GLFW/glfw3.h>

#define SKRYTCH_IMPLEMENTATION
#define SKRYTCH_SHORT_NAMES
#include <skrytch/skrytch.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <math.h>
#include <unistd.h>

#include "print.h"
#include "skrmath.h"
#include "texture.h"
#include "shapes.h"
#include "shader.h"
#include "render.h"
#include "state.h"

#include "../src/print.c"
#include "../src/skrmath.c"
#include "../src/texture.c"
#include "../src/shader.c"
#include "../src/render.c"

/* @Note: uncomment whichever program you want to run below */

#include "../src/play/tester.c"
// #include "../src/play/chipmunkiest.c"
// #include "../src/play/stars.c"
// #include "../src/play/particle.c"

#endif
