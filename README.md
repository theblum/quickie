# Quickie OpenGL playground

This is a work-in-progress playground for me to learn various aspects of graphics programming.  This
includes learning the OpenGL API, 2D and 3D graphics, rendering techniques, fun visualizations, and
whatever else I can think of.  Many of the playgrounds are based on the
[coding challenges playlist](https://www.youtube.com/playlist?list=PLRqwX-V7Uu6ZiZxtDDRCi6uhfTH4FilpH)
on [The Coding Train](https://www.youtube.com/user/shiffman) YouTube channel.

## Usage

To create a new playground, create a `.c` file in the `./src/play/` directory.  At the top of this
file, make sure to `#include "includes.h"`.  At the bottom of the `./include/includes.h` file,
comment out any other include directive that contains a `../src/play/*.c` filepath and add an include
to the `.c` file just created.

Each playground must include the following functions:

- `internal void setup(void)`
- `internal void update(f32 dt)`
- `internal void draw(void)`
- `internal void teardown(void)`
