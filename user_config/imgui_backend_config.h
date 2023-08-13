#pragma once

/**
 * This header contains some feature flags that can be enabled or disabled manually for each game.
 *
 * For example, your game might need to use a specific command buffer, or change the viewport size.
 */

// Graphics

// ID starts at 0.
// The first command buffer that is initialized in Xenoblade games is too small for ImGui
#ifndef IMGUI_XENO_COMMAND_BUFFER_ID
#define IMGUI_XENO_COMMAND_BUFFER_ID 1
#endif
// Might be necessary if the game doesn't expose glslc
#ifndef IMGUI_XENO_FORCE_PRECOMPILED_SHADERS
#define IMGUI_XENO_FORCE_PRECOMPILED_SHADERS false
#endif
// Base path for shaders. Note: file system must be mounted before the call to imgui_xeno_init
#ifndef IMGUI_XENO_SHADER_PATH
#define IMGUI_XENO_SHADER_PATH "rom:/imgui/shaders"
#endif
#ifndef IMGUI_XENO_VIEWPORT_WIDTH
#define IMGUI_XENO_VIEWPORT_WIDTH 1280
#endif
#ifndef IMGUI_XENO_VIEWPORT_HEIGHT
#define IMGUI_XENO_VIEWPORT_HEIGHT 720
#endif

// Input

#ifndef IMGUI_XENO_DEFAULT_INPUT_PORT
#define IMGUI_XENO_DEFAULT_INPUT_PORT 0
#endif
// Enable keyboard/mouse inputs when connected to the Switch via USB
#ifndef IMGUI_XENO_INPUT_KBM
#define IMGUI_XENO_INPUT_KBM true
#endif
// Enable gamepad inputs (must be toggled by pressing both sticks)
#ifndef IMGUI_XENO_INPUT_PAD
#define IMGUI_XENO_INPUT_PAD true
#endif
// Enable touchscreen inputs
#ifndef IMGUI_XENO_INPUT_TOUCH
#define IMGUI_XENO_INPUT_TOUCH true
#endif

// ImGui

// Change to true to draw the ImGui demo window
#ifndef IMGUI_XENO_DRAW_DEMO
#define IMGUI_XENO_DRAW_DEMO false
#endif
// If true, loads Jetbrains Mono as the default font.
// You can load custom fonts during init using ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF
#ifndef IMGUI_XENO_LOAD_DEFAULT_FONT
#define IMGUI_XENO_LOAD_DEFAULT_FONT true
#endif

// Logging

// Logs messages using system calls. If a logger is provided with imgui_xeno_set_logger, it will be used instead.
#ifndef IMGUI_XENO_LOG_SVC
#define IMGUI_XENO_LOG_SVC true
#endif