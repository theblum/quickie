/* ===========================================================================
 * File: logging.c
 * Date: 07 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

internal void
term_colors_init(TermColors *colors, b32 enable)
{
    if(enable) {
        colors->normal  = "\033[0m";
        colors->black   = "\033[0;30m";
        colors->red     = "\033[0;31m";
        colors->green   = "\033[0;32m";
        colors->yellow  = "\033[0;33m";
        colors->blue    = "\033[0;34m";
        colors->magenta = "\033[0;35m";
        colors->cyan    = "\033[0;36m";
        colors->white   = "\033[0;37m";
    } else {
        colors->normal  = "";
        colors->black   = "";
        colors->red     = "";
        colors->green   = "";
        colors->yellow  = "";
        colors->blue    = "";
        colors->magenta = "";
        colors->cyan    = "";
        colors->white   = "";
    }
}

internal void
print_type(u32 type, char *format, va_list vargs)
{
    FILE *f = stderr;
    char *c = "";
    char *p = "";

    switch(type) {
        case MessageType_NONE:    { f = stdout; } break;
        case MessageType_INFO:    { p = "INFO: ";    c = global_colors.green; } break;
        case MessageType_WARNING: { p = "WARNING: "; c = global_colors.yellow; } break;
        case MessageType_ERROR:   { p = "ERROR: ";   c = global_colors.red; } break;

        default: { invalid_code_path; } break;
    }

    fprintf(f, "%s%s%s", c, p, global_colors.normal);
    vfprintf(f, format, vargs);
}

internal void __attribute((format(printf, 2, 3)))
print_message(u32 type, char *format, ...)
{
    va_list vargs;
    va_start(vargs, format);
    print_type(type, format, vargs);
    va_end(vargs);
}

internal void __attribute__((format(printf, 1, 2)))
print_info(char *format, ...)
{
    va_list vargs;
    va_start(vargs, format);
    print_type(MessageType_INFO, format, vargs);
    va_end(vargs);
}

internal void __attribute__((format(printf, 1, 2)))
print_warning(char *format, ...)
{
    va_list vargs;
    va_start(vargs, format);
    print_type(MessageType_WARNING, format, vargs);
    va_end(vargs);
}

/* @Note: If `exitcode` is 0, returns from function as normal.  Otherwise, exits program with
 * `exitcode` as the exit code. */
internal void __attribute__((format(printf, 2, 3)))
print_error(u32 exitcode, char *format, ...)
{
    va_list vargs;
    va_start(vargs, format);
    print_type(MessageType_ERROR, format, vargs);
    va_end(vargs);

    if(exitcode)
        exit(exitcode);
}
