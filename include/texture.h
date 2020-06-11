#if !defined(TEXTURE_H)
#define TEXTURE_H
/* ===========================================================================
 * File: texture.h
 * Date: 09 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

typedef struct {
    u32 id;
    u8 *data;
    u32 width;
    u32 height;
    u32 alpha;
} Texture;

#endif
