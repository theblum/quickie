/* ===========================================================================
 * File: quickie_main.c
 * Date: 03 Jun 2020
 * Creator: Brian Blumberg <blum@disroot.org>
 * Notice: Copyright (c) 2020 Brian Blumberg. All Rights Reserved.
 * ===========================================================================
 */

#include "includes.h"

#if !defined(SCREEN_WIDTH)
#define SCREEN_WIDTH 1280
#endif

#if !defined(SCREEN_HEIGHT)
#define SCREEN_HEIGHT 720
#endif

#if !defined(SCREEN_SCALE)
#define SCREEN_SCALE 1.0f
#endif

internal void
fbsize_callback(GLFWwindow *window, s32 width, s32 height)
{
    unused(window);

    global_state.width = width * (1.0f / global_state.scale);
    global_state.height = height * (1.0f / global_state.scale);

#if 0
    state->view = mat4_identity;
    global_state.view = scale(global_state.view,
                              vec3(1.0f / global_state.scale,
                                   1.0f / global_state.scale,
                                   1.0f));
    global_state.view = translate(global_state.view,
                                  vec3(global_state.width * global_state.scale * 0.5f,
                                       global_state.height * global_state.scale * 0.5f,
                                       0.0f));
    global_state.view = scale(global_state.view,
                              vec3(global_state.scale,
                                   global_state.scale,
                                   1.0f));

    mat4 projection = ortho(0.0f, global_state.width,
                            global_state.height, 0.0f,
                            -1.0f, 100.0f);

    glUseProgram(global_state.shader);
    glUniformMatrix4fv(glGetUniformLocation(global_state.shader, "projection"),
                       1, false, (f32 *)projection.row);
    glUseProgram(0);
#endif

    print_info("window size: w: %d, h: %d\n", width, height);
    print_info("global size: w: %d, h: %d\n", global_state.width, global_state.height);

    glViewport(0, 0, width, height);
}

internal void
key_callback(GLFWwindow *window, s32 key, s32 scancode, s32 action, s32 mods)
{
    unused(scancode);
    unused(mods);

    assert(key > GLFW_KEY_UNKNOWN && key <= GLFW_KEY_LAST);
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    switch(action) {
        case GLFW_PRESS:   { global_state.keys[key] = true; } break;
        case GLFW_RELEASE: { global_state.keys[key] = false; } break;
        case GLFW_REPEAT:  { /* print_info("GLFW_REPEAT received\n"); */ } break;

        default: { invalid_code_path; } break;
    }
}

internal void
mouse_button_callback(GLFWwindow *window, s32 button, s32 action, s32 mods)
{
    unused(window);
    unused(mods);

    switch(action) {
        case GLFW_PRESS:   { global_state.mouse.buttons[button] = true; } break;
        case GLFW_RELEASE: { global_state.mouse.buttons[button] = false; } break;

        default: { invalid_code_path; } break;
    }
}

internal void
cursor_pos_callback(GLFWwindow *window, f64 xpos, f64 ypos)
{
    unused(window);
    global_state.mouse.position = vec2(xpos - (global_state.width * global_state.scale) * 0.5f,
                                       -ypos + (global_state.height * global_state.scale) * 0.5f);
    global_state.mouse.position = vec2_divs(global_state.mouse.position, global_state.scale);
}

internal void
gl_debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                  GLsizei length, const GLchar *message, const void *userp)
{
    unused(length);
    unused(userp);

    b32 error   = (type == GL_DEBUG_TYPE_ERROR);
    b32 info    = (type == GL_DEBUG_TYPE_OTHER);
    b32 warning = !(error && type);

    char *srcstr =
        (source == GL_DEBUG_SOURCE_API)             ? "API"             :
        (source == GL_DEBUG_SOURCE_WINDOW_SYSTEM)   ? "WINDOW SYSTEM"   :
        (source == GL_DEBUG_SOURCE_SHADER_COMPILER) ? "SHADER COMPILER" :
        (source == GL_DEBUG_SOURCE_THIRD_PARTY)     ? "THIRD PARTY"     :
        (source == GL_DEBUG_SOURCE_APPLICATION)     ? "APPLICATION"     :
        (source == GL_DEBUG_SOURCE_OTHER)           ? "OTHER"           : "UNKNOWN";

    char *typestr =
        (type == GL_DEBUG_TYPE_ERROR)               ? "ERROR"               :
        (type == GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR) ? "DEPRECATED BEHAVIOR" :
        (type == GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR)  ? "UNDEFINED BEHAVIOR"  :
        (type == GL_DEBUG_TYPE_PORTABILITY)         ? "PORTABILITY"         :
        (type == GL_DEBUG_TYPE_PERFORMANCE)         ? "PERFORMANCE"         :
        (type == GL_DEBUG_TYPE_MARKER)              ? "MARKER"              :
        (type == GL_DEBUG_TYPE_PUSH_GROUP)          ? "GROUP"               :
        (type == GL_DEBUG_TYPE_POP_GROUP)           ? "GROUP"               :
        (type == GL_DEBUG_TYPE_OTHER)               ? "OTHER"               : "UNKNOWN";

    char *sevstr =
        (severity == GL_DEBUG_SEVERITY_LOW)          ? "LOW"          :
        (severity == GL_DEBUG_SEVERITY_MEDIUM)       ? "MEDIUM"       :
        (severity == GL_DEBUG_SEVERITY_HIGH)         ? "HIGH"         :
        (severity == GL_DEBUG_SEVERITY_NOTIFICATION) ? "NOTIFICATION" : "UNKNOWN";

    if(error)
        print_error(0, "GL(%u):%s:%s:%s:\n%s\n", id, srcstr, typestr, sevstr, message);
    else if(info)
        print_info("GL(%u):%s:%s:%s:\n%s\n", id, srcstr, typestr, sevstr, message);
    else if(warning)
        print_warning("GL(%u):%s:%s:%s:\n%s\n", id, srcstr, typestr, sevstr, message);
    else
        invalid_code_path;
}

