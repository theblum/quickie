#!/usr/bin/env bash

# This script compiles C program unity builds.  When run, it will find all `*_main.c` files located
# in `$SRCDIR`, compile them with `$CC`, and place them in `$BUILDDIR`, with the `_main.c` removed.
#
# If `-R` is passed as the first argument, a release build will be compiled, otherwise `_debug` will
# be appended to the executable.  Any additional arguments will be passed along to the compiler.
#
# Typically you will only need to adjust the first three variables when creating a new project.
# However, you can temporarily set any of the first five variables by setting them as environment
# variables prior to running.

: "${SRCDIR:="./src"}"
: "${BUILDDIR:="./build"}"
: "${PKGCONFIG:="gl glfw3 portaudio-2.0"}"
: "${LIBS:="-lm -ldl -lchipmunk"}"

: "${CC:="gcc"}"
: "${FILES:=$(find "$SRCDIR" -name "*_main.c")}"

: "${FILES:?"No main source files found in $SRCDIR"}"

DEBUG_FLAGS="-g -ggdb -DDEBUG_BUILD -O0"
DEBUG_EXT="_debug"
if [ "$1" == "-R" ]; then
    DEBUG_FLAGS="-O3"
    DEBUG_EXT=""
    shift
fi

PKGCONFIG_CFLAGS=${PKGCONFIG:+$(pkg-config --cflags "$PKGCONFIG")}
PKGCONFIG_LIBS=${PKGCONFIG:+$(pkg-config --libs "$PKGCONFIG")}

WARNINGS="-Wall -Wextra -Wno-unused-function"
CFLAGS="$DEBUG_FLAGS -fms-extensions -pedantic -pipe -I./include -I./vendor/include -D_DEFAULT_SOURCE $PKGCONFIG_CFLAGS"
LDLIBS="$PKGCONFIG_LIBS $LIBS"

[ -d "$BUILDDIR" ] || mkdir "$BUILDDIR"
time {
    RESULT=0
    for FILE in $FILES; do
        OUTFILE="${FILE#${SRCDIR}/}"
        OUTFILE="${OUTFILE%_main.c}"
        OUTFILE="${OUTFILE/\//_}${DEBUG_EXT}"
        # shellcheck disable=SC2089
        DEFINES="-DPROGRAM_NAME=\"$OUTFILE\""
        echo "*** building $OUTFILE"
        # shellcheck disable=SC2086 disable=SC2090
        $CC -o "$BUILDDIR/$OUTFILE" "$@" $CFLAGS $WARNINGS $DEFINES "$FILE" $LDLIBS
        RESULT=${RESULT/0/$?}
    done
}

exit $RESULT
