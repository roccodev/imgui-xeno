#pragma once

#include "xeno_types.h"

extern "C" void imgui_xeno_init(InitFunc init, ProcDrawFunc renderCallback);

extern "C" void* imgui_xeno_bootstrap_hook(const char *functionName, OrigNvnBootstrap origFn);