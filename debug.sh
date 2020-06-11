#!/usr/bin/env bash

: "${BUILDDIR:="./build"}"
: "${EXT:="_debug"}"
: "${GDB_SERVER_PATH:="/home/blum/git/gdb-frontend"}"
: "${GDB_SERVER_ADDRESS:="http://127.0.0.1:5551"}"
: "${GDB:="gdb"}"
: "${BROWSER:="xdg-open"}"
: "${CURL:="curl"}"

if [ ! "$(pgrep $GDB)" ]; then
    tmux new-session -s tempdbg -d "$GDB_SERVER_PATH/gdbfrontend" --readonly --workdir="$(realpath "$BUILDDIR/..")"
    sleep 0.3
    tmux move-window -s tempdbg:1 -t gdb-frontend:2
    sleep 0.3
    tmux select-window -t gdb-frontend:1
    sleep 0.3
fi

curl "$GDB_SERVER_ADDRESS/api/load" --get --data "file=$(realpath "$BUILDDIR/$1$EXT")"
"$BROWSER" "$GDB_SERVER_ADDRESS/terminal/"
