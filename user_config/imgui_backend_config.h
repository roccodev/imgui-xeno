#pragma once

/**
 * This header contains some feature flags that can be enabled or disabled manually for each game.
 *
 * For example, your game might need to use a specific command buffer, or change the viewport size.
 */

// ID starts at 0.
// The first command buffer that is initialized in Xenoblade games is too small for ImGui
#define IMGUI_XENO_COMMAND_BUFFER_ID 1

#define IMGUI_XENO_DEFAULT_INPUT_PORT 0

// Change to true to draw the ImGui demo window
#define IMGUI_XENO_DRAW_DEMO false