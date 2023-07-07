#pragma once

#include "xeno_types.h"

/**
 * Registers callbacks that are executed when the backend is fully initialized, and every time ImGui needs to render
 * a frame.
 *
 * **Note**: this is not sufficient to initialize the ImGui backend. A hook must also be registered (using your platform
 * of choice: Skyline, exlaunch, etc.) for the `nvnBootstrapLoader` function. The hook must call
 * `imgui_xeno_bootstrap_hook`.
 *
 * @param init the function to execute after the ImGui backend has been fully initialized
 * @param init the function to execute every frame
 */
extern "C" void imgui_xeno_init(InitFunc init, ProcDrawFunc renderCallback);

/**
 * The function to call when `nvnBootstrapLoader` is being called by the game.
 *
 * This hook attempts to grab NVN instances from the called functions by redirecting execution to internal functions.
 *
 * @param functionName the function name parameter from the original function
 * @param origFn a pointer to the original function (trampoline functions are also accepted, provided they call the
 *               original)
 * @returns a function pointer that should be used as the hook's return value
 */
extern "C" void* imgui_xeno_bootstrap_hook(const char *functionName, OrigNvnBootstrap origFn);

/**
 * Registers a custom logging function that both ImGui and imgui-xeno can use.
 *
 * By default, if logging is enabled (see `IMGUI_XENO_LOG_SVC`), messages are logged to the debug system output using
 * supervisor calls.
 *
 * This function can be used to redirect log messages to a user-provided frontend instead.
 * The callback takes the following parameters:
 *
 * - `const char* buffer`: the nul-terminated message buffer
 * - `size_t len`: the size of the string in the buffer. It is guaranteed that `len == strlen(buffer)`.
 *
 * @param loggerCallback the external logger function
 */
extern "C" void imgui_xeno_set_logger(LoggerFunc loggerCallback);