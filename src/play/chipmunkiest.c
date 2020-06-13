/* ===========================================================================
 * File: chipmunkiest.c
 * Date: 09 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include <chipmunk/chipmunk.h>
#include "includes.h"

global State *state = &global_state;

global Circle ball;
global Rectangle ground;

global cpVect  cgravity;
global cpSpace *cspace; 
global cpShape *cground;
global cpShape *cballs;
global cpBody  *cballb;

internal void
setup(void)
{
    cgravity = cpv(0.0f, -700.0f);

    cspace = cpSpaceNew();
    cpSpaceSetGravity(cspace, cgravity);

    ground.position  = vec2(0.0f, -(state->height*0.5f) + 15.0f);
    ground.size      = vec2(200.0f, 10.0f);
    ground.color     = vec4(0.0f, 0.6f, 0.8f, 1.0f);
    ground.fill_type = FillType_FILL;

    cground = cpSegmentShapeNew(cpSpaceGetStaticBody(cspace),
                                cpv(ground.position.x - (ground.size.x*0.5f),
                                    ground.position.y),
                                cpv(ground.position.x + (ground.size.x*0.5f),
                                    ground.position.y),
                                ground.size.y*0.5f);
    cpShapeSetFriction(cground, 1.0f);
    cpShapeSetElasticity(cground, 1.0f);
    cpSpaceAddShape(cspace, cground);

    ball.position  = vec2(0.0f, 15.0f);
    ball.radius    = 10.0f;
    ball.fill_type = FillType_STROKE;
    ball.stroke_color = vec4(0.6f, 0.7f, 0.0f, 1.0f);
    ball.stroke_size  = 1.0f;

    f32 mass = 1.0f;
    f32 moment = cpMomentForCircle(mass, 0, ball.radius, cpvzero);
    cballb = cpSpaceAddBody(cspace, cpBodyNew(mass, moment));
    cpBodySetPosition(cballb, cpv(ball.position.x, ball.position.y));

    cballs = cpCircleShapeNew(cballb, ball.radius, cpvzero);
    cpShapeSetFriction(cballs, 0.7f);
    cpShapeSetElasticity(cballs, 0.3f);
    f32 e = cpShapeGetElasticity(cballs);
    print_info("elast: %f\n", e);
    cpSpaceAddShape(cspace, cballs);
}

internal void
update(f32 dt)
{
    cpSpaceStep(cspace, dt);
    cpVect pos = cpBodyGetPosition(cballb);
    ball.position.x = pos.x;
    ball.position.y = pos.y;
}

internal void
draw(void)
{
    render_rectangle(&ground);
    render_circle(&ball);
}

internal void
teardown(void)
{
    cpShapeFree(cballs);
    cpBodyFree(cballb);
    cpShapeFree(cground);
    cpSpaceFree(cspace);
}