internal void
gl_debug_messages(b32 enable)
{
    s32 flags = 0;
    glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
    if(flags & GL_CONTEXT_FLAG_DEBUG_BIT) {
        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(gl_debug_callback, 0);
        glDebugMessageControl(GL_DONT_CARE,
                              GL_DONT_CARE,
                              GL_DONT_CARE,
                              0,
                              0,
                              enable);
    }
}

internal void
glfw_check_error(void)
{
    const char *err = 0;
    s32 ret = glfwGetError(&err);
    if(ret)
        print_error(ret, "Unable to init GLFW: %s\n", err);
}

internal void
state_init(State *state, s32 width, s32 height, f32 scale)
{
    state->width  = width;
    state->height = height;
    state->scale  = scale;

    state->clear = true;
    state->clear_color = vec4(0.0f, 0.0f, 0.0f, 1.0f);

    state->multisample = false;

    state->shader = shader_create(global_vsrc, global_fsrc, 0);

    glGenTextures(1, &state->empty_tex);
    glBindTexture(GL_TEXTURE_2D, state->empty_tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    state->view = mat4_identity;
    state->view = mat4_mul(state->view, translationf(state->width * 0.5f, state->height * 0.5f, 0.0f));

    state->projection = ortho(0.0f, (f32)state->width,
                              (f32)state->height, 0.0f,
                              -1.0f, 100.0f);

    renderer_create_rectangle(&state->rectangle);
    renderer_create_triangle(&state->triangle);
    renderer_create_circle(&state->circle);
    renderer_create_line(&state->line);
}

internal void cleanup(void);

int
main(void)
{
    term_colors_init(&global_colors, isatty(STDOUT_FILENO));

    glfwInit();
    glfw_check_error();

    atexit(cleanup);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, true);
    glfwWindowHint(GLFW_SAMPLES, 4);
#if defined(DEBUG_BUILD)
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH * SCREEN_SCALE,
                                          SCREEN_HEIGHT * SCREEN_SCALE,
                                          PROGRAM_NAME,
                                          0,
                                          0);
    glfw_check_error();

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    state_init(&global_state, SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_SCALE);

    glfwSetFramebufferSizeCallback(window, fbsize_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_pos_callback);

    gl_debug_messages(true);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glfwShowWindow(window);
    glViewport(0, 0, global_state.width * global_state.scale, global_state.height * global_state.scale);

    srand(time(0));
    setup();

    glfwSwapInterval(1);

    if(global_state.multisample) glEnable(GL_MULTISAMPLE);
    else                         glDisable(GL_MULTISAMPLE);

    glUseProgram(global_state.shader);
    glUniformMatrix4fv(glGetUniformLocation(global_state.shader, "projection"),
                       1, false, (f32 *)global_state.projection.row);
    glUniformMatrix4fv(glGetUniformLocation(global_state.shader, "view"),
                       1, false, global_state.view.e);
    glUseProgram(0);

    glClearColor(global_state.clear_color.x,
                 global_state.clear_color.y,
                 global_state.clear_color.z,
                 global_state.clear_color.z);
    glClear(GL_COLOR_BUFFER_BIT);

    gl_debug_messages(false);

    f32 tlast = 0;
    f32 tcurr = glfwGetTime();

    while(!glfwWindowShouldClose(window)) {
        tcurr = glfwGetTime();
        f32 dt = tcurr - tlast;
        tlast = tcurr;

        glfwPollEvents();

        update(dt);

        glUseProgram(global_state.shader);
        glUniformMatrix4fv(glGetUniformLocation(global_state.shader, "view"),
                           1, false, global_state.view.e);
        glUseProgram(0);

        if(global_state.clear)
            glClear(GL_COLOR_BUFFER_BIT);

        draw();

        glfwSwapBuffers(window);
    }

    return 0;
}

internal void
cleanup(void)
{
    teardown();

    glDeleteTextures(1, &global_state.empty_tex);

    renderer_destroy(&global_state.rectangle);
    renderer_destroy(&global_state.triangle);
    renderer_destroy(&global_state.circle);
    renderer_destroy(&global_state.line);

    shader_destroy(global_state.shader);

    glfwTerminate();
}
