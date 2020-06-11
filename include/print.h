#if !defined(LOGGING_H)
#define LOGGING_H
/* ===========================================================================
 * File: logging.h
 * Date: 07 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

enum MessageType {
    MessageType_NONE,

    MessageType_INFO,
    MessageType_WARNING,
    MessageType_ERROR,

    MessageType_COUNT,
};

typedef struct {
    char *normal;
    char *black;
    char *red;
    char *green;
    char *yellow;
    char *blue;
    char *magenta;
    char *cyan;
    char *white;
} TermColors;

global TermColors global_colors;

#endif
