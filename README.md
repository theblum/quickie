# Quickie OpenGL playground

This is a **work-in-progress** playground for me to learn various aspects of graphics programming.  This
includes learning the OpenGL API, 2D and 3D graphics, rendering techniques, fun visualizations, and
whatever else I can think of.  Many of the playgrounds are based on the
[coding challenges playlist](https://www.youtube.com/playlist?list=PLRqwX-V7Uu6ZiZxtDDRCi6uhfTH4FilpH)
on [The Coding Train](https://www.youtube.com/user/shiffman) YouTube channel.

**Note:** The math functions use a left-handed coordinate system, row-major matrices, and
left-to-right matrix multiplication.  Many of these functions are based on the code in a fantastic
book by _Gabor Szauer_ called [_Game Physics Cookbook_](https://gamephysicscookbook.com).

## Usage

To create a new playground, create a `.c` file in the `./src/play/` directory.  At the top of this
file, make sure to `#include "includes.h"`.  At the bottom of the `./include/includes.h` file,
comment out any other include directive that contains a `../src/play/*.c` file path and add an include
to the `.c` file just created.

Each playground must include the following functions:

- `internal void setup(void)`
- `internal void update(f32 dt)`
- `internal void draw(void)`
- `internal void teardown(void)`

## Building

Make sure to be in the root directory of this project.  Simply run the `./build.sh` command to build
the executable in debug mode.  To build in release mode, instead run `./build.sh -R`.  The executable
will be placed in the `./build/` directory.

## Running

In the root directory of this project, run `./run.sh quickie` to start the previously built debug
executable.  To run the release build, instead run `./run.sh -R quickie`.  Check out the `./run.sh`
source for other available options (i.e. `./run -d` to debug with `gdb`).
