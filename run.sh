#!/usr/bin/env bash

# This script runs programs built with the corresponding `build.sh` script. You must pass the program
# you wish to run as an arugment.  By default, the debug build is run, so you do not need to add
# `_debug` in the program name.
#
# If `-R` is passed as the first argument, the release build will be executed.  The following
# arguments can be passed after `-R` and before the program name.  They are mutually exclusive:
#
# * `-d`:   debugger defined in `$DBG`
# * `-v`:   valgrind --leak-check=full
# * `-vs`:  valgrind --leak-check=full --show-leak-kinds=all
# * `-vt`:  valgrind --leak-check=full --track-origins=yes
# * `-vst`: valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes
#
# Any additional arguments will be passed along to the program.

: "${BUILDDIR:="./build"}"
: "${DBG:="gdb"}"
: "${VALGRIND:="valgrind"}"

DEBUG_EXT="_debug"
if [ "$1" == "-R" ]; then
    DEBUG_EXT=""
    shift
fi

# @Note: I'm just doing this to be clever.  It is just a sequence of "ternary" expressions.
PREFIX=$( ([ "$1" == "-d" ]   && (echo "$DBG --")) ||
          ([ "$1" == "-v" ]   && (echo "$VALGRIND --leak-check=full --")) ||
          ([ "$1" == "-vs" ]  && (echo "$VALGRIND --leak-check=full --show-leak-kinds=all --")) ||
          ([ "$1" == "-vt" ]  && (echo "$VALGRIND --leak-check=full --track-origins=yes --")) ||
          ([ "$1" == "-vst" ] && (echo "$VALGRIND --leak-check=full --show-leak-kinds=all --track-origins=yes --")) ||
          (echo ""))
[[ "$1" == -* ]] && shift

: "${PROGRAM:=${1/_debug}}"
: "${PROGRAM:?"Usage: $0 [-R] [-d|-v|-vs|-vt|-vst] PROGRAM"}"
shift

eval "$PREFIX" "$BUILDDIR/$PROGRAM$DEBUG_EXT" "$@"
