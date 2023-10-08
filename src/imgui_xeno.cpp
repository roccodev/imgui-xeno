#include "imgui_xeno.h"
#include "imgui_backend/imgui_nvn.h"
#include "logger/Logger.hpp"

extern "C" void imgui_xeno_init(InitFunc preInitCallback, InitFunc postInitCallback, NewFrameFunc newFrameCallback, ProcDrawFunc renderCallback) {
  if (preInitCallback != 0)
    nvnImGui::addPreInitFunc(preInitCallback);
  if (postInitCallback != 0)
    nvnImGui::addPostInitFunc(postInitCallback);

  nvnImGui::InstallHooks();

  if (newFrameCallback != 0)
    nvnImGui::addNewFrameFunc(newFrameCallback);
  if (renderCallback != 0)
    nvnImGui::addDrawFunc(renderCallback);
}

extern "C" void* imgui_xeno_bootstrap_hook(const char *functionName, nvnImGui::OrigNvnBootstrap origFn) {
  return nvnImGui::NvnBootstrapHook(functionName, origFn);
}

extern "C" void imgui_xeno_set_logger(LoggerFunc loggerCallback) {
  Logger::instance().forward(loggerCallback);
}