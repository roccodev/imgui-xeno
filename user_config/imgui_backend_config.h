#pragma once

/**
 * This header contains some feature flags that can be enabled or disabled manually for each game.
 *
 * For example, your game might need to use a specific command buffer, or change the viewport size.
 */

// Graphics

// ID starts at 0.
// The first command buffer that is initialized in Xenoblade games is too small for ImGui
#define IMGUI_XENO_COMMAND_BUFFER_ID 1
// Might be necessary if the game doesn't expose glslc
#define IMGUI_XENO_FORCE_PRECOMPILED_SHADERS false
// Base path for shaders. Note: file system must be mounted before the call to imgui_xeno_init
#define IMGUI_XENO_SHADER_PATH "rom:/imgui/shaders"
#define IMGUI_XENO_VIEWPORT_WIDTH 1280
#define IMGUI_XENO_VIEWPORT_HEIGHT 720

// Input

#define IMGUI_XENO_DEFAULT_INPUT_PORT 0

// ImGui

// Change to true to draw the ImGui demo window
#define IMGUI_XENO_DRAW_DEMO false
// If true, loads Jetbrains Mono as the default font.
// You can load custom fonts during init using ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF
#define IMGUI_XENO_LOAD_DEFAULT_FONT true

// Logging

// Logs messages using system calls. If a logger is provided with imgui_xeno_set_logger, it will be used instead.
#define IMGUI_XENO_LOG_SVC true